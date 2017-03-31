# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := webrtc
LOCAL_MODULE_FILENAME := libwebrtc

WEBRTC_SOURCE_PATH := $(LOCAL_PATH)/../../Classes

MY_FILES_WEBRTC_BASE_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/base
MY_FILES_WEBRTC_VOICE_ENGINE_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/voice_engine
MY_FILES_WEBRTC_SYSTEM_WRAPPER_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/system_wrappers
MY_FILES_WEBRTC_MODULES_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/modules
MY_FILES_WEBRTC_AUDIO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/audio
MY_FILES_WEBRTC_VIDEO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/video
MY_FILES_WEBRTC_COMMON_AUDIO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/common_audio
MY_FILES_WEBRTC_COMMON_VIDEO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/common_video

MY_FILES_SUFFIX := %.cpp %.c %.cc

#EXCLUDE_UNITTEST := unittest
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
#rwildcard = $(foreach d,$(wildcard $1*), $(if $(findstring $(EXCLUDE_UNITTEST),$d),,$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d)))
SRC_FILES := $(call rwildcard, $(MY_FILES_WEBRTC_BASE_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_VOICE_ENGINE_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_SYSTEM_WRAPPER_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_MODULES_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_AUDIO_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_VIDEO_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_COMMON_AUDIO_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_COMMON_VIDEO_PATH)/,$(MY_FILES_SUFFIX))
#$(warning "$(SRC_FILES)")

not-containing = $(foreach v,$2,$(if $(findstring $1,$v),,$v))
MY_SRC_FILES := $(call not-containing,win,$(SRC_FILES))
MY_SRC_FILES := $(call not-containing,mac,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,cocoa,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,macutils,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,macconversion,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,gcd,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,test,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,_sse,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,mips,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,examples,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,corevideo,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,rtc_event_log,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,fake,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,mock,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,openmax,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,sctptransport,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,tools,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,ensure_initialized,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,audio_device/linux,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,desktop_capture,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,simulations,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,vp8_sequence_coder,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,noop,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,p2p,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,voice_engine_fixture,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,cpu_features_linux,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,replay,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,loopback,$(MY_SRC_FILES))


#$(warning "$(MY_SRC_FILES)")

LOCAL_SRC_FILES += $(MY_SRC_FILES:$(LOCAL_PATH)/%=%) \
				   $(WEBRTC_SOURCE_PATH)/webrtc/config.cc \
			       $(WEBRTC_SOURCE_PATH)/webrtc/common_types.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/common_audio/window_generator.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/system_wrappers/source/atomic32_non_darwin_unix.cc\
				   $(WEBRTC_SOURCE_PATH)/webrtc/common_audio/signal_processing/get_hanning_window.c\
				   $(WEBRTC_SOURCE_PATH)/webrtc/modules/audio_coding/codecs/ilbc/window32_w32.c

LOCAL_C_INCLUDES := $(WEBRTC_SOURCE_PATH) \
					$(WEBRTC_SOURCE_PATH)/third_party/boringssl/src/include \
					$(WEBRTC_SOURCE_PATH)/third_party/jsoncpp/source/include \
					$(WEBRTC_SOURCE_PATH)/third_party/libyuv/include \
					$(WEBRTC_SOURCE_PATH)/third_party/libvpx/source/libvpx \
					$(WEBRTC_SOURCE_PATH)/third_party/opus/src/include \
					$(WEBRTC_SOURCE_PATH)/third_party/ffmpeg \
					$(WEBRTC_SOURCE_PATH)/webrtc/common_audio/signal_processing/include \
				    $(WEBRTC_SOURCE_PATH)/webrtc/modules/audio_coding/codecs/isac/main/include \
				    $(NDK_ROOT)/sources/android/cpufeatures \

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)				    
LOCAL_C_INCLUDES += $(WEBRTC_SOURCE_PATH)/third_party/ffmpeg/chromium/config/Chromium/android/arm-neon
else ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
LOCAL_C_INCLUDES += $(WEBRTC_SOURCE_PATH)/third_party/ffmpeg/chromium/config/Chromium/android/arm64
endif
	
#$(warning "$(LOCAL_C_INCLUDES)")			    

LOCAL_CFLAGS += -DANDROID -DWEBRTC_POSIX -DWEBRTC_ANDROID -DWEBRTC_LINUX
LOCAL_CFLAGS += -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -DDYNAMIC_ANNOTATIONS_ENABLED=1 -DWTF_USE_DYNAMIC_ANNOTATIONS=1 -D__GNU_SOURCE=1 -DWEBRTC_BUILD_LIBEVENT
LOCAL_CFLAGS += -Wno-narrowing

LOCAL_CFLAGS += -DWEBRTC_INTELLIGIBILITY_ENHANCER=1 -DWEBRTC_NS_FIXED -DWEBRTC_AEC_DEBUG_DUMP=0 -DWEBRTC_APM_DEBUG_DUMP=0 -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE

LOCAL_CFLAGS += -DWEBRTC_CODEC_OPUS -DOPUS_FIXED_POINT -DWEBRTC_CODEC_ISACFX -DWEBRTC_CODEC_ILBC -DWEBRTC_CODEC_G722 -DWEBRTC_CODEC_RED

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
LOCAL_CFLAGS += -DWEBRTC_ARCH_ARM -DWEBRTC_ARCH_ARM_V7 -DWEBRTC_HAS_NEON
LOCAL_CFLAGS += -mfpu=neon
else ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
LOCAL_CFLAGS += -DWEBRTC_ARCH_ARM -DWEBRTC_ARCH_ARM64 -DWEBRTC_HAS_NEON
LOCAL_CFLAGS += -mfpu=neon
endif

LOCAL_CPPFLAGS += -std=gnu++11

include $(BUILD_STATIC_LIBRARY)