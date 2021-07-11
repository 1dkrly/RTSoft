  
FROM ss2019
RUN apt-get update && apt-get upgrade
COPY ./main1.cpp /usr/src
COPY ./test_video.mp4 /usr/src
WORKDIR /usr/src
RUN g++ main1.cpp -o output `pkg-config --cflags --libs opencv` && \
echo /usr/local/lib>/etc/ld.so.conf.d/opencv.conf && \
ldconfig -v
CMD ./output
