#pragma once

#include "IConcurrentQueue.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace thread_pool
{

template <typename T>
class ConcurrentQueue final : public IConcurrentQueue<T>
{
public:
  ConcurrentQueue() = default;
  ~ConcurrentQueue() = default;
  ConcurrentQueue(const ConcurrentQueue&) = delete;
  ConcurrentQueue(ConcurrentQueue&&) = delete;
  ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
  ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;

  bool pop(T& item) override;
  void push(T item) override;
  void clear() override;
  void stop() override;
  bool empty() const override;
  size_t size() const override;

private:
  std::queue<T> m_itemQueue;
  mutable std::mutex m_mutex;
  std::condition_variable m_cv;
  std::atomic_bool m_stop {false};
};

} // thread_pool

#include "ConcurrentQueue.ipp"