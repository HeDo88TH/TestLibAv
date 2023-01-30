# Test compilation of program that requires libav*

## Native Windows Build
mkdr build-windows
cd build-windows
cmake ..
cmake --build . --config Release --target ALL_BUILD -- /maxcpucount:14


## Native Linux Build
apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libavfilter-dev \
    libavdevice-dev \
    libavutil-dev \
    pkg-config

mkdir build-linux
cd build-linux
cmake ..
make


## Docker Linux Build

### Build Docker Image
cd docker
docker build -t ffmpeg-build .

### Compile
docker run --rm -v ${PWD}:/data -it ffmpeg-build bash
cd /data
mkdir build-linux
cd build-linux
cmake ..
make