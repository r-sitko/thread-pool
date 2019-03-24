#include "ThreadTask.hpp"
#include "gtest/gtest.h"
#include <future>

namespace
{
  using namespace thread_pool;
  using namespace ::testing;
}

TEST(ThreadTaskTest, RunPackagedTask)
{
  auto task = []{return 5;};
  std::packaged_task<int()> packTask(std::move(task));
  auto result = packTask.get_future();
  ThreadTask<decltype(packTask)> threadTask(std::move(packTask));
  threadTask.run();
  ASSERT_EQ(result.get(), 5);
}



