AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libaudio_device.a

INCLUDES = -I../../../ -I./linux

DEFS = -DWEBRTC_DUMMY_AUDIO_BUILD -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11 -D_DEBUG

libaudio_device_a_SOURCES = audio_device_buffer.cc\
audio_device_generic.cc\
audio_device_impl.cc\
audio_device_utility.cc

libaudio_device_a_SOURCES += linux/audio_device_utility_linux.cc

libaudio_device_a_SOURCES += dummy/audio_device_dummy.cc\
dummy/audio_device_utility_dummy.cc\
dummy/file_audio_device.cc\
dummy/file_audio_device_factory.cc
