mkdir rasp
cd rasp 
mkdir gcc && wget -O- https://releases.linaro.org/components/toolchain/binaries/latest-5.1/arm-linux-gnueabihf/gcc-linaro-5.1-2015.08-x86_64_arm-linux-gnueabihf.tar.xz | tar -x --xz -C gcc/ --strip-components=1
export PATH=$PATH:$PWD/gcc/bin
git clone -b rpi-4.5.y --single-branch --depth 1 https://github.com/raspberrypi/linux.git
git clone -b next --single-branch --depth 1 https://github.com/raspberrypi/firmware.git
cd linux
export LINVER=4.5
KERNEL=kernel
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcmrpi_defconfig -j 4
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules vmlinux dtbs -j 4
mkdir INSTALL && cd INSTALL && mkdir overlays && cd ..
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=$PWD/INSTALL modules_install
scripts/mkknlimg arch/arm/boot/zImage $PWD/$KERNEL.img
mv kernel.img INSTALL/kernel-$LINVER.img
cp arch/arm/boot/dts/*.dtb INSTALL/
cp arch/arm/boot/dts/overlays/*.dtb* INSTALL/overlays/
cp arch/arm/boot/dts/overlays/README INSTALL/overlays/
cd ..
mkdir INSTALL && cp -R linux/INSTALL/ .
cp -r -f firmware/boot/* INSTALL/
