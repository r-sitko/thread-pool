#pragma once

#include "IThreadWorker.hpp"
#include "gmock/gmock.h"

namespace thread_pool
{

struct MockThreadWorker : IThreadWorker
{
  MOCK_METHOD0(run, void());
};

} // thread_pool