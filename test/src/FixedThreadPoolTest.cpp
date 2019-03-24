#include "IThreadTask.hpp"
#include "IConcurrentQueue.hpp"
#include "MockThreadWorker.hpp"
#include "FixedThreadPool.hpp"
#include "MockConcurrentQueue.hpp"
#include "MockThreadWorkerFactory.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <queue>
#include <atomic>
#include <memory>
#include <vector>

namespace
{
  using namespace thread_pool;
  using namespace ::testing;
}

TEST(FixedThreadPoolTest, CreateThreadPoolAndEnqueueTasks)
{
  auto m_mockTaskQueuePtr = std::make_shared<
    StrictMock<MockConcurrentQueue<std::unique_ptr<IThreadTask>>>>();
  auto m_mockWorkerFactoryPtr = std::make_shared<
    StrictMock<MockThreadWorkerFactory>>();
  auto m_stopPtr = std::make_shared<std::atomic_bool>();

  auto workerPtr = std::make_unique<StrictMock<MockThreadWorker>>();
  auto workerPtr2 =  std::make_unique<StrictMock<MockThreadWorker>>();
  EXPECT_CALL(*workerPtr, run());
  EXPECT_CALL(*workerPtr2, run());

  EXPECT_CALL(
    *m_mockWorkerFactoryPtr,
    createWorkerThread(
      AllOf(
        NotNull(),
        SafeMatcherCast<std::shared_ptr<IConcurrentQueue<std::unique_ptr<IThreadTask>>>>(m_mockTaskQueuePtr)),
      m_stopPtr))
      .Times(2)
      .WillOnce(Return(ByMove(std::move(workerPtr))))
      .WillOnce(Return(ByMove(std::move(workerPtr2))));

  auto threadPoolPtr = std::make_unique<FixedThreadPool>(
    m_mockTaskQueuePtr,
    m_mockWorkerFactoryPtr,
    m_stopPtr,
    2);

  EXPECT_CALL(*m_mockTaskQueuePtr, push(_))
    .Times(2)
    .WillRepeatedly([](auto taskPtr){taskPtr->run();});
  auto testTask = [](int x){return x;};
  auto result = threadPoolPtr->enqueue(testTask, 10);
  ASSERT_EQ(result.get(), 10);

  auto testTask2 = [](int x){return x;};
  auto result2 = threadPoolPtr->enqueue(testTask2, 20);
  ASSERT_EQ(result2.get(), 20);

  EXPECT_CALL(*m_mockTaskQueuePtr, stop());
  threadPoolPtr.reset();
  ASSERT_TRUE(*m_stopPtr);
}