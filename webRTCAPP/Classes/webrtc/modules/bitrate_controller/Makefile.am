AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libbitrate_controller.a

INCLUDES = -I../../../

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libbitrate_controller_a_SOURCES = bitrate_controller_impl.cc\
remb_suppressor.cc\
send_side_bandwidth_estimation.cc
