FROM ubuntu:latest
FROM gcc:11
RUN apt-get update && apt-get install -yq cmake libopencv-dev
COPY . /usr/src/2/2.2
WORKDIR /usr/src/2/2.2
RUN mkdir build && cd build ** cmake ,, && make
CMD ./output
