AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libvoice_engine.a

INCLUDES = -I../../ -I../../third_party/jsoncpp/source/include

DEFS = -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11 -D_DEBUG

DEFS += -DFEATURE_ENABLE_SSL -DSSL_USE_OPENSSL

libvoice_engine_a_SOURCES = channel.cc\
channel_manager.cc\
dtmf_inband.cc\
dtmf_inband_queue.cc\
level_indicator.cc\
monitor_module.cc\
network_predictor.cc\
output_mixer.cc\
shared_data.cc\
statistics.cc\
transmit_mixer.cc\
utility.cc\
voe_audio_processing_impl.cc\
voe_base_impl.cc\
voe_codec_impl.cc\
voe_dtmf_impl.cc\
voe_external_media_impl.cc\
voe_file_impl.cc\
voe_hardware_impl.cc\
voe_neteq_stats_impl.cc\
voe_network_impl.cc\
voe_rtp_rtcp_impl.cc\
voe_video_sync_impl.cc\
voe_volume_control_impl.cc\
voice_engine_impl.cc
