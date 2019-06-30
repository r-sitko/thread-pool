#pragma once

#include "ThreadTask.hpp"
#include "IConcurrentQueue.hpp"
#include <future>
#include <type_traits>
#include <functional>
#include <exception>

namespace thread_pool
{

template <typename Fun, typename... Args>
decltype(auto) FixedThreadPool::enqueue(Fun&& fun, Args&&... args)
{
  if (*m_stopPtr)
  {
    throw std::runtime_error("Can't enqueue job, because FixedThreadPool is stopped.");
  }

  using returnType = std::result_of_t<Fun(Args...)>;
  using packagedTaskType = std::packaged_task<returnType()>;

  auto packagedTask = std::packaged_task<returnType()>(
    std::bind(std::forward<Fun>(fun), std::forward<Args>(args)...));

  auto taskResult = packagedTask.get_future();
  m_taskQueuePtr->push(std::make_unique<ThreadTask<packagedTaskType>>(std::move(packagedTask)));
  return taskResult;
}

} // thread_pool
