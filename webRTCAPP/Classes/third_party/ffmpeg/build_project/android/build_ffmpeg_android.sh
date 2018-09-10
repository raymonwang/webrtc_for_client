#!/bin/bash
  
NDK=/home/RTChatServer/webrtc-checkout/src/chromium/src/third_party/android_tools/ndk/

#TagetArch=armeabi-v7a
#TagetArch=arm64-v8a
#TagetArch=x86
TagetArch=x86_64

if [ "$TagetArch"x = "armeabi-v7a"x ]
then
SYSROOT=$NDK/platforms/android-21/arch-arm
TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64
CROSS_PREFIX=$TOOLCHAIN/bin/arm-linux-androideabi-
CPU=arm
PREFIX=$(pwd)/android/$CPU
ADDI_CFLAGS="-marm"
elif [ "$TagetArch"x = "arm64-v8a"x ]
then
SYSROOT=$NDK/platforms/android-21/arch-arm64
TOOLCHAIN=$NDK/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64
CROSS_PREFIX=$TOOLCHAIN/bin/aarch64-linux-android-
CPU=aarch64
PREFIX=$(pwd)/android/$CPU
ADDI_CFLAGS=""
elif [ "$TagetArch"x = "x86"x ]
then
SYSROOT=$NDK/platforms/android-21/arch-x86
TOOLCHAIN=$NDK/toolchains/x86-4.9/prebuilt/linux-x86_64
CROSS_PREFIX=$TOOLCHAIN/bin/i686-linux-android-
CPU=x86
PREFIX=$(pwd)/android/$CPU
ADDI_CFLAGS=""
elif [ "$TagetArch"x = "x86_64"x ]
then
SYSROOT=$NDK/platforms/android-21/arch-x86_64
TOOLCHAIN=$NDK/toolchains/x86_64-4.9/prebuilt/linux-x86_64
CROSS_PREFIX=$TOOLCHAIN/bin/x86_64-linux-android-
CPU=x86_64
#编译后的文件会放置在 当前路径下的android/arm／下
PREFIX=$(pwd)/android/$CPU
ADDI_CFLAGS=""
fi

cd android-build

../ffmpeg/configure \
--prefix=$PREFIX \
--target-os=linux \
--arch=$CPU \
--enable-cross-compile \
--cross-prefix=$CROSS_PREFIX \
--sysroot=$SYSROOT \
--extra-cflags="-Os -fPIC $ADDI_CFLAGS" \
--extra-ldflags="$ADDI_CFLAGS" \
--disable-debug \
--disable-programs \
--disable-doc \
--disable-everything \
--enable-pic \
--enable-hwaccel=h264_vaapi \
--enable-hwaccel=h264_dxva2 \
--enable-hwaccel=mpeg4_vaapi \
--enable-hwaccels \
--enable-decoder=h264 \
--enable-decoder=aac \
--enable-decoder=mp3 \
--enable-protocol=file \
--enable-protocol=http \
--enable-protocol=hls \
--enable-demuxer=mov \
--enable-demuxer=matroska \
--enable-demuxer=mp3 \
--enable-demuxer=hls \
--enable-demuxer=mpegts \
--disable-yasm \
--disable-shared \
--enable-static \
$ADDITIONAL_CONFIGURE_FLAG

make clean
make -j4
make install
