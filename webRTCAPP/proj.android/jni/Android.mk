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

VIDEO_BUILD := true
VPX_BUILD := false
USE_FFMPEG_DECODER_BUILD := false

include $(CLEAR_VARS)

LOCAL_MODULE    := webrtc
LOCAL_MODULE_FILENAME := libwebrtc

WEBRTC_SOURCE_PATH := $(LOCAL_PATH)/../../Classes

WEBRTC_OVERRIDES_SOURCE_PATH := $(LOCAL_PATH)/../../../../RTChatSdk/Client/ios/RTChat/Classes/webrtc_overrides

MY_FILES_WEBRTC_BASE_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/base
MY_FILES_WEBRTC_RTC_BASE_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/rtc_base
MY_FILES_WEBRTC_VOICE_ENGINE_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/voice_engine
MY_FILES_WEBRTC_SYSTEM_WRAPPER_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/system_wrappers
MY_FILES_WEBRTC_MODULES_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/modules
MY_FILES_WEBRTC_AUDIO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/audio
MY_FILES_WEBRTC_COMMON_AUDIO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/common_audio
MY_FILES_WEBRTC_OVERRIDES_PATH  :=  $(WEBRTC_OVERRIDES_SOURCE_PATH)/webrtc
MY_FILES_WEBRTC_MEDIA_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/media
MY_FILES_WEBRTC_CALL_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/call
MY_FILES_WEBRTC_API_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/api
MY_FILES_WEBRTC_VIDEO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/video
MY_FILES_WEBRTC_COMMON_VIDEO_PATH  :=  $(WEBRTC_SOURCE_PATH)/webrtc/common_video


MY_FILES_SUFFIX := %.cpp %.c %.cc

#EXCLUDE_UNITTEST := unittest
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
#rwildcard = $(foreach d,$(wildcard $1*), $(if $(findstring $(EXCLUDE_UNITTEST),$d),,$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d)))
SRC_FILES := $(call rwildcard, $(MY_FILES_WEBRTC_BASE_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES := $(call rwildcard, $(MY_FILES_WEBRTC_RTC_BASE_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_VOICE_ENGINE_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_SYSTEM_WRAPPER_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_MODULES_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_AUDIO_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_COMMON_AUDIO_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_MEDIA_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_CALL_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_API_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_VIDEO_PATH)/,$(MY_FILES_SUFFIX))
SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_COMMON_VIDEO_PATH)/,$(MY_FILES_SUFFIX))


not-containing = $(foreach v,$2,$(if $(findstring $1,$v),,$v))
MY_SRC_FILES := $(call not-containing,win,$(SRC_FILES))
MY_SRC_FILES := $(call not-containing,mac,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,cocoa,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,macutils,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,macconversion,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,gcd,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,test,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,mips,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,examples,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,corevideo,$(MY_SRC_FILES))
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
MY_SRC_FILES := $(call not-containing,aec_dump,$(MY_SRC_FILES))

ifeq ($(VIDEO_BUILD),false)
MY_SRC_FILES := $(call not-containing,h264,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,vp8,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,vp9,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,i420,$(MY_SRC_FILES))
endif

ifeq ($(VPX_BUILD),false)
MY_SRC_FILES := $(call not-containing,vp8_impl.cc,$(MY_SRC_FILES))
endif

#remove default files
MY_SRC_FILES := $(call not-containing,replay.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,audio_manager.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,audio_record_jni.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,audio_settings.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,audio_track_jni.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,opensles_player.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,opensles_recorder.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,opensles_recorder.cc,$(MY_SRC_FILES))
MY_SRC_FILES := $(call not-containing,jvm_android.cc,$(MY_SRC_FILES))

#add change files
MY_SRC_FILES += $(call rwildcard, $(MY_FILES_WEBRTC_OVERRIDES_PATH)/,$(MY_FILES_SUFFIX))


ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
MY_SRC_FILES := $(call not-containing,_sse,$(MY_SRC_FILES))
else ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
MY_SRC_FILES := $(call not-containing,_sse,$(MY_SRC_FILES))
else ifeq ($(TARGET_ARCH_ABI), x86)
MY_SRC_FILES := $(call not-containing,_neon,$(MY_SRC_FILES))
else ifeq ($(TARGET_ARCH_ABI), x86_64)
MY_SRC_FILES := $(call not-containing,_neon,$(MY_SRC_FILES))
endif

#$(warning "$(MY_SRC_FILES)")

LOCAL_SRC_FILES += $(MY_SRC_FILES:$(LOCAL_PATH)/%=%) \
				   $(WEBRTC_SOURCE_PATH)/webrtc/config.cc \
			       $(WEBRTC_SOURCE_PATH)/webrtc/common_types.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/common_audio/window_generator.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/system_wrappers/source/atomic32_non_darwin_unix.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/common_audio/signal_processing/get_hanning_window.c \
				   $(WEBRTC_SOURCE_PATH)/webrtc/logging/rtc_event_log/rtc_event_log.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/logging/rtc_event_log/rtc_event_log_helper_thread.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/modules/audio_processing/include/aec_dump.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/modules/audio_processing/aec_dump/null_aec_dump_factory.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/modules/audio_coding/codecs/ilbc/window32_w32.c

ifeq ($(VIDEO_BUILD),true)
LOCAL_SRC_FILES += $(WEBRTC_SOURCE_PATH)/webrtc/pc/mediastream.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/pc/mediastreamobserver.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/pc/videotrack.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/pc/videotracksource.cc \
				   $(WEBRTC_SOURCE_PATH)/webrtc/pc/videocapturertracksource.cc
endif
				   
LOCAL_C_INCLUDES := $(WEBRTC_OVERRIDES_SOURCE_PATH) \
                    $(WEBRTC_SOURCE_PATH) \
					$(WEBRTC_SOURCE_PATH)/third_party/boringssl/src/include \
					$(WEBRTC_SOURCE_PATH)/third_party/jsoncpp/source/include \
					$(WEBRTC_SOURCE_PATH)/third_party/libyuv/include \
					$(WEBRTC_SOURCE_PATH)/third_party/libvpx/source/libvpx \
					$(WEBRTC_SOURCE_PATH)/third_party/opus/src/include \
					$(WEBRTC_SOURCE_PATH)/third_party/ffmpeg \
                                        $(WEBRTC_SOURCE_PATH)/third_party/protobuf/src \
					$(WEBRTC_SOURCE_PATH)/webrtc/common_audio/signal_processing/include \
				    $(WEBRTC_SOURCE_PATH)/webrtc/modules/audio_coding/codecs/isac/main/include \
				    $(NDK_ROOT)/sources/android/cpufeatures \

ifeq ($(USE_FFMPEG_DECODER_BUILD),true)
ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)				    
LOCAL_C_INCLUDES += $(WEBRTC_SOURCE_PATH)/third_party/ffmpeg/chromium/config/Chromium/android/arm-neon
else ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
LOCAL_C_INCLUDES += $(WEBRTC_SOURCE_PATH)/third_party/ffmpeg/chromium/config/Chromium/android/arm64
else ifeq ($(TARGET_ARCH_ABI), x86)
LOCAL_C_INCLUDES += $(WEBRTC_SOURCE_PATH)/third_party/ffmpeg/chromium/config/Chromium/android/ia32
else ifeq ($(TARGET_ARCH_ABI), x86_64)
LOCAL_C_INCLUDES += $(WEBRTC_SOURCE_PATH)/third_party/ffmpeg/chromium/config/Chromium/android/x64
endif
endif
	
#$(warning "$(LOCAL_C_INCLUDES)")			    

LOCAL_CFLAGS += -DANDROID -DWEBRTC_POSIX -DWEBRTC_ANDROID -DWEBRTC_LINUX -DWEBRTC_OPUS_SUPPORT_120MS_PTIME=0 -DWEBRTC_OPUS_VARIABLE_COMPLEXITY=0
LOCAL_CFLAGS += -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -DDYNAMIC_ANNOTATIONS_ENABLED=1 -DWTF_USE_DYNAMIC_ANNOTATIONS=1 -D__GNU_SOURCE=1 -DWEBRTC_BUILD_LIBEVENT -DGOOGLE_PROTOBUF_NO_RTTI -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER   -DHAVE_WEBRTC_VOICE -DRTCHAT_OPUS_FREQ=16000
LOCAL_CFLAGS += -Wno-narrowing

LOCAL_CFLAGS += -fno-strict-aliasing --param=ssp-buffer-size=4 -funwind-tables -fPIC -pipe -ffunction-sections -fno-short-enums -finline-limit=64 -Wall -Werror -Wno-maybe-uninitialized -Wno-missing-field-initializers -Wno-unused-parameter -fvisibility=hidden -Wextra -Wno-missing-field-initializers -Wno-strict-overflow -Os -fno-ident -fdata-sections -g0 -fno-builtin-cos -fno-builtin-sin -fno-builtin-cosf -fno-builtin-sinf -Wno-unused-local-typedefs -Wno-unused-function
LOCAL_CPPFLAGS += -fno-threadsafe-statics -fvisibility-inlines-hidden -std=gnu++11 -Wno-narrowing -fno-rtti -fno-exceptions -Woverloaded-virtual -fuse-ld=gold -Wno-reorder

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)				    
LOCAL_CFLAGS += -fstack-protector -march=armv7-a -mfloat-abi=softfp -mtune=generic-armv7-a -fno-tree-sra -fno-caller-saves -mfpu=neon -mthumb -mthumb-interwork  -Wno-psabi -fomit-frame-pointer
else ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
LOCAL_CFLAGS += -fstack-protector  -fno-omit-frame-pointer 
else ifeq ($(TARGET_ARCH_ABI), x86)
LOCAL_CFLAGS += -fno-stack-protector -mstackrealign -m32 -msse2 -mfpmath=sse -mmmx -fomit-frame-pointer 
else ifeq ($(TARGET_ARCH_ABI), x86_64)
LOCAL_CFLAGS += -fstack-protector -m64 -march=x86-64 -fomit-frame-pointer 
endif


LOCAL_CFLAGS += -DWEBRTC_INTELLIGIBILITY_ENHANCER=1 -DWEBRTC_NS_FIXED -DWEBRTC_AEC_DEBUG_DUMP=0 -DWEBRTC_APM_DEBUG_DUMP=0 -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE

LOCAL_CFLAGS += -DWEBRTC_CODEC_OPUS -DOPUS_FIXED_POINT -DWEBRTC_CODEC_ISACFX -DWEBRTC_CODEC_ILBC -DWEBRTC_CODEC_G722 -DWEBRTC_CODEC_RED -DWEBRTC_HOWLINGCONTROL

ifeq ($(VIDEO_BUILD),true)

ifeq ($(VPX_BUILD),true)
LOCAL_CFLAGS += -DWEBRTC_VPX
endif

ifeq ($(USE_FFMPEG_DECODER_BUILD),true)
LOCAL_CFLAGS += -DUSEFFMPEG264
endif

LOCAL_CFLAGS += -DUSE_LIBJPEG_TURBO=1 -DHAVE_WEBRTC_VIDEO -DWEBRTC_USE_H264

endif

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
LOCAL_CFLAGS += -DWEBRTC_ARCH_ARM -DWEBRTC_ARCH_ARM_V7 -DWEBRTC_HAS_NEON
LOCAL_CFLAGS += -mfpu=neon
else ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
LOCAL_CFLAGS += -DWEBRTC_ARCH_ARM -DWEBRTC_ARCH_ARM64 -DWEBRTC_HAS_NEON
endif

include $(BUILD_STATIC_LIBRARY)