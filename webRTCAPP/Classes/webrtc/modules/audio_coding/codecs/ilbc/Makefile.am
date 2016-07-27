AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libiLBC.a

INCLUDES = -I../../../../../ -I../../../../../webrtc/common_audio/signal_processing/include/ -I../../../../../webrtc/modules/audio_coding/codecs/ilbc/interface/

DEFS = -D_DEBUG -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11 -march=athlon64

libiLBC_a_SOURCES = audio_encoder_ilbc.cc\
abs_quant.c\
abs_quant_loop.c\
augmented_cb_corr.c\
bw_expand.c\
cb_construct.c\
cb_mem_energy_augmentation.c\
cb_mem_energy.c\
cb_mem_energy_calc.c\
cb_search.c\
cb_search_core.c\
cb_update_best_index.c\
chebyshev.c\
comp_corr.c\
constants.c\
create_augmented_vec.c\
decode.c\
decode_residual.c\
decoder_interpolate_lsf.c\
do_plc.c\
encode.c\
energy_inverse.c\
enhancer.c\
enhancer_interface.c\
enh_upsample.c\
filtered_cb_vecs.c\
frame_classify.c\
gain_dequant.c\
gain_quant.c\
get_cd_vec.c\
get_lsp_poly.c\
get_sync_seq.c\
hp_input.c\
hp_output.c\
ilbc.c\
index_conv_dec.c\
index_conv_enc.c\
init_decode.c\
init_encode.c\
interpolate.c\
interpolate_samples.c\
lpc_encode.c\
lsf_check.c\
lsf_interpolate_to_poly_dec.c\
lsf_interpolate_to_poly_enc.c\
lsf_to_lsp.c\
lsf_to_poly.c\
lsp_to_lsf.c\
my_corr.c\
nearest_neighbor.c\
pack_bits.c\
poly_to_lsf.c\
poly_to_lsp.c\
refiner.c\
simple_interpolate_lsf.c\
simple_lpc_analysis.c\
simple_lsf_dequant.c\
simple_lsf_quant.c\
smooth.c\
smooth_out_data.c\
sort_sq.c\
split_vq.c\
state_construct.c\
state_search.c\
swap_bytes.c\
unpack_bits.c\
vq3.c\
vq4.c\
window32_w32.c\
xcorr_coef.c
