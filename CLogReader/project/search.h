#ifndef SEARCH_H
#define SEARCH_H

#include <variant>
#include <string.h>
#include <stdio.h>
#include <algorithm>

class Equal
{
    char filter[100];
    int filterLength;
public:
    Equal() = default;
    Equal(const char *filter)
    {
        snprintf(this->filter, sizeof(this->filter), "%s", filter);
        filterLength = strlen(filter);
    }
    bool search(char** line, int &lineLength)
    {
        if (lineLength != filterLength)
            return false;

        for (int i = 0; i < filterLength; i++)
        {
            if (filter[i] == '?')
                continue;

            if (filter[i] != (*line)[i])
                return false;
        }
        lineLength = 0;
        (*line) += filterLength;
        return true;
    }
};


class SimpleStart
{
    char filter[100];
    int filterLength;
public:
    SimpleStart() = default;

    SimpleStart(const char *filter)
    {
        snprintf(this->filter, sizeof(this->filter), "%s", filter);
        filterLength = strlen(filter);
    }
    bool search(char** line, int &lineLength)
    {
        if (lineLength < filterLength)
            return false;

        for (int i = 0; i < filterLength; i++)
        {
            if (filter[i] == '?')
                continue;

            if (filter[i] != (*line)[i])
                return false;
        }
        (*line) += filterLength;
        lineLength -= filterLength;
        return true;
    }
};

class SimpleEnd
{
    char filter[100];
    int filterLength;
public:
    SimpleEnd() = default;

    SimpleEnd(const char *filter)
    {
        snprintf(this->filter, sizeof(this->filter), "%s", filter);
        filterLength = strlen(filter);
    }
    bool search(char** line, int &lineLength)
    {
        if (lineLength < filterLength)
            return false;

        for (int i = 0; i < filterLength; i++)
        {
            if (filter[i] == '?')
                continue;

            if (filter[i] != (*line)[lineLength - filterLength + i])
                return false;
        }
        lineLength -= filterLength;
        return true;
    }

};

class BoyerMoore
{
    static const int NO_OF_CHARS = 256;
    int badchar[NO_OF_CHARS];
    char filter[100];
    int shift[100];
    int shiftLength = -1;
    int  filterLength = -1;

public:
    BoyerMoore() = default;
    void badCharHeuristic()
    {
        int i;
        // Initialize all occurrences as -1
        for (i = 0; i < NO_OF_CHARS; i++)
            badchar[i] = -1;

        // Fill the actual value of last occurrence
        // of a character
        for (i = 0; i < filterLength; i++)
        {
            if (filter[i] == '?')
                continue;

            badchar[(int)filter[i]] = i;
        }
    }

    // preprocessing for strong good suffix rule
    void preprocess_strong_suffix(int *bpos)
    {
        // m is the length of pattern
        int i=filterLength, j=filterLength+1;
        bpos[i]=j;

        while(i>0)
        {
            /*if character at position i-1 is not equivalent to
          character at j-1, then continue searching to right
          of the pattern for border */
            while(j<=filterLength && (
                       (filter[i-1] != filter[j-1]) || filter[i-1] == '?' || filter[j-1] == '?'))
            {
                /* the character preceding the occurrence of t in
               pattern P is different than the mismatching character in P,
               we stop skipping the occurrences and shift the pattern
               from i to j */
                if (shift[j]==0)
                    shift[j] = j-i;

                //Update the position of next border
                j = bpos[j];
            }
            /* p[i-1] matched with p[j-1], border is found.
           store the  beginning position of border */
            i--;j--;
            bpos[i] = j;
        }
    }

    //Preprocessing for case 2
    void preprocess_case2(int *bpos)
    {
        int i, j;
        j = bpos[0];
        for(i=0; i<=filterLength; i++)
        {
            /* set the border position of the first character of the pattern
           to all indices in array shift having shift[i] = 0 */
            if(shift[i]==0)
                shift[i] = j;

            /* suffix becomes shorter than bpos[0], use the position of
           next widest border as value of j */
            if (i==j)
                j = bpos[j];
        }
    }

    BoyerMoore(const char *filter)
    {
        snprintf(this->filter, sizeof(this->filter), "%s", filter);
        filterLength = strlen(filter);
        badCharHeuristic();

        int m = filterLength;

        int bpos[filterLength+1];
        shiftLength = filterLength+1;

        //initialize all occurrence of shift to 0
        for(int i=0;i<m+1;i++) shift[i]=0;

        //do preprocessing
        preprocess_strong_suffix(bpos);
        preprocess_case2(bpos);
    }

    bool search(char** line, int &lineLength)
    {
        int s = 0; // s is shift of the pattern with
        // respect to text
        while (s <= (lineLength - filterLength)) {
            int j = filterLength - 1;

            /* Keep reducing index j of pattern while
            characters of pattern and text are
            matching at this shift s */
            while (j >= 0 && (filter[j] == (*line)[s + j] || filter[j] == '?'))
                j--;

            /* If the pattern is present at current
            shift, then index j will become -1 after
            the above loop */
            if (j < 0) {
                int offset = s + filterLength - 1;
                (*line) += offset;
                lineLength -= offset;
                return true;
            }

            else
            {
                /* Shift the pattern so that the bad character
                in text aligns with the last occurrence of
                it in pattern. The max function is used to
                make sure that we get a positive shift.
                We may get a negative shift if the last
                occurrence of bad character in pattern
                is on the right side of the current
                character. */
                int badShift = std::max(1, j - badchar[(*line)[s + j]]);
                s += std::max(shift[j+1], badShift);
            }
        }
        return false;
    }

};

using Search = std::variant<Equal, SimpleStart, SimpleEnd, BoyerMoore>;

#endif // SEARCH_H
