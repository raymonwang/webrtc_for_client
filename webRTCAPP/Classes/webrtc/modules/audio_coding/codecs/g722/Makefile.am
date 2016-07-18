AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libG722.a

INCLUDES = -I../../../../../ -I../../../../../webrtc/common_audio/signal_processing/include/ -I../../../../../webrtc/modules/audio_coding/codecs/cng/include/ -I../../../../../webrtc/modules/audio_coding/codecs/g722/include

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libG722_a_SOURCES = audio_encoder_g722.cc\
g722_decode.c\
g722_encode.c\
g722_interface.c
