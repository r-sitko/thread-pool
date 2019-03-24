#include "DefaultFixedThreadPool.hpp"
#include "gtest/gtest.h"
#include <future>
#include <thread>
#include <chrono>
#include <algorithm>

namespace
{
  using namespace thread_pool;
  using namespace ::testing;

  const std::chrono::high_resolution_clock::rep InaccuracyTimeMs = 50;
}

TEST(DefaultFixedThreadPoolTest, SameAmountOfTasksAsNumberOfWorkerThreads)
{
  auto fixedThreadPoolPtr = DefaultFixedThreadPool::create();

  const std::chrono::high_resolution_clock::rep SleepTimeMs = 5000;
  auto ExpectedTasksExecTimeMs = SleepTimeMs;
  auto workersNumber = std::thread::hardware_concurrency();
  auto testTask = [SleepTimeMs]
    {std::this_thread::sleep_for(std::chrono::milliseconds(SleepTimeMs));};

  std::vector<std::future<void>> futures;

  auto startTime = std::chrono::high_resolution_clock::now();
  for (uint32_t i = 0; i < workersNumber; ++i)
  {
    futures.push_back(fixedThreadPoolPtr->enqueue(testTask));
  }

  for (auto& future : futures)
  {
    future.get();
  }
  auto endTime = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diffTimes = endTime - startTime;
  std::chrono::milliseconds diffTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(diffTimes);

  ASSERT_EQ(diffTimeMs.count(),
    std::clamp(
      diffTimeMs.count(),
      ExpectedTasksExecTimeMs - InaccuracyTimeMs,
      ExpectedTasksExecTimeMs + InaccuracyTimeMs));
}