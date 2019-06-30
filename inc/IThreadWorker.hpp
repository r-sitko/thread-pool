#pragma once

namespace thread_pool
{

struct IThreadWorker
{
  virtual ~IThreadWorker() = default;
  IThreadWorker(const IThreadWorker&) = default;
  IThreadWorker(IThreadWorker&&) = default;
  IThreadWorker& operator=(const IThreadWorker&) = default;
  IThreadWorker& operator=(IThreadWorker&&) = default;

  virtual void run() = 0;

protected:
  IThreadWorker() = default;
};

} // thread_pool
