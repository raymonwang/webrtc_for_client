AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libCNG.a

INCLUDES = -I../../../../../ -I../../../../../webrtc/common_audio/signal_processing/include/ -I../../../../../webrtc/modules/audio_coding/codecs/cng/include/

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libCNG_a_SOURCES = cng_helpfuns.c\
webrtc_cng.c\
audio_encoder_cng.cc
