docker build . --tag slam:latest --progress=plain
echo "xhost +local:docker" >> ~/.profile