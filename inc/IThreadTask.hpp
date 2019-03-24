#pragma once

namespace thread_pool
{

struct IThreadTask
{
  virtual ~IThreadTask() = default;
  IThreadTask(const IThreadTask&) = default;
  IThreadTask(IThreadTask&&) = default;
  IThreadTask& operator=(const IThreadTask&) = default;
  IThreadTask& operator=(IThreadTask&&) = default;

  virtual void run() = 0;

protected:
  IThreadTask() = default;
};

} // thread_pool