#include "ConcurrentQueue.hpp"
#include "gtest/gtest.h"
#include <memory>
#include <vector>

namespace
{
  using namespace thread_pool;
  using namespace ::testing;
}

class ConcurrentQueueTest : public Test
{
protected:
  using ItemType = std::unique_ptr<int>;

  void addItemToQueue(int value)
  {
    auto item = std::make_unique<int>(value);
    m_queue.push(std::move(item));
  }

  ConcurrentQueue<ItemType> m_queue;
};

TEST_F(ConcurrentQueueTest, PushItemsAndPop)
{
  addItemToQueue(3);
  addItemToQueue(15);
  addItemToQueue(1);

  ASSERT_FALSE(m_queue.empty());
  ASSERT_EQ(m_queue.size(), 3u);

  ItemType item;
  ASSERT_TRUE(m_queue.pop(item));
  ASSERT_TRUE(item);
  ASSERT_EQ(*item, 3);
  ASSERT_TRUE(m_queue.pop(item));
  ASSERT_TRUE(item);
  ASSERT_EQ(*item, 15);
  ASSERT_TRUE(m_queue.pop(item));
  ASSERT_TRUE(item);
  ASSERT_EQ(*item, 1);

  ASSERT_TRUE(m_queue.empty());
  ASSERT_EQ(m_queue.size(), 0u);
}

TEST_F(ConcurrentQueueTest, TryPopItemOnStoppedEmptyQueue)
{
  ASSERT_TRUE(m_queue.empty());
  ASSERT_EQ(m_queue.size(), 0u);

  ItemType item;
  m_queue.stop();
  ASSERT_FALSE(m_queue.pop(item));
  ASSERT_FALSE(item);
}