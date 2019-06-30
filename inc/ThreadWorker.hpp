#pragma once

#include "IThreadWorker.hpp"
#include "ThreadTask.hpp"
#include "ConcurrentQueue.hpp"
#include <memory>
#include <atomic>
#include <thread>

namespace thread_pool
{

class ThreadWorker final : public IThreadWorker
{
public:
  explicit ThreadWorker(
    const std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>>& taskQueuePtr,
    const std::shared_ptr<std::atomic_bool>& stopPtr);
  ~ThreadWorker();
  ThreadWorker(const ThreadWorker&) = delete;
  ThreadWorker(ThreadWorker&&) = delete;
  ThreadWorker& operator=(const ThreadWorker&) = delete;
  ThreadWorker& operator=(ThreadWorker&&) = delete;

  void run() override;

private:
  void mainLoop();

  std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>> m_taskQueuePtr;
  std::shared_ptr<std::atomic_bool> m_stopPtr;
  std::thread m_thread;
};

} // thread_pool
