FROM ubuntu:18.04

RUN apt-get -qq update && apt-get install --no-install-recommends -yq \
    build-essential \
    bison \
    cmake \
    flex \
    git \
    && \
    apt-get clean -y && \
    rm -rf /var/lib/apt/lists/*

ADD . /opt/midd-cool

WORKDIR /opt/midd-cool

ENV PATH="/opt/midd-cool/bin:${PATH}"
