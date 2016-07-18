AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libneteq.a

INCLUDES = -I../../../../ -I../../../../third_party/opus/src/celt/ -I../../../../third_party/opus/src/include/ -I../../../../third_party/opus/src/src/

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11

libneteq_a_SOURCES = accelerate.cc\
audio_classifier.cc\
audio_decoder_impl.cc\
audio_multi_vector.cc\
audio_vector.cc\
background_noise.cc\
buffer_level_filter.cc\
comfort_noise.cc\
decision_logic.cc\
decision_logic_fax.cc\
decision_logic_normal.cc\
decoder_database.cc\
delay_manager.cc\
delay_peak_detector.cc\
dsp_helper.cc\
dtmf_buffer.cc\
dtmf_tone_generator.cc\
expand.cc\
merge.cc\
neteq.cc\
neteq_impl.cc\
normal.cc\
packet_buffer.cc\
payload_splitter.cc\
post_decode_vad.cc\
preemptive_expand.cc\
random_vector.cc\
rtcp.cc\
statistics_calculator.cc\
sync_buffer.cc\
timestamp_scaler.cc\
time_stretch.cc
