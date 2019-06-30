#pragma once

#include "IThreadWorkerFactory.hpp"
#include "ThreadWorker.hpp"

namespace thread_pool
{

class ThreadWorkerFactory : public IThreadWorkerFactory
{
public:
  ThreadWorkerFactory() = default;
  ~ThreadWorkerFactory() = default;
  ThreadWorkerFactory(const ThreadWorkerFactory&) = delete;
  ThreadWorkerFactory(ThreadWorkerFactory&&) = delete;
  ThreadWorkerFactory& operator=(const ThreadWorkerFactory&) = delete;
  ThreadWorkerFactory& operator=(ThreadWorkerFactory&&) = delete;

  std::unique_ptr<IThreadWorker> createWorkerThread(
    std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>> taskQueuePtr,
    std::shared_ptr<std::atomic_bool> stopPtr) override
  {
    return std::make_unique<ThreadWorker>(taskQueuePtr, stopPtr);
  }
};

} // thread_pool
