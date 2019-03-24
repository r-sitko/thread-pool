#pragma once

#include <memory>
#include <future>
#include <type_traits>
#include <vector>
#include <atomic>

namespace thread_pool
{

struct IThreadWorker;
struct IThreadTask;
struct IThreadWorkerFactory;
template <typename T>
struct IConcurrentQueue;

class FixedThreadPool final
{
public:
  using TaskPtrType = std::unique_ptr<IThreadTask>;
  using TaskQueueType = IConcurrentQueue<TaskPtrType>;
  explicit FixedThreadPool(
    const std::shared_ptr<TaskQueueType>& taskQueuePtr,
    const std::shared_ptr<IThreadWorkerFactory>& workerFactoryPtr,
    const std::shared_ptr<std::atomic_bool>& stopPtr,
    const uint32_t threadsNumber);
  ~FixedThreadPool();
  FixedThreadPool(const FixedThreadPool&) = delete;
  FixedThreadPool(FixedThreadPool&&) = delete;
  FixedThreadPool& operator=(const FixedThreadPool&) = delete;
  FixedThreadPool& operator=(FixedThreadPool&&) = delete;

  template <typename Fun, typename... Args>
  decltype(auto) enqueue(Fun&& fun, Args&&... args);

private:
  void stop();

  std::shared_ptr<TaskQueueType> m_taskQueuePtr;
  std::shared_ptr<IThreadWorkerFactory> m_workerFactoryPtr;
  std::shared_ptr<std::atomic_bool> m_stopPtr;
  std::vector<std::unique_ptr<IThreadWorker>> m_workers;
};

} // thread_pool

#include "FixedThreadPool.ipp"