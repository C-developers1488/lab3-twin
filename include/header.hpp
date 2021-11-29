// Copyright 2021 C-developers1488
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <cstddef>
#include <atomic>
#include <utility>

template <typename T>
class SharedPtr{
 public:
  std::atomic_size_t *refCounter = nullptr;
  T* elemPointer = nullptr;
  SharedPtr()
  {
    refCounter = new std::atomic_size_t(1);
  }
  explicit SharedPtr(T* ptr)
  {
    elemPointer = ptr;
    refCounter = new std::atomic_size_t(1);
  }
  SharedPtr(const SharedPtr& r)
  {
    *this = r;
  }
  SharedPtr(SharedPtr&& r)
  {
    *this = std::move(r);
  }
  ~SharedPtr()
  {
    if (!refCounter)
    {
      return;
    }
    if (--(*refCounter) == 0)
    {
      delete refCounter;
      delete elemPointer;
    }
  }
  auto operator=(const SharedPtr& r) -> SharedPtr&
  {
    if (this == &r)
    {
      return *this;
    }
    this->~SharedPtr();
    elemPointer = r.elemPointer;
    refCounter = r.refCounter;
    (*refCounter)++;
    return *this;
  }
  auto operator=(SharedPtr&& r) noexcept -> SharedPtr&
  {
    if (this == &r)
    {
      return *this;
    }
    this->~SharedPtr();
    elemPointer = r.elemPointer;
    refCounter = r.refCounter;
    r.refCounter = nullptr;
    r.elemPointer = nullptr;
    (*refCounter)++;
    return *this;
  }

  operator bool() const
  {
    if (elemPointer != nullptr)
    {
      return true;
    }else
    {
      return false;
    }
  }
  auto operator*() const -> T&
  {
    return *elemPointer;
  }
  auto operator->() const -> T*
  {
    return elemPointer;
  }

  auto get() -> T*
  {
    return elemPointer;
  }
  void reset()
  {
    *this = SharedPtr();
  }
  void reset(T* ptr)
  {
    *this = SharedPtr(ptr);
  }
  void swap(SharedPtr& r)
  {
    std::swap(refCounter, r.refCounter);
    std::swap(elemPointer, r.elemPointer);
  }
  auto use_count() const -> size_t
  {
    return *refCounter;
  };
};

#endif // INCLUDE_HEADER_HPP_

