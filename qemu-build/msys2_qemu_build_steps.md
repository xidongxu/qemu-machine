# Win11本地构建QEMU二进制文件步骤



## 1. 安装 MSYS2 

安装：msys2-x86_64-20240113.exe

> 工程的 ./qemu-packs 目录下包含 msys2-x86_64-20240113.exe 文件，可以直接安装使用，如果需要安装最新版本请参考下面的安装方式，这里以：msys2-x86_64-20240113.exe 文件为例：

网页：https://www.msys2.org/ 中，找到然后下载：msys2-x86_64-20240113.exe 文件，下载并安装即可。 
链接：https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe



## 2. 配置 MSYS2 

> 这里安装目录：C:\msys64 为例，进入安装目录：C:\msys64\etc\pacman.d 

- 在文件 mirrorlist.msys 的前面插入

  ```shell
  Server = http://mirrors.ustc.edu.cn/msys2/msys/$arch
  ```

- 在文件 mirrorlist.mingw32 的前面插入

  ```shell
  Server = http://mirrors.ustc.edu.cn/msys2/mingw/i686
  ```

- 在文件 mirrorlist.mingw64 的前面插入

  ```shell
  Server = http://mirrors.ustc.edu.cn/msys2/mingw/x86_64
  ```



## 3. 打开 MSYS2 终端

> 尽量使用管理员权限

MSYS2 MINGW64



## 4. 在 MSYS2 安装 qemu 依赖库

> 期间可能会询问是否安装，直接全部 Y 即可，还可能会自动关闭终端，需要再次使用管理员权限打开，继续执行其它安装步骤

```shell
pacman -Syu
pacman -Su
```

```shell
pacman -S base-devel mingw-w64-x86_64-toolchain git python ninja
pacman -S mingw-w64-x86_64-glib2 mingw-w64-x86_64-pixman python-setuptools
pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-SDL2 mingw-w64-x86_64-libslirp
```

```shell
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
```



## 5. 拉取最新工程

```shell
https://github.com/xidongxu/qemu-machine.git
cd ./qemu-machine
```



## 6. 选择 qemu 版本

### 方式1：使用工程自带版本

> 工程自带的qemu版本为 qemu-9.0.0，无需执行其它操作

### 方式2：下载源码压缩文件

> 如果需要其它版本，请使用以下命令自行下载解压，例如9.0.0版本，使用以下命令：

```shell
wget https://download.qemu.org/qemu-9.0.0.tar.xz
tar xvJf qemu-9.0.0.tar.xz
```

### 方式3： 使用官方最新版本

> 使用官方最新版本，请使用以下命令：

```shell
git clone https://gitlab.com/qemu-project/qemu.git
cd qemu
git submodule init
git submodule update --recursive
```



## 7. 进入临时配置目录

```shell
cd ./qemu-configure
```



## 8. 配置源码工程

>  这里安装目录以：C:\Users\xidon\program\QEMU-MACHINE 为例

###  方式1：使用工程自带源码

```shell
../qemu-9.0.0/configure --prefix=/C/Users/xidon/program/QEMU-MACHINE
```

### 方式2：使用其它版本源码

```shell
../qemu-版本号/configure --prefix=/C/Users/xidon/program/QEMU-MACHINE
```

### 方式3：使用官方最新源码

``` shell
../qemu/configure --prefix=/C/Users/xidon/program/QEMU-MACHINE
```



## 9. 编译源码工程

```shell
make -j16
```



## 10. 安装二进制文件

```shell
make install
```



## 11. 安装的二进制文件所在目录

```shell
C:\Users\xidon\program\QEMU-MACHINE
```

