# This file is generated by gyp; do not edit.

export builddir_name ?= ./webrtc/media/out
.PHONY: all
all:
	$(MAKE) -C ../.. rtc_unittest_main rtc_media rtc_media_unittests rtc_media_unittests_run
