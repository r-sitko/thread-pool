#include "FixedThreadPool.hpp"
#include "IThreadWorker.hpp"
#include "IThreadWorkerFactory.hpp"
#include <cassert>

namespace thread_pool
{

FixedThreadPool::FixedThreadPool(
  const std::shared_ptr<TaskQueueType>& taskQueuePtr,
  const std::shared_ptr<IThreadWorkerFactory>& workerFactoryPtr,
  const std::shared_ptr<std::atomic_bool>& stopPtr,
  const uint32_t threadsNumber) :
  m_taskQueuePtr{taskQueuePtr},
  m_workerFactoryPtr{workerFactoryPtr},
  m_stopPtr{stopPtr}
{
  assert(threadsNumber > 0);

  for (uint32_t i = 0; i < threadsNumber; ++i)
  {
    m_workers.push_back(
      m_workerFactoryPtr->createWorkerThread(m_taskQueuePtr, m_stopPtr));
  }

  for (auto& worker : m_workers)
  {
    worker->run();
  }
}

FixedThreadPool::~FixedThreadPool()
{
  stop();
}

void FixedThreadPool::stop()
{
  *m_stopPtr = true;
  m_taskQueuePtr->stop();
  m_workers.clear();
}

} // thread_pool
