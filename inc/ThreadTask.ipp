#pragma once

namespace thread_pool
{

template <typename T>
ThreadTask<T>::ThreadTask(T&& task) :
  m_task{std::move(task)}
{

}

template <typename T>
ThreadTask<T>::ThreadTask(T& task) :
  m_task{task}
{

}

template <typename T>
void ThreadTask<T>::run()
{
  m_task();
}

} // thread_pool
