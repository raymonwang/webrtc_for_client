AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libaudio_device.a

INCLUDES = -I../../../ -I./linux

DEFS = -DWEBRTC_POSIX -DWEBRTC_LINUX -DRTCHAT_SERVER -std=gnu++11 -D_DEBUG -march=athlon64

libaudio_device_a_SOURCES = audio_device_buffer.cc\
audio_device_generic.cc\
audio_device_impl.cc\
audio_device_utility.cc

libaudio_device_a_SOURCES += linux/audio_device_utility_linux.cc

libaudio_device_a_SOURCES += linux/alsasymboltable_linux.cc\
linux/audio_device_alsa_linux.cc\
linux/audio_device_utility_linux.cc\
linux/audio_mixer_manager_alsa_linux.cc\
linux/latebindingsymboltable_linux.cc\
linux/pulseaudiosymboltable_linux.cc\
linux/audio_device_pulse_linux.cc\
linux/audio_mixer_manager_pulse_linux.cc

libaudio_device_a_SOURCES += dummy/audio_device_dummy.cc\
dummy/audio_device_utility_dummy.cc
