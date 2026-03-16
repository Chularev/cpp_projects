#include "clogreader.h"

#include <string.h>
#include <iostream>

#include <fcntl.h>
#include <unistd.h>

bool CLogReader::MoveToNextLine()
{
    line_start = ++line_end;
    while (line_end < data + data_size) {
        if (*line_end == '\n') {
            return true;
        }
        line_end++;
    }
    // Last line
    if (line_start < data + data_size)
        return true;
    return false;
}

CLogReader::CLogReader()
{
}

CLogReader::~CLogReader()
{
    Close();
}

bool CLogReader::Open(const char *filePath)
{
    fileDescriptor = open(filePath, O_RDONLY);
    if (fileDescriptor == -1) {
        std::cerr << "Can not open file" << std::endl;
        return false;
    }

    if (fstat(fileDescriptor, &sb) == -1) {
        std::cerr << "Can not get file info" << std::endl;
        close(fileDescriptor);
        return false;
    }

    void *data_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fileDescriptor, 0);
    data = static_cast<char*>(data_ptr);
    if (data == MAP_FAILED) {
        std::cerr << "Can not map data to memory" << std::endl;
        close(fileDescriptor);
        return false;
    }

    line_end = data - 1;
    data_size = sb.st_size;

    return true;
}
void  CLogReader::Close()
{
    if (data != MAP_FAILED)
    {
        munmap(data, sb.st_size);
        data = static_cast<char*>(MAP_FAILED);
    }

    if (fileDescriptor != -1)
    {
        close(fileDescriptor);
        fileDescriptor = -1;
    }
}

void CLogReader::FillFilters(bool startsWithStar, bool endsWithStar, char* subFilters[], int size)
{
    if (size == 1 && !startsWithStar && !endsWithStar)
    {
        filters[filtersLength++] = Equal(subFilters[0]);
        return;
    }
    int index = 0;
    if (!startsWithStar)
    {
        filters[filtersLength++] = SimpleStart(subFilters[index++]);
    }
    if (!endsWithStar)
    {
        filters[filtersLength++] = SimpleEnd(subFilters[--size]);
    }

    for (; index < size; index++)
    {
        filters[filtersLength++] = BoyerMoore(subFilters[index]);
    }


}

bool CLogReader::SetFilter(const char *filter)
{
    if (!filter)
    {
        std::cerr << "Filter can not be empty" << std::endl;
        return false;
    }
    int filterLength = strlen(filter);
    if (filterLength > 100)
    {
        std::cerr << "Filter length must be less than 100";
        return false;
    }

    char filter_copy[100];
    snprintf(filter_copy, sizeof(filter_copy), "%s", filter);

    filtersLength = 0;

    bool startsWithStar = (filter[0] == '*');
    bool endsWithStar = (filter[strlen(filter) - 1] == '*');

    char* subFilters[10];
    int index = 0;

    subFilters[index] = strtok (filter_copy,"*");

    while (subFilters[index] != NULL)
    {
        if (++index == 10)
        {
            std::cerr << "Error: filter can not have more than 10 asterisk"  << "\n";
            return false;
        }
        else
            subFilters[index] = strtok (NULL, "*");
    }

    FillFilters(startsWithStar, endsWithStar, subFilters, index);
    return true;
}
bool CLogReader::GetNextLineTest(int bufsize, char *buf)
{
    if (fileDescriptor < 0)
    {
        std::cerr << "File with data do not open yet";
        return false;
    }
    if (filtersLength < 0)
    {
        std::cerr << "Filter do not set yet";
        return false;
    }
    if (bufsize < 1)
    {
        std::cerr << "Buffer size must be more than 0";
        return false;
    }
    if (buf == nullptr)
    {
        std::cerr << "Buffer can not be null";
        return false;
    }
    return true;
}
bool CLogReader::GetNextLine(char *buf, const int bufsize)
{
    if (!GetNextLineTest(bufsize, buf))
        return false;

    while (MoveToNextLine())
    {
        // if search will be success it will be reduce
        int lineLength = line_end - line_start;
        char *line = line_start;

        int i = 0;
        for (; i < filtersLength; i++)
        {
            if (!std::visit([&](auto&& arg) {
                    return arg.search(&line,lineLength);
                }, filters[i]))
            {
                break;
            }
        }
        if (i == filtersLength)
        {
            memset(buf, 0, bufsize);
            lineLength = line_end - line_start;
            int min = std::min(bufsize, lineLength);
            strncpy(buf,line_start, min);
            return true;
        }

    }
    return false;
}
