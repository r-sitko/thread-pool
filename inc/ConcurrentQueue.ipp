#pragma once

namespace thread_pool
{

template <typename T>
bool ConcurrentQueue<T>::pop(T& item)
{
  std::unique_lock<std::mutex> lock{m_mutex};

  if (m_itemQueue.empty())
  {
    m_cv.wait(lock, [this]{return !m_itemQueue.empty() || m_stop;});
  }

  if (!m_stop)
  {
    item = std::move(m_itemQueue.front());
    m_itemQueue.pop();
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
void ConcurrentQueue<T>::push(T item)
{
  {
    std::unique_lock<std::mutex> lock{m_mutex};
    m_itemQueue.push(std::move(item));
  }
  m_cv.notify_one();
}

template <typename T>
void ConcurrentQueue<T>::clear()
{
  std::unique_lock<std::mutex> lock{m_mutex};
  while (!m_itemQueue.empty())
  {
    m_itemQueue.pop();
  }
  m_cv.notify_all();
}

template <typename T>
void ConcurrentQueue<T>::stop()
{
  std::unique_lock<std::mutex> lock{m_mutex};
  m_stop = true;
  m_cv.notify_all();
}

template <typename T>
bool ConcurrentQueue<T>::empty() const
{
  std::unique_lock<std::mutex> lock{m_mutex};
  return m_itemQueue.empty();
}

template <typename T>
size_t ConcurrentQueue<T>::size() const
{
  std::unique_lock<std::mutex> lock{m_mutex};
  return m_itemQueue.size();
}

} // thread_pool