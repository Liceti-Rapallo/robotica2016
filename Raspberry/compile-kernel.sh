#!/bin/bash    
# CONFIG
KERNEL_URL=https://cdn.kernel.org/pub/linux/kernel/v4.x/testing/linux-4.5-rc5.tar.xz
KERNEL_DIR=/home
# DOWNLOAD AND EXTRACT
wget $KERNEL_URL
tar -xzf *.xz
rm -f *.xz
cd linux-*
# MAKE CONFIG
cat /proc/config.gz | gunzip > .config
make clean
make silentoldconfig
# COMPILE
make-kpkg -j 4 kernel_image
cd ..
dpkg -i *.deb
