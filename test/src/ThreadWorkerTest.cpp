#include "MockThreadTask.hpp"
#include "MockConcurrentQueue.hpp"
#include "ThreadWorker.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <queue>
#include <atomic>
#include <memory>

namespace
{
  using namespace thread_pool;
  using namespace ::testing;
}

class ThreadWorkerTest : public Test
{
protected:
  void SetUp() override
  {
      mockTaskQueuePtr = std::make_shared<
        NiceMock<MockConcurrentQueue<std::unique_ptr<IThreadTask>>>>();
      stopPtr = std::make_shared<std::atomic_bool>();

      threadWorkerPtr = std::make_unique<ThreadWorker>(mockTaskQueuePtr, stopPtr);
  }

  std::shared_ptr<MockConcurrentQueue<std::unique_ptr<IThreadTask>>> mockTaskQueuePtr;
  std::shared_ptr<std::atomic_bool> stopPtr;
  std::unique_ptr<ThreadWorker> threadWorkerPtr;
};

TEST_F(ThreadWorkerTest, ExitWhenStopIsSetToTrue)
{
  *stopPtr = true;
  threadWorkerPtr->run();
}

TEST_F(ThreadWorkerTest, RunJobWhenStopIsSetToFalseAndQueueReturnsNotEmptyTask)
{
  *stopPtr = false;
  auto mockTaskPtr = std::make_unique<StrictMock<MockThreadTask>>();
  auto mockTaskPtr2 = std::make_unique<StrictMock<MockThreadTask>>();
  EXPECT_CALL(*mockTaskPtr, run()).WillOnce(Return());
  EXPECT_CALL(*mockTaskPtr2, run()).WillOnce(Return());
  EXPECT_CALL(*mockTaskQueuePtr, pop(_))
    .WillOnce(
        DoAll(
          Invoke(
            [&mockTaskPtr](auto& item)
            {item = std::move(mockTaskPtr);}),
          Return(true)))
    .WillOnce(
      DoAll(
        Invoke(
          [&](auto& item)
          {item = std::move(mockTaskPtr2);}),
        Assign(stopPtr.get(), true),
        Return(true)));

  threadWorkerPtr->run();
  threadWorkerPtr.reset();
}
