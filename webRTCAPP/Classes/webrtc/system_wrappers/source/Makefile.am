AUTOMAKE_OPTIONS = foreign

noinst_LIBRARIES = libsystem_wrappers.a
libsystem_wrappers_a_SOURCES =  aligned_malloc.cc atomic32_posix.cc clock.cc condition_variable.cc condition_variable_posix.cc cpu_features.cc  cpu_info.cc  critical_section.cc critical_section_posix.cc data_log.cc  data_log_c.cc  data_log_no_op.cc  event.cc  event_posix.cc  event_tracer.cc field_trial_default.cc  file_impl.cc logging.cc  metrics_default.cc  rtp_to_ntp.cc  rw_lock.cc  rw_lock_generic.cc  rw_lock_posix.cc sleep.cc  sort.cc thread.cc  thread_posix.cc tick_util.cc  timestamp_extrapolator.cc  trace_impl.cc  trace_posix.cc 

INCLUDES = -I../../../ 
AM_CXXFLAGS = -DWEBRTC_POSIX -DWEBRTC_LINUX -std=gnu++11
AM_CXXFLAGS += 
