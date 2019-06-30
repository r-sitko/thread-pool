#pragma once

#include <stddef.h>

namespace thread_pool
{

template <typename T>
class IConcurrentQueue
{
public:
  virtual ~IConcurrentQueue() = default;
  IConcurrentQueue(const IConcurrentQueue&) = default;
  IConcurrentQueue(IConcurrentQueue&&) = default;
  IConcurrentQueue& operator=(const IConcurrentQueue&) = default;
  IConcurrentQueue& operator=(IConcurrentQueue&&) = default;

  virtual bool pop(T& item) = 0;
  virtual void push(T item) = 0;
  virtual void clear() = 0;
  virtual void stop() = 0;
  virtual bool empty() const = 0;
  virtual size_t size() const = 0;

protected:
  IConcurrentQueue() = default;
};

} // thread_pool
