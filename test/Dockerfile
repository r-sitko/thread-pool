FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
  build-essential \
  git \
  cmake \
  && rm -rf /var/lib/apt/lists/*

ENTRYPOINT ["./buildAndRunTests.sh"]
