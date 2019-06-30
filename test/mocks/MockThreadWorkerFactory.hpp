#pragma once

#include "IThreadWorkerFactory.hpp"
#include "gmock/gmock.h"

namespace thread_pool
{

struct MockThreadWorkerFactory : IThreadWorkerFactory
{
  MOCK_METHOD2(
    createWorkerThread,
    std::unique_ptr<IThreadWorker>(
      std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>> taskQueuePtr,
      std::shared_ptr<std::atomic_bool> stopPtr));
};

} // thread_pool
