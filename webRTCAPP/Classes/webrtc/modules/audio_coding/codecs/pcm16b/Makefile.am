AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libPCM16B.a

INCLUDES = -I../../../../../ -I../../../../../webrtc/common_audio/signal_processing/include/ -I./include

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libPCM16B_a_SOURCES = audio_encoder_pcm16b.cc\
pcm16b.c
