#include "clogreader.h"

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "there should be three arguments";
        return 1;
    }
    CLogReader reader;
    if(!reader.Open(argv[1]))
    {
        std::cerr << "Can not open file";
        return 2;
    }
    if (!reader.SetFilter(argv[2]))
    {
        std::cerr << "Can not set filter";
        return 3;
    }
    char buff[1000];
    while (reader.GetNextLine(buff,100))
    {
        std::cout << buff << std::endl;
    }
    return 0;
}
