#include "testclogreader.h"
#include "clogreader.h"

TEST(TestCLogReader, Search) {
    CLogReader reader;
    EXPECT_TRUE(reader.Open("../data/testfile.txt"));
    reader.SetFilter("*BIOS-e820*");

    char buf[400];
    EXPECT_TRUE(reader.GetNextLine(buf,400));

    std::string tmp = "Jul 19 11:01:17 alex-Nitro-AN517-54 kernel: BIOS-e820: [mem 0x0000000000000000-0x000000000009efff] usable";
    EXPECT_EQ(std::string(buf), tmp);

    //==============================================
    EXPECT_TRUE(reader.GetNextLine(buf,400));
    tmp = "Jul 19 11:01:17 alex-Nitro-AN517-54 kernel: BIOS-e820: [mem 0x000000000009f000-0x00000000000fffff] reserved";
    EXPECT_EQ(std::string(buf), tmp);
    //================================================
    reader.SetFilter("Jul 19 11:01:17 alex-Nitro-AN517-54 kernel: APIC: Static calls initialized");
    EXPECT_TRUE(reader.GetNextLine(buf,400));
    tmp = "Jul 19 11:01:17 alex-Nitro-AN517-54 kernel: APIC: Static calls initialized";
    EXPECT_EQ(std::string(buf), tmp);

    //=======================================
    reader.SetFilter("Jul 19 11:01:37*gdm-x-session[2215]*4?\"");
    EXPECT_TRUE(reader.GetNextLine(buf,400));
    tmp = "Jul 19 11:01:37 alex-Nitro-AN517-54 /usr/libexec/gdm-x-session[2215]: (**) Option \"fd\" \"40\"";
    EXPECT_EQ(std::string(buf), tmp);

    //==============================================================
    EXPECT_TRUE(reader.GetNextLine(buf,400));
    tmp = "Jul 19 11:01:37 alex-Nitro-AN517-54 /usr/libexec/gdm-x-session[2215]: (**) Option \"fd\" \"43\"";
    EXPECT_EQ(std::string(buf), tmp);

}
TEST(TestCLogReader, Safety)
{
    CLogReader reader;
    EXPECT_TRUE(reader.Open("../data/testfile.txt"));


}
