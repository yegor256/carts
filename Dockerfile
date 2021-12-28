FROM ubuntu:20.04
MAINTAINER Yegor Bugayenko <yegor256@gmail.com>
WORKDIR /tmp

RUN apt update -y
RUN apt install -y build-essential

COPY . /tmp
RUN cd /tmp
RUN make
ENTRYPOINT ["/tmp/objects"]
