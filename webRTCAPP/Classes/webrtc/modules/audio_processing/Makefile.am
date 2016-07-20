AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libaudio_processing.a

INCLUDES = -I../../../

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_NS_FLOAT -std=gnu++11


libaudio_processing_a_SOURCES = audio_buffer.cc\
audio_processing_impl.cc\
channel_buffer.cc\
echo_cancellation_impl.cc\
echo_control_mobile_impl.cc\
gain_control_impl.cc\
high_pass_filter_impl.cc\
level_estimator_impl.cc\
noise_suppression_impl.cc\
processing_component.cc\
rms_level.cc\
splitting_filter.cc\
typing_detection.cc\
voice_detection_impl.cc


libaudio_processing_a_SOURCES += aec/aec_core.c \
aec/aec_core_sse2.c \
aec/aec_rdft.c \
aec/aec_rdft_sse2.c \
aec/aec_resampler.c \
aec/echo_cancellation.c

libaudio_processing_a_SOURCES += aecm/aecm_core.c \
aecm/aecm_core_c.c\
aecm/echo_control_mobile.c

libaudio_processing_a_SOURCES += agc/agc_audio_proc.cc\
agc/agc.cc\
agc/agc_manager_direct.cc\
agc/circular_buffer.cc\
agc/gmm.cc\
agc/histogram.cc\
agc/pitch_based_vad.cc\
agc/pitch_internal.cc\
agc/pole_zero_filter.cc\
agc/standalone_vad.cc\
agc/utility.cc\
agc/legacy/analog_agc.c\
agc/legacy/digital_agc.c

libaudio_processing_a_SOURCES += ns/noise_suppression.c\
ns/noise_suppression_x.c\
ns/ns_core.c\
ns/nsx_core.c\
ns/nsx_core_c.c

libaudio_processing_a_SOURCES += transient/click_annotate.cc\
transient/file_utils.cc\
transient/moving_moments.cc\
transient/transient_detector.cc\
transient/transient_suppressor.cc\
transient/wpd_node.cc\
transient/wpd_tree.cc

libaudio_processing_a_SOURCES += utility/delay_estimator.c\
utility/delay_estimator_wrapper.c\
utility/fft4g.c

libaudio_processing_a_SOURCES += beamformer/beamformer.cc\
beamformer/covariance_matrix_generator.cc
