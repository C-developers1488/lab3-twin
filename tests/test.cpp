// Copyright by C-developers1488

#include <gtest/gtest.h>
#include "header.hpp"

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}
TEST(Test, Zerro) {
  SharedPtr<int> sp;
  EXPECT_EQ((sp),0);
}
TEST(Test, UseCount) {
  int val = 5;
  SharedPtr<int> sp1 (&val);
  SharedPtr<int> sp2(sp1);
  SharedPtr<int> sp3(sp2);
  EXPECT_EQ(sp1.use_count(),3);
}
TEST(Test, Clas_Strelka) {
  class Values{
   public:
    int val;
  };
  Values val1;
  val1.val=20;
  SharedPtr<Values> sp5(&val1);
  EXPECT_EQ(sp5->val,20);
}
TEST(Test, Zvezda) {
  int val = 5, val2 = 30;
  SharedPtr<int> sp1 (&val);
  SharedPtr<int> sp2(sp1);
  SharedPtr<int> sp3(sp2);
  SharedPtr<int> spoz(&val2);
  std::stringstream str;
  str<<*sp1<<" "<<*sp2<<" "<<*sp3<<" "<<*spoz;
  std::string stroka = "5 5 5 30";
  EXPECT_EQ(str.str(), stroka);
}
TEST(Test, Get) {
  int val = 5, val2 = 30;
  SharedPtr<int> sp1 (&val);
  SharedPtr<int> sp2(sp1);
  SharedPtr<int> sp3(sp2);
  SharedPtr<int> spoz(&val2);
  std::stringstream str, str2;
  str<<*sp1.get()<<" "<<*sp2.get()<<" "<<*sp3.get()<<" "<<*spoz.get();
  std::string stroka = "5 5 5 30";
  EXPECT_EQ(str.str(), stroka);
}
TEST(Test, Reset) {
  int val = 5, val2 =30;
  SharedPtr<int> sp1 (&val);
  SharedPtr<int> sp2(sp1);
  SharedPtr<int> sp3(sp2);
  sp1.reset();
  sp2.reset(&val2);
  std::stringstream str;
  str<<(sp1)<<" "<<*sp2;
  std::string stroka = "0 30";
  EXPECT_EQ(str.str(), stroka);
}
TEST(Test, Swap) {
  int val = 5, val2 = 30;
  SharedPtr<int> sp1 (&val);
  SharedPtr<int> sp2(sp1);
  SharedPtr<int> sp3(sp2);
  SharedPtr<int> spoz(&val2);
  std::stringstream str;
  str<<*sp3<<" "<<*spoz;
  sp3.swap(spoz);
  str<<" "<<*sp3<<" "<<*spoz;
  std::string stroka = "5 30 30 5";
  EXPECT_EQ(str.str(), stroka);
}