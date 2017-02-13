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

LOCAL_MODULE    := jsoncpp
LOCAL_MODULE_FILENAME := libjsoncpp

WEBRTC_SOURCE_PATH := $(LOCAL_PATH)/../../../Classes

MY_FILES_JSONCPP_PATH  :=  $(WEBRTC_SOURCE_PATH)/third_party/jsoncpp

MY_FILES_SUFFIX := %.cpp %.c %.cc

LOCAL_SRC_FILES += $(MY_FILES_JSONCPP_PATH)/overrides/src/lib_json/json_reader.cpp \
    			   $(MY_FILES_JSONCPP_PATH)/overrides/src/lib_json/json_value.cpp \
    			   $(MY_FILES_JSONCPP_PATH)/source/src/lib_json/json_writer.cpp

LOCAL_C_INCLUDES := $(WEBRTC_SOURCE_PATH) \
					$(MY_FILES_JSONCPP_PATH)/source/src/lib_json \
					$(MY_FILES_JSONCPP_PATH)/overrides/include \
					$(MY_FILES_JSONCPP_PATH)/source/include 

LOCAL_CFLAGS += -DJSON_USE_EXCEPTION=0

LOCAL_CPPFLAGS += -std=gnu++11

include $(BUILD_STATIC_LIBRARY)