#include "rtklib.h"
#include "gtest/gtest.h"
#include "ver.h"

int showmsg(char* format, ...) { return 0; }
void settspan(gtime_t ts, gtime_t te) {}
void settime(gtime_t time) {}
TEST(Test1, TestTime) {
   printf("hello rtklibcpp. branch:%s,hash:%s\n", branch_name.c_str(), commit_hash.c_str());
   EXPECT_TRUE(1);
}