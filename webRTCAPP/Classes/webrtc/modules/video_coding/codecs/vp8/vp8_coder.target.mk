# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := vp8_coder
DEFS_Debug := \
	'-DV8_DEPRECATION_WARNINGS' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DCHROMIUM_BUILD' \
	'-DCR_CLANG_REVISION=274369-1' \
	'-DUI_COMPOSITOR_IMAGE_TRANSPORT' \
	'-DUSE_AURA=1' \
	'-DUSE_PANGO=1' \
	'-DUSE_CAIRO=1' \
	'-DUSE_DEFAULT_RENDER_THEME=1' \
	'-DUSE_LIBJPEG_TURBO=1' \
	'-DUSE_X11=1' \
	'-DUSE_CLIPBOARD_AURAX11=1' \
	'-DENABLE_WEBRTC=1' \
	'-DENABLE_MEDIA_ROUTER=1' \
	'-DENABLE_PEPPER_CDMS' \
	'-DENABLE_NOTIFICATIONS' \
	'-DUSE_UDEV' \
	'-DFIELDTRIAL_TESTING_ENABLED' \
	'-DENABLE_TASK_MANAGER=1' \
	'-DENABLE_EXTENSIONS=1' \
	'-DENABLE_PDF=1' \
	'-DENABLE_PLUGINS=1' \
	'-DENABLE_SESSION_SERVICE=1' \
	'-DENABLE_THEMES=1' \
	'-DENABLE_PRINTING=1' \
	'-DENABLE_BASIC_PRINTING=1' \
	'-DENABLE_PRINT_PREVIEW=1' \
	'-DENABLE_SPELLCHECK=1' \
	'-DENABLE_CAPTIVE_PORTAL_DETECTION=1' \
	'-DENABLE_SUPERVISED_USERS=1' \
	'-DENABLE_MDNS=1' \
	'-DENABLE_SERVICE_DISCOVERY=1' \
	'-DV8_USE_EXTERNAL_STARTUP_DATA' \
	'-DFULL_SAFE_BROWSING' \
	'-DSAFE_BROWSING_CSD' \
	'-DSAFE_BROWSING_DB_LOCAL' \
	'-DEXPAT_RELATIVE_PATH' \
	'-DWEBRTC_BUILD_LIBEVENT' \
	'-DWEBRTC_POSIX' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE' \
	'-DGTEST_HAS_POSIX_RE=0' \
	'-DGTEST_LANG_CXX11=0' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-DUSE_LIBPCI=1' \
	'-DUSE_GLIB=1' \
	'-DUSE_NSS_CERTS=1' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG' \
	'-D_GLIBCXX_DEBUG=1'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fstack-protector \
	--param=ssp-buffer-size=4 \
	-Werror \
	-pthread \
	-fno-strict-aliasing \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-B/data/home/RTChatServer/webrtc-checkout/src//usr/bin \
	-Wno-char-subscripts \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-Wno-strict-overflow \
	-m64 \
	-march=x86-64 \
	--sysroot=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot \
	-O0 \
	-g \
	-funwind-tables \
	-gsplit-dwarf

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-exceptions \
	-fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-std=gnu++11 \
	-Wnon-virtual-dtor \
	-Woverloaded-virtual

INCS_Debug := \
	-I$(obj)/gen \
	-I. \
	-Iwebrtc/common_video/include \
	-Iwebrtc/common_video/libyuv/include \
	-Ichromium/src/third_party/libyuv/include \
	-Ichromium/src/third_party/libyuv \
	-Ichromium/src/testing/gtest/include

DEFS_Release := \
	'-DV8_DEPRECATION_WARNINGS' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DCHROMIUM_BUILD' \
	'-DCR_CLANG_REVISION=274369-1' \
	'-DUI_COMPOSITOR_IMAGE_TRANSPORT' \
	'-DUSE_AURA=1' \
	'-DUSE_PANGO=1' \
	'-DUSE_CAIRO=1' \
	'-DUSE_DEFAULT_RENDER_THEME=1' \
	'-DUSE_LIBJPEG_TURBO=1' \
	'-DUSE_X11=1' \
	'-DUSE_CLIPBOARD_AURAX11=1' \
	'-DENABLE_WEBRTC=1' \
	'-DENABLE_MEDIA_ROUTER=1' \
	'-DENABLE_PEPPER_CDMS' \
	'-DENABLE_NOTIFICATIONS' \
	'-DUSE_UDEV' \
	'-DFIELDTRIAL_TESTING_ENABLED' \
	'-DENABLE_TASK_MANAGER=1' \
	'-DENABLE_EXTENSIONS=1' \
	'-DENABLE_PDF=1' \
	'-DENABLE_PLUGINS=1' \
	'-DENABLE_SESSION_SERVICE=1' \
	'-DENABLE_THEMES=1' \
	'-DENABLE_PRINTING=1' \
	'-DENABLE_BASIC_PRINTING=1' \
	'-DENABLE_PRINT_PREVIEW=1' \
	'-DENABLE_SPELLCHECK=1' \
	'-DENABLE_CAPTIVE_PORTAL_DETECTION=1' \
	'-DENABLE_SUPERVISED_USERS=1' \
	'-DENABLE_MDNS=1' \
	'-DENABLE_SERVICE_DISCOVERY=1' \
	'-DV8_USE_EXTERNAL_STARTUP_DATA' \
	'-DFULL_SAFE_BROWSING' \
	'-DSAFE_BROWSING_CSD' \
	'-DSAFE_BROWSING_DB_LOCAL' \
	'-DEXPAT_RELATIVE_PATH' \
	'-DWEBRTC_BUILD_LIBEVENT' \
	'-DWEBRTC_POSIX' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE' \
	'-DGTEST_HAS_POSIX_RE=0' \
	'-DGTEST_LANG_CXX11=0' \
	'-DUNIT_TEST' \
	'-DGTEST_HAS_RTTI=0' \
	'-DUSE_LIBPCI=1' \
	'-DUSE_GLIB=1' \
	'-DUSE_NSS_CERTS=1' \
	'-D__STDC_CONSTANT_MACROS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0'

# Flags passed to all source files.
CFLAGS_Release := \
	-fstack-protector \
	--param=ssp-buffer-size=4 \
	-Werror \
	-pthread \
	-fno-strict-aliasing \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-B/data/home/RTChatServer/webrtc-checkout/src//usr/bin \
	-Wno-char-subscripts \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-Wno-strict-overflow \
	-m64 \
	-march=x86-64 \
	--sysroot=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot \
	-O2 \
	-fno-ident \
	-fdata-sections \
	-ffunction-sections \
	-funwind-tables

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-exceptions \
	-fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-std=gnu++11 \
	-Wnon-virtual-dtor \
	-Woverloaded-virtual

INCS_Release := \
	-I$(obj)/gen \
	-I. \
	-Iwebrtc/common_video/include \
	-Iwebrtc/common_video/libyuv/include \
	-Ichromium/src/third_party/libyuv/include \
	-Ichromium/src/third_party/libyuv \
	-Ichromium/src/testing/gtest/include

OBJS := \
	$(obj).target/$(TARGET)/webrtc/modules/video_coding/codecs/vp8/vp8_sequence_coder.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(obj).target/webrtc/modules/video_coding/codecs/vp8/libwebrtc_vp8.a $(obj).target/webrtc/common_video/libcommon_video.a $(obj).target/webrtc/test/libmetrics.a $(obj).target/chromium/src/testing/libgtest.a $(obj).target/webrtc/system_wrappers/libsystem_wrappers.a $(obj).target/webrtc/test/libtest_support_main.a $(obj).target/webrtc/tools/libcommand_line_parser.a $(obj).target/webrtc/libwebrtc_common.a $(obj).target/webrtc/base/librtc_base_approved.a $(obj).target/webrtc/system_wrappers/libcpu_features_linux.a $(builddir)/libyuv.a $(obj).target/chromium/src/third_party/libjpeg_turbo/libjpeg_turbo.a $(obj).target/webrtc/modules/video_coding/utility/libvideo_coding_utility.a $(obj).target/chromium/src/third_party/libvpx/libvpx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_mmx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_sse2.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_ssse3.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_sse4_1.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_avx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_avx2.a $(obj).target/chromium/src/testing/gtest_prod.stamp $(obj).target/webrtc/test/libfield_trial.a $(obj).target/webrtc/system_wrappers/libfield_trial_default.a $(obj).target/webrtc/test/libtest_support.a $(obj).target/chromium/src/testing/libgmock.a $(obj).target/webrtc/base/libgtest_prod.a $(obj).target/third_party/gflags/libgflags.a $(obj).target/webrtc/system_wrappers/libmetrics_default.a $(obj).target/chromium/src/third_party/libyuv/libyuv.a

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-Wl,--fatal-warnings \
	-Wl,-z,defs \
	-pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-fuse-ld=gold \
	-B/data/home/RTChatServer/webrtc-checkout/src//usr/bin \
	-Wl,--disable-new-dtags \
	-m64 \
	--sysroot=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot \
	-L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/lib/x86_64-linux-gnu -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/lib/x86_64-linux-gnu -L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/x86_64-linux-gnu -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/x86_64-linux-gnu -L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/gcc/x86_64-linux-gnu/4.6 -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/gcc/x86_64-linux-gnu/4.6 -L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib \
	-Wl,--threads \
	-Wl,--thread-count=4 \
	-Wl,--detect-odr-violations \
	-Wl,--icf=all

LDFLAGS_Release := \
	-Wl,-z,now \
	-Wl,-z,relro \
	-Wl,--fatal-warnings \
	-Wl,-z,defs \
	-pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-fuse-ld=gold \
	-B/data/home/RTChatServer/webrtc-checkout/src//usr/bin \
	-Wl,--disable-new-dtags \
	-m64 \
	--sysroot=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot \
	-L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/lib/x86_64-linux-gnu -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/lib/x86_64-linux-gnu -L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/x86_64-linux-gnu -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/x86_64-linux-gnu -L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/gcc/x86_64-linux-gnu/4.6 -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib/gcc/x86_64-linux-gnu/4.6 -L/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib -Wl,-rpath-link=/data/home/RTChatServer/webrtc-checkout/src/build/linux/debian_wheezy_amd64-sysroot/usr/lib \
	-Wl,--threads \
	-Wl,--thread-count=4 \
	-Wl,--detect-odr-violations \
	-Wl,--icf=all \
	-Wl,-O1 \
	-Wl,--as-needed \
	-Wl,--gc-sections \
	-Wl,--no-as-needed \
	-lpthread \
	-Wl,--as-needed

LIBS := \
	 \
	-lrt

$(builddir)/vp8_coder: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(builddir)/vp8_coder: LIBS := $(LIBS)
$(builddir)/vp8_coder: LD_INPUTS := $(OBJS) $(obj).target/webrtc/modules/video_coding/codecs/vp8/libwebrtc_vp8.a $(obj).target/webrtc/common_video/libcommon_video.a $(obj).target/webrtc/test/libmetrics.a $(obj).target/chromium/src/testing/libgtest.a $(obj).target/webrtc/system_wrappers/libsystem_wrappers.a $(obj).target/webrtc/test/libtest_support_main.a $(obj).target/webrtc/tools/libcommand_line_parser.a $(obj).target/webrtc/libwebrtc_common.a $(obj).target/webrtc/base/librtc_base_approved.a $(obj).target/webrtc/system_wrappers/libcpu_features_linux.a $(obj).target/chromium/src/third_party/libyuv/libyuv.a $(obj).target/chromium/src/third_party/libjpeg_turbo/libjpeg_turbo.a $(obj).target/webrtc/modules/video_coding/utility/libvideo_coding_utility.a $(obj).target/chromium/src/third_party/libvpx/libvpx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_mmx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_sse2.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_ssse3.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_sse4_1.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_avx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_avx2.a $(obj).target/webrtc/test/libfield_trial.a $(obj).target/webrtc/system_wrappers/libfield_trial_default.a $(obj).target/webrtc/test/libtest_support.a $(obj).target/chromium/src/testing/libgmock.a $(obj).target/webrtc/base/libgtest_prod.a $(obj).target/third_party/gflags/libgflags.a $(obj).target/webrtc/system_wrappers/libmetrics_default.a
$(builddir)/vp8_coder: TOOLSET := $(TOOLSET)
$(builddir)/vp8_coder: $(OBJS) $(obj).target/webrtc/modules/video_coding/codecs/vp8/libwebrtc_vp8.a $(obj).target/webrtc/common_video/libcommon_video.a $(obj).target/webrtc/test/libmetrics.a $(obj).target/chromium/src/testing/libgtest.a $(obj).target/webrtc/system_wrappers/libsystem_wrappers.a $(obj).target/webrtc/test/libtest_support_main.a $(obj).target/webrtc/tools/libcommand_line_parser.a $(obj).target/webrtc/libwebrtc_common.a $(obj).target/webrtc/base/librtc_base_approved.a $(obj).target/webrtc/system_wrappers/libcpu_features_linux.a $(obj).target/chromium/src/third_party/libyuv/libyuv.a $(obj).target/chromium/src/third_party/libjpeg_turbo/libjpeg_turbo.a $(obj).target/webrtc/modules/video_coding/utility/libvideo_coding_utility.a $(obj).target/chromium/src/third_party/libvpx/libvpx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_mmx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_sse2.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_ssse3.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_sse4_1.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_avx.a $(obj).target/chromium/src/third_party/libvpx/libvpx_intrinsics_avx2.a $(obj).target/webrtc/test/libfield_trial.a $(obj).target/webrtc/system_wrappers/libfield_trial_default.a $(obj).target/webrtc/test/libtest_support.a $(obj).target/chromium/src/testing/libgmock.a $(obj).target/webrtc/base/libgtest_prod.a $(obj).target/third_party/gflags/libgflags.a $(obj).target/webrtc/system_wrappers/libmetrics_default.a FORCE_DO_CMD
	$(call do_cmd,link)

all_deps += $(builddir)/vp8_coder
# Add target alias
.PHONY: vp8_coder
vp8_coder: $(builddir)/vp8_coder

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/vp8_coder
