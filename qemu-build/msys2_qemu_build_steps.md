# Win11本地构建QEMU二进制文件步骤

## 安装 MSYS2
安装：qemu-packs/msys2-x86_64-20240113.exe
最新版本请在以下万盏寻找（这里以：msys2-x86_64-20240113.exe 文件为例）：
https://www.msys2.org/中，下载：msys2-x86_64-20240113.exe 
链接：https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe

## 配置 MSYS2 源：
进入安装目录：C:\msys64\etc\pacman.d （这里安装目录以：C:\msys64 为例）
在文件mirrorlist.msys的前面插入： Server = http://mirrors.ustc.edu.cn/msys2/msys/$arch
在文件mirrorlist.mingw32的前面插入： Server = http://mirrors.ustc.edu.cn/msys2/mingw/i686
在文件mirrorlist.mingw64的前面插入： Server = http://mirrors.ustc.edu.cn/msys2/mingw/x86_64

## 管理员权限打开终端
MSYS2 MINGW64

## 安装 MSYS2 需要安装的依赖库
pacman -Syu
pacman -Su

pacman -S base-devel mingw-w64-x86_64-toolchain git python ninja
pacman -S mingw-w64-x86_64-glib2 mingw-w64-x86_64-pixman python-setuptools
pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-SDL2 mingw-w64-x86_64-libslirp

pacman -Sy mingw-w64-x86_64-meson mingw-w64-x86_64-ninja \
           mingw-w64-x86_64-python \
           mingw-w64-x86_64-python-sphinx \
           mingw-w64-x86_64-python-sphinx_rtd_theme \
           mingw-w64-x86_64-autotools \
           mingw-w64-x86_64-tools-git \
           mingw-w64-x86_64-cc \
           mingw-w64-x86_64-angleproject \
           mingw-w64-x86_64-capstone \
           mingw-w64-x86_64-curl \
           mingw-w64-x86_64-cyrus-sasl \
           mingw-w64-x86_64-expat \
           mingw-w64-x86_64-fontconfig \
           mingw-w64-x86_64-freetype \
           mingw-w64-x86_64-fribidi \
           mingw-w64-x86_64-gcc-libs \
           mingw-w64-x86_64-gdk-pixbuf2 \
           mingw-w64-x86_64-gettext \
           mingw-w64-x86_64-glib2 \
           mingw-w64-x86_64-gmp \
           mingw-w64-x86_64-gnutls \
           mingw-w64-x86_64-graphite2 \
           mingw-w64-x86_64-gst-plugins-base \
           mingw-w64-x86_64-gstreamer \
           mingw-w64-x86_64-gtk3 \
           mingw-w64-x86_64-harfbuzz \
           mingw-w64-x86_64-jbigkit \
           mingw-w64-x86_64-lerc \
           mingw-w64-x86_64-libc++ \
           mingw-w64-x86_64-libdatrie \
           mingw-w64-x86_64-libdeflate \
           mingw-w64-x86_64-libepoxy \
           mingw-w64-x86_64-libffi \
           mingw-w64-x86_64-libiconv \
           mingw-w64-x86_64-libidn2 \
           mingw-w64-x86_64-libjpeg-turbo \
           mingw-w64-x86_64-libnfs \
           mingw-w64-x86_64-libpng \
           mingw-w64-x86_64-libpsl \
           mingw-w64-x86_64-libslirp \
           mingw-w64-x86_64-libssh \
           mingw-w64-x86_64-libssh2 \
           mingw-w64-x86_64-libtasn1 \
           mingw-w64-x86_64-libthai \
           mingw-w64-x86_64-libtiff \
           mingw-w64-x86_64-libunistring \
           mingw-w64-x86_64-libunwind \
           mingw-w64-x86_64-libusb \
           mingw-w64-x86_64-libwebp \
           mingw-w64-x86_64-libwinpthread-git \
           mingw-w64-x86_64-lz4 \
           mingw-w64-x86_64-lzo2 \
           mingw-w64-x86_64-nettle \
           mingw-w64-x86_64-openssl \
           mingw-w64-x86_64-opus \
           mingw-w64-x86_64-orc \
           mingw-w64-x86_64-p11-kit \
           mingw-w64-x86_64-pango \
           mingw-w64-x86_64-pixman \
           mingw-w64-x86_64-SDL2 \
           mingw-w64-x86_64-SDL2_image \
           mingw-w64-x86_64-snappy \
           mingw-w64-x86_64-spice \
           mingw-w64-x86_64-usbredir \
           mingw-w64-x86_64-xz \
           mingw-w64-x86_64-zlib \
           mingw-w64-x86_64-zstd

## 进入工程目录（这里以：C:\Users\xidon\code\github\qemu-machine\ 为例）
cd /C/Users/xidon/code/github/qemu-machine/

## 下载解压源码（如果需要其它版本，请使用以下命令自行下载解压，例如9.0.0版本，使用以下命令，如果使用9.0.0的版本，无需执行以下2条指令）
wget https://download.qemu.org/qemu-9.0.0.tar.xz
tar xvJf qemu-9.0.0.tar.xz

## 进入源码目录（绝对路径为：C:\Users\xidon\code\github\qemu-machine\qemu-9.0.0\）
cd qemu-9.0.0

## 配置源码工程（这里以：C:\Users\xidon\program\QEMU-MACHINE\ 为例）
./configure --prefix=/C/Users/xidon/program/QEMU-MACHINE
 
## 编译源码工程
make -j6

## 安装二进制文件
make install

## 安装的二进制文件所在目录
C:\Users\xidon\program\QEMU-MACHINE
