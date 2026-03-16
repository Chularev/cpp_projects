#include "testsetfilter.h"


TEST_F(TestSetFilter, FiltersChain) {
    reader.SetFilter("hsdfghjkl");

    EXPECT_EQ(1, reader.getFiltersLength());

    Search* filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<Equal>(filters[0]));

    //=====================================================
    reader.SetFilter("*hsdfghjkl");

    EXPECT_EQ(1, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<SimpleEnd>(filters[0]));


    //=====================================================
    reader.SetFilter("hsdfghjkl*");

    EXPECT_EQ(1, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<SimpleStart>(filters[0]));

    //=====================================================
    reader.SetFilter("hsdfghjkl*zxcvbhjk");

    EXPECT_EQ(2, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<SimpleStart>(filters[0]));
    EXPECT_TRUE(std::holds_alternative<SimpleEnd>(filters[1]));

    //=====================================================
    reader.SetFilter("*hsdfghjkl*");

    EXPECT_EQ(1, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[0]));


    //=====================================================
    reader.SetFilter("hsdfghjkl*zxcvbhjk*");

    EXPECT_EQ(2, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<SimpleStart>(filters[0]));
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[1]));

    //=====================================================
    reader.SetFilter("*hsdfghjkl*zxcvbhjk");

    EXPECT_EQ(2, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<SimpleEnd>(filters[0]));
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[1]));

    //=====================================================
    reader.SetFilter("*hsdfghjkl*zxcvbhjk*vbnm*");

    EXPECT_EQ(3, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[0]));
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[1]));
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[2]));

    //=====================================================
    reader.SetFilter("hsdfghjkl*zxcvbhjk*vbnm");

    EXPECT_EQ(3, reader.getFiltersLength());

    filters = reader.getFilters();
    EXPECT_TRUE(std::holds_alternative<SimpleStart>(filters[0]));
    EXPECT_TRUE(std::holds_alternative<SimpleEnd>(filters[1]));
    EXPECT_TRUE(std::holds_alternative<BoyerMoore>(filters[2]));
}
