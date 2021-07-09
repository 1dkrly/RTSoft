1. sudo docker build . -t 1dkrly/test-example
2. xhost +
3. sudo docker run -e DISPLAY=unix$DISPLAY -v /tmp/.X11-unix 1dkrly/test-example
4. xhost -
