#ifndef TESTSETFILTER_H
#define TESTSETFILTER_H

#include <gtest/gtest.h>
#include "clogreader.h"
class MyCLogReader : public CLogReader
{
public:
    Search* getFilters()
    {
        return filters;
    }
    int getFiltersLength()
    {
        return filtersLength;
    }
};


class TestSetFilter: public ::testing::Test
{
public:
    MyCLogReader reader;
};

#endif // TESTSETFILTER_H
