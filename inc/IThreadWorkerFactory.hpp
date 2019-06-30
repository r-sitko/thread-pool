#pragma once

#include <memory>
#include <atomic>

namespace thread_pool
{

struct IThreadWorker;
template <typename T>
class IConcurrentQueue;

struct IThreadWorkerFactory
{
  virtual ~IThreadWorkerFactory() = default;
  IThreadWorkerFactory(const IThreadWorkerFactory&) = default;
  IThreadWorkerFactory(IThreadWorkerFactory&&) = default;
  IThreadWorkerFactory& operator=(const IThreadWorkerFactory&) = default;
  IThreadWorkerFactory& operator=(IThreadWorkerFactory&&) = default;

  virtual std::unique_ptr<IThreadWorker> createWorkerThread(
    std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>> taskQueuePtr,
    std::shared_ptr<std::atomic_bool> stopPtr) = 0;

protected:
  IThreadWorkerFactory() = default;
};

} // thread_pool
