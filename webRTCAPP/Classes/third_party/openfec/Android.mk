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

LOCAL_MODULE    := openfec
LOCAL_MODULE_FILENAME := libopenfec

MY_FILES_OPENFEC_PATH  :=  $(LOCAL_PATH)/

MY_FILES_SUFFIX := %.cpp %.c %.cc

LOCAL_SRC_FILES +=  $(MY_FILES_OPENFEC_PATH)/src/lib_advanced/ldpc_from_file/of_ldpc_ff_api.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/binary_matrix/of_hamming_weight.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/binary_matrix/of_matrix_convert.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/binary_matrix/of_matrix_dense.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/binary_matrix/of_matrix_sparse.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/binary_matrix/of_tools.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/it_decoding/of_it_decoding.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/ml_decoding/of_ml_decoding.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/ml_decoding/of_ml_tool.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/of_create_pchk.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/linear_binary_codes_utils/of_symbol.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/statistics/of_statistics.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/of_mem.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/of_openfec_api.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_common/of_rand.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/2d_parity_matrix/of_2d_parity_api.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/ldpc_staircase/of_ldpc_staircase_api.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/ldpc_staircase/of_ldpc_staircase_pchk.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/reed-solomon_gf_2_8/of_reed-solomon_gf_2_8.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/reed-solomon_gf_2_8/of_reed-solomon_gf_2_8_api.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/reed-solomon_gf_2_m/galois_field_codes_utils/algebra_2_4.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/reed-solomon_gf_2_m/galois_field_codes_utils/algebra_2_8.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/reed-solomon_gf_2_m/of_reed-solomon_gf_2_m_api.c \
                   $(MY_FILES_OPENFEC_PATH)/src/lib_stable/reed-solomon_gf_2_m/galois_field_codes_utils/of_galois_field_code.c \

LOCAL_C_INCLUDES := $(WEBRTC_SOURCE_PATH) \
					$(MY_FILES_OPENFEC_PATH)/src/lib_common \
					$(MY_FILES_OPENFEC_PATH)/src/include

LOCAL_CPPFLAGS += -std=gnu++11

include $(BUILD_STATIC_LIBRARY)