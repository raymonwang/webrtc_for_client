AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libG711.a

INCLUDES = -I../../../../../ -I../../../../../webrtc/common_audio/signal_processing/include/ -I../../../../../webrtc/modules/audio_coding/codecs/cng/include/ -I../../../../../webrtc/modules/audio_coding/codecs/g711/include/

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libG711_a_SOURCES = audio_encoder_pcm.cc\
g711.c\
g711_interface.c
