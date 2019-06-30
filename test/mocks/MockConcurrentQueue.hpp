#pragma once

#include "IConcurrentQueue.hpp"
#include "gmock/gmock.h"

namespace thread_pool
{

template <typename T>
struct MockConcurrentQueue : IConcurrentQueue<T>
{
  MOCK_METHOD1_T(pop, bool(T& item));
  MOCK_METHOD1_T(push, void(T item));
  MOCK_METHOD0_T(clear, void());
  MOCK_METHOD0_T(stop, void());
  MOCK_CONST_METHOD0_T(empty, bool());
  MOCK_CONST_METHOD0_T(size, size_t());
};

} // thread_pool
