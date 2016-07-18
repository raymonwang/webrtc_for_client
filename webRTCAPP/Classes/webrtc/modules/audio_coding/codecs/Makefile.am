AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libaudio_decoder_interface.a

INCLUDES = -I../../../../ 

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libaudio_decoder_interface_a_SOURCES = audio_decoder.cc

lib_LIBRARIES += libaudio_encoder_interface.a

libaudio_encoder_interface_a_SOURCES = audio_encoder.cc

SUBDIRS = . cng g711 g722 ilbc isac/main isac/fix pcm16b
