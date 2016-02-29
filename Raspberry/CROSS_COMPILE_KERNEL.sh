mkdir rasp
cd rasp 
mkdir gcc && wget -O- https://releases.linaro.org/components/toolchain/binaries/latest-5.1/arm-linux-gnueabihf/gcc-linaro-5.1-2015.08-x86_64_arm-linux-gnueabihf.tar.xz | tar -x --xz -C gcc/ --strip-components=1
export PATH=$PATH:$PWD/gcc/bin
git clone -b rpi-4.5.y --single-branch --depth 1 https://github.com/raspberrypi/linux.git
cd linux
KERNEL=kernel
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcmrpi_defconfig -j 4
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs -j 4
