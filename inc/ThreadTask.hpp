#pragma once

#include "IThreadTask.hpp"
#include <utility>

namespace thread_pool
{

template <typename T>
class ThreadTask final : public IThreadTask
{
public:
  explicit ThreadTask(T&& task);
  explicit ThreadTask(T& task);
  ~ThreadTask() = default;
  ThreadTask(const ThreadTask&) = delete;
  ThreadTask(ThreadTask&&) = delete;
  ThreadTask& operator=(const ThreadTask&) = delete;
  ThreadTask& operator=(ThreadTask&&) = delete;

  void run() override;

private:
  T m_task;
};

} // thread_pool

#include "ThreadTask.ipp"