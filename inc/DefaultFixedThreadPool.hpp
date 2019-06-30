#pragma once

#include "FixedThreadPool.hpp"
#include <cstdint>
#include <thread>
#include <atomic>

namespace thread_pool
{

struct DefaultFixedThreadPool final
{
  virtual ~DefaultFixedThreadPool() = delete;
  DefaultFixedThreadPool() = delete;
  DefaultFixedThreadPool(const DefaultFixedThreadPool&) = delete;
  DefaultFixedThreadPool(DefaultFixedThreadPool&&) = delete;
  DefaultFixedThreadPool& operator=(const DefaultFixedThreadPool&) = delete;
  DefaultFixedThreadPool& operator=(DefaultFixedThreadPool&&) = delete;

  static std::unique_ptr<FixedThreadPool> create();
};

} // thread_pool
