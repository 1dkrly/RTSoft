1. docker build -t 1dkrly/ss2019
2. docker build -t 1dkrly/test-example .
3. xhost +
4. docker run -e DISPLAY=unix$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix 1dkrly/test-example
5. xhost -
