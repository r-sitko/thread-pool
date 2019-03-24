#pragma once

#include "IThreadTask.hpp"
#include "gmock/gmock.h"

namespace thread_pool
{

struct MockThreadTask : IThreadTask
{
  MOCK_METHOD0(run, void());
};

} // thread_pool