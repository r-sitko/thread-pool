#include "DefaultFixedThreadPool.hpp"
#include "ConcurrentQueue.hpp"
#include "ThreadWorkerFactory.hpp"

namespace thread_pool
{

std::unique_ptr<FixedThreadPool> DefaultFixedThreadPool::create()
{
  auto taskQueuePtr =
    std::make_shared<ConcurrentQueue<std::unique_ptr<IThreadTask>>>();
  auto stopPtr =
    std::make_shared<std::atomic_bool>(false);
  auto workerFactory = std::make_shared<ThreadWorkerFactory>();
  const auto maxWorkersThreads = std::thread::hardware_concurrency();

  return std::make_unique<FixedThreadPool>(
    taskQueuePtr,
    workerFactory,
    stopPtr,
    maxWorkersThreads);
}

} // thread_pool