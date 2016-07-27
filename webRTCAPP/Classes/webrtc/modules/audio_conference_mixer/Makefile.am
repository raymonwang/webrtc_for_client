AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libaudio_conference_mixer.a

INCLUDES = -I../../../

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11 -march=athlon64

libaudio_conference_mixer_a_SOURCES = source/audio_conference_mixer_impl.cc\
source/audio_frame_manipulator.cc\
source/level_indicator.cc\
source/time_scheduler.cc
