// Copyright 2021 C-developes1488

#include <gtest/gtest.h>

#include "header.hpp"

TEST(Shared_ptr, Empty_Conctruct) {
  SharedPtr<std::string> p;
  ASSERT_EQ(p.get(), nullptr);
}

TEST(Shared_ptr, Intialized_ptr) {
  SharedPtr<int> p(new int{3});
  ASSERT_EQ(*p, 3);
  ASSERT_EQ(p.use_count(), 1);
}

TEST(Shared_Ptr, Copy_Construct) {
  const SharedPtr<int> p(new int{10});
  SharedPtr<int> r(p);
  ASSERT_EQ(*r, 10);
  ASSERT_EQ(r.use_count(), 2);
}
TEST(Shared_Ptr, Move_Construct) {
  SharedPtr<int> p(new int{10});
  SharedPtr<int> r(std::move(p));
  ASSERT_EQ(*r, 10);
  ASSERT_EQ(r.use_count(), 1);
  ASSERT_EQ(p.get(), nullptr);
}
TEST(Shared_Ptr, Copy_Assyngment) {
  const SharedPtr<std::string> p(new std::string("Levonchik"));
  SharedPtr<std::string> r(p);
  ASSERT_EQ(*p, "Levonchik");
  ASSERT_EQ(*r, "Levonchik");
  ASSERT_EQ(p.use_count(), 2);
  ASSERT_EQ(r.use_count(), 2);
  SharedPtr<std::string> ptr(new std::string("Avakimyanc"));
  ASSERT_EQ(ptr.use_count(), 1);
  r = ptr;
  ASSERT_EQ(*r, "Avakimyanc");
  ASSERT_EQ(r.use_count(), 2);
  ASSERT_EQ(ptr.use_count(), 2);
  ASSERT_EQ(p.use_count(), 1);
}
TEST(Shared_Ptr, Move_Assyngment) {
  SharedPtr<std::string> r(new std::string{"PTR"});
  SharedPtr<std::string> p(r);
  ASSERT_EQ(*p, "PTR");
  ASSERT_EQ(p.use_count(), 2);
  ASSERT_EQ(r.use_count(), 2);

  SharedPtr<std::string> q(new std::string{"Shared"});
  SharedPtr<std::string> z(q);
  ASSERT_EQ(*z, "Shared");
  ASSERT_EQ(z.use_count(), 2);
  ASSERT_EQ(q.use_count(), 2);

  q = std::move(p);
  ASSERT_EQ(p.operator bool(), false);
  ASSERT_EQ(r.use_count(), 2);
  ASSERT_EQ(z.use_count(), 1);

  SharedPtr<std::string> *ptr_ = &q;
  q = std::move(*ptr_);
  ASSERT_EQ(*q, "PTR");
  ASSERT_EQ(q.use_count(), 2);
}
TEST(Shared_Ptr, reset) {
  SharedPtr<std::string> q(new std::string{"Scoped"});
  SharedPtr<std::string> z(q);
  q.reset();
  ASSERT_EQ(z.use_count(), 1);
  ASSERT_EQ(q.operator bool(), false);
}
TEST(Shared_Ptr, reset_by_ptr) {
  SharedPtr<std::string> q(new std::string{"Scoped"});
  ASSERT_EQ(*q, "Scoped");
  ASSERT_EQ(q.use_count(), 1);
  std::string *ptr = new std::string{"Unique"};
  ASSERT_EQ(*ptr, "Unique");
  q.reset(ptr);
  ASSERT_EQ(*q, "Unique");
  ASSERT_EQ(q.use_count(), 1);
}
TEST(Shared_Ptr, Swap) {
  SharedPtr<std::string> q(new std::string{"Scoped"});
  ASSERT_EQ(*q, "Scoped");
  ASSERT_EQ(q.use_count(), 1);
  SharedPtr<std::string> r(new std::string{"PTR"});
  ASSERT_EQ(*r, "PTR");
  ASSERT_EQ(r.use_count(), 1);
  swap(q, r);
  ASSERT_EQ(*r, "Scoped");
  ASSERT_EQ(r.use_count(), 1);
  ASSERT_EQ(*q, "PTR");
  ASSERT_EQ(q.use_count(), 1);
}
TEST(Shared_Ptr, equal_ptr) {
  SharedPtr<std::string> q(new std::string{"Scoped"});
  ASSERT_EQ(*q, "Scoped");
  ASSERT_EQ(q.use_count(), 1);
  q = q;
  ASSERT_EQ(*q, "Scoped");
  ASSERT_EQ(q.use_count(), 1);
}