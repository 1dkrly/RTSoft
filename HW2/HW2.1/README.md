sudo docker build . -t 1dkrly/test-example
xhost +
sudo docker run -e DISPLAY=unix$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix 1dkrly/test-example
xhost -
