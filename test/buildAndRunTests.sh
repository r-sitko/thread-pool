#!/usr/bin/env bash
set -ex

TESTS_DIR=$(dirname $(readlink -f $0))
cd $TESTS_DIR
GIT_REPO_ROOT=$(git rev-parse --show-toplevel)

mkdir -p $GIT_REPO_ROOT/build/test
cd $GIT_REPO_ROOT/build/test
cmake ../.. -DENABLE_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
make
make check GTEST_COLOR=1
