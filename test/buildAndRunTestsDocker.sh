#!/usr/bin/env bash
set -ex

TESTS_DIR=$(dirname $(readlink -f $0))
cd $TESTS_DIR
GIT_REPO_ROOT=$(git rev-parse --show-toplevel)

docker build -t thread_pool_tests -f Dockerfile .
docker run --rm -v $GIT_REPO_ROOT:/build -w /build/test --name thread_pool_tests thread_pool_tests
