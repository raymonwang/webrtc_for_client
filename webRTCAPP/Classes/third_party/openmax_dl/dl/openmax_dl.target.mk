# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := openmax_dl
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
	'-DBIG_FFT_TABLE' \
	'-DUSE_LIBPCI=1' \
	'-DUSE_GLIB=1' \
	'-DUSE_NSS_CERTS=1' \
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
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Xclang \
	-load \
	-Xclang \
	/data/home/RTChatServer/webrtc-checkout/src/third_party/llvm-build/Release+Asserts/lib/libFindBadConstructs.so \
	-Xclang \
	-add-plugin \
	-Xclang \
	find-bad-constructs \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	check-templates \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	follow-macro-expansion \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	check-implicit-copy-ctors \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	check-ipc \
	-B/data/home/RTChatServer/webrtc-checkout/src//usr/bin \
	-Wno-char-subscripts \
	-Wno-unused-variable \
	-msse2 \
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
	-Wno-deprecated

INCS_Debug := \
	-Ichromium/src/third_party/openmax_dl \
	-I$(obj)/gen

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
	'-DBIG_FFT_TABLE' \
	'-DUSE_LIBPCI=1' \
	'-DUSE_GLIB=1' \
	'-DUSE_NSS_CERTS=1' \
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
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Xclang \
	-load \
	-Xclang \
	/data/home/RTChatServer/webrtc-checkout/src/third_party/llvm-build/Release+Asserts/lib/libFindBadConstructs.so \
	-Xclang \
	-add-plugin \
	-Xclang \
	find-bad-constructs \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	check-templates \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	follow-macro-expansion \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	check-implicit-copy-ctors \
	-Xclang \
	-plugin-arg-find-bad-constructs \
	-Xclang \
	check-ipc \
	-B/data/home/RTChatServer/webrtc-checkout/src//usr/bin \
	-Wno-char-subscripts \
	-Wno-unused-variable \
	-msse2 \
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
	-Wno-deprecated

INCS_Release := \
	-Ichromium/src/third_party/openmax_dl \
	-I$(obj)/gen

OBJS := \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/armSP_FFT_F32TwiddleTable.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/omxSP_FFTFwd_RToCCS_F32_Sfs.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/omxSP_FFTGetBufSize_R_F32.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/omxSP_FFTInit_R_F32.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/omxSP_FFTInv_CCSToR_F32_Sfs.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix2_fs.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix2_ls.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix2_ls_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix2_ms.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix4_fs.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix4_fs_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix4_ls.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix4_ls_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix4_ms.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Fwd_Radix4_ms_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix2_fs.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix2_ls.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix2_ls_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix2_ms.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix4_fs.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix4_fs_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix4_ls.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix4_ls_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix4_ms.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_CToC_FC32_Inv_Radix4_ms_sse.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_F32_radix2_kernel.o \
	$(obj).target/$(TARGET)/chromium/src/third_party/openmax_dl/dl/sp/src/x86/x86SP_FFT_F32_radix4_kernel.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

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
	

$(obj).target/chromium/src/third_party/openmax_dl/dl/libopenmax_dl.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/chromium/src/third_party/openmax_dl/dl/libopenmax_dl.a: LIBS := $(LIBS)
$(obj).target/chromium/src/third_party/openmax_dl/dl/libopenmax_dl.a: TOOLSET := $(TOOLSET)
$(obj).target/chromium/src/third_party/openmax_dl/dl/libopenmax_dl.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink_thin)

all_deps += $(obj).target/chromium/src/third_party/openmax_dl/dl/libopenmax_dl.a
# Add target alias
.PHONY: openmax_dl
openmax_dl: $(obj).target/chromium/src/third_party/openmax_dl/dl/libopenmax_dl.a

# Add target alias to "all" target.
.PHONY: all
all: openmax_dl
