#include "rtklib.h"
#include "gtest/gtest.h"
#include "ver.h"

int showmsg(char* format, ...) { return 0; }
void settspan(gtime_t ts, gtime_t te) {}
void settime(gtime_t time) {}
TEST(Test1, TestTime) {
   printf("hello rtklibcpp. branch:%s,hash:%s\n", branch_name.c_str(), commit_hash.c_str());
   gtime_t t1; t1.time = 100; t1.sec = 0.1;
   gtime_t t2; t2.time = 89; t2.sec = 0.5;
   EXPECT_NEAR(t1 - t2, 10.6, 1e-6);
   t2 = t1 + 4.5;
   EXPECT_EQ(t2.time, 104);
   EXPECT_NEAR(t2.sec,0.6,1e-6);
}