#include "ThreadWorker.hpp"

namespace thread_pool
{

ThreadWorker::ThreadWorker(
  const std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>>& taskQueuePtr,
  const std::shared_ptr<std::atomic_bool>& stopPtr) :
  m_taskQueuePtr{taskQueuePtr},
  m_stopPtr{stopPtr},
  m_thread{}
{
}

ThreadWorker::~ThreadWorker()
{
  if (m_thread.joinable())
  {
    m_thread.join();
  }
}

void ThreadWorker::run()
{
  m_thread = std::thread(&ThreadWorker::mainLoop, this);
}

void ThreadWorker::mainLoop()
{
  while (!*m_stopPtr)
  {
    std::unique_ptr<IThreadTask> taskPtr{nullptr};
    if(m_taskQueuePtr->pop(taskPtr))
    {
      if (taskPtr)
      {
        taskPtr->run();
      }
    }
  }
}

} // thread_pool
