FROM ubuntu:latest


RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    git \
    vim

WORKDIR /app

COPY . .

RUN /app/scripts/build.sh

CMD ["/app/bin/Scheduling"]
