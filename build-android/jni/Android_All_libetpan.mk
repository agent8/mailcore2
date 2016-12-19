CURRENT_DIR := $(call my-dir)
LIBETPAN_DIR := $(CURRENT_DIR)/../../../libetpan

#add in android NDK_Build only
# TODO: change to your NDK Path
ANDROID_NDK := /Users/farmer/Documents/Tools/AndroidSDK/ndk-bundle
# TODO: Add your phone edition 
TARGET_ARCH_ABI := x86
build_version := 4
ctemplate_build_version := 3
cyrus_sasl_build_version := 4
icu4c_build_version := 3
# libetpan_build_version := 6
libxml2_build_version := 3
tidy_html5_build_version := 3
openssl_build_version := 3

CTEMPLATE_PATH := $(CURRENT_DIR)/../third-party/ctemplate-android-$(ctemplate_build_version)
ICU4C_PATH := $(CURRENT_DIR)/../third-party/icu4c-android-$(icu4c_build_version)
# LIBETPAN_PATH := $(CURRENT_DIR)/../third-party/libetpan-android-$(libetpan_build_version)
LIBXML2_PATH := $(CURRENT_DIR)/../third-party/libxml2-android-$(libxml2_build_version)
TIDY_HTML5_PATH := $(CURRENT_DIR)/../third-party/tidy-html5-android-$(tidy_html5_build_version)
OPENSSL_PATH := $(CURRENT_DIR)/../third-party/openssl-android-$(openssl_build_version)
CYRUS_SASL_PATH := $(CURRENT_DIR)/../third-party/cyrus-sasl-android-$(cyrus_sasl_build_version)
#add in android NDK_Build only

src_dir := $(CURRENT_DIR)/../../src
subdirs = \
    core \
    core/basetypes \
    core/abstract \
    core/imap \
    core/nntp \
    core/pop \
    core/provider \
    core/renderer \
    core/rfc822 \
    core/security \
    core/smtp \
    core/zip \
    core/zip/MiniZip \
    async/imap \
    async/nntp \
    async/pop \
    async/smtp \
    java java/native
libetpan_src_files =\
/src/data-types/base64.c \
/src/data-types/carray.c \
/src/data-types/charconv.c \
/src/data-types/chash.c \
/src/data-types/clist.c \
/src/data-types/connect.c \
/src/data-types/mail_cache_db.c \
/src/data-types/maillock.c \
/src/data-types/mailsasl.c \
/src/data-types/mailsem.c \
/src/data-types/mailstream.c \
/src/data-types/mailstream_cancel.c \
/src/data-types/mailstream_cfstream.c \
/src/data-types/mailstream_compress.c \
/src/data-types/mailstream_helper.c \
/src/data-types/mailstream_low.c \
/src/data-types/mailstream_socket.c \
/src/data-types/mailstream_ssl.c \
/src/data-types/md5.c \
/src/data-types/mmapstring.c \
/src/data-types/timeutils.c \
/src/low-level/imap/acl.c \
/src/low-level/imap/acl_parser.c \
/src/low-level/imap/acl_sender.c \
/src/low-level/imap/acl_types.c \
/src/low-level/imap/annotatemore.c \
/src/low-level/imap/annotatemore_parser.c \
/src/low-level/imap/annotatemore_sender.c \
/src/low-level/imap/annotatemore_types.c \
/src/low-level/imap/condstore.c \
/src/low-level/imap/condstore_types.c \
/src/low-level/imap/enable.c \
/src/low-level/imap/idle.c \
/src/low-level/imap/mailimap.c \
/src/low-level/imap/mailimap_compress.c \
/src/low-level/imap/mailimap_extension.c \
/src/low-level/imap/mailimap_helper.c \
/src/low-level/imap/mailimap_id.c \
/src/low-level/imap/mailimap_id_parser.c \
/src/low-level/imap/mailimap_id_sender.c \
/src/low-level/imap/mailimap_id_types.c \
/src/low-level/imap/mailimap_keywords.c \
/src/low-level/imap/mailimap_oauth2.c \
/src/low-level/imap/mailimap_parser.c \
/src/low-level/imap/mailimap_print.c \
/src/low-level/imap/mailimap_sender.c \
/src/low-level/imap/mailimap_socket.c \
/src/low-level/imap/mailimap_sort.c \
/src/low-level/imap/mailimap_sort_types.c \
/src/low-level/imap/mailimap_ssl.c \
/src/low-level/imap/mailimap_types.c \
/src/low-level/imap/mailimap_types_helper.c \
/src/low-level/imap/namespace.c \
/src/low-level/imap/namespace_parser.c \
/src/low-level/imap/namespace_sender.c \
/src/low-level/imap/namespace_types.c \
/src/low-level/imap/qresync.c \
/src/low-level/imap/qresync_types.c \
/src/low-level/imap/quota.c \
/src/low-level/imap/quota_parser.c \
/src/low-level/imap/quota_sender.c \
/src/low-level/imap/quota_types.c \
/src/low-level/imap/uidplus.c \
/src/low-level/imap/uidplus_parser.c \
/src/low-level/imap/uidplus_sender.c \
/src/low-level/imap/uidplus_types.c \
/src/low-level/imap/xgmlabels.c \
/src/low-level/imap/xgmmsgid.c \
/src/low-level/imap/xgmthrid.c \
/src/low-level/imap/xlist.c \
/src/low-level/imf/mailimf.c \
/src/low-level/imf/mailimf_types.c \
/src/low-level/imf/mailimf_types_helper.c \
/src/low-level/imf/mailimf_write_file.c \
/src/low-level/imf/mailimf_write_generic.c \
/src/low-level/imf/mailimf_write_mem.c \
/src/low-level/mime/mailmime.c \
/src/low-level/mime/mailmime_content.c \
/src/low-level/mime/mailmime_decode.c \
/src/low-level/mime/mailmime_disposition.c \
/src/low-level/mime/mailmime_types.c \
/src/low-level/mime/mailmime_types_helper.c \
/src/low-level/mime/mailmime_write_file.c \
/src/low-level/mime/mailmime_write_generic.c \
/src/low-level/mime/mailmime_write_mem.c \
/src/low-level/nntp/newsnntp.c \
/src/low-level/nntp/newsnntp_socket.c \
/src/low-level/nntp/newsnntp_ssl.c \
/src/low-level/pop3/mailpop3.c \
/src/low-level/pop3/mailpop3_helper.c \
/src/low-level/pop3/mailpop3_socket.c \
/src/low-level/pop3/mailpop3_ssl.c \
/src/low-level/smtp/mailsmtp.c \
/src/low-level/smtp/mailsmtp_helper.c \
/src/low-level/smtp/mailsmtp_oauth2.c \
/src/low-level/smtp/mailsmtp_socket.c \
/src/low-level/smtp/mailsmtp_ssl.c \
/src/main/libetpan_version.c \
/src/driver/implementation/data-message/data_message_driver.c \
/src/driver/interface/maildriver.c \
/src/driver/interface/maildriver_tools.c \
/src/driver/interface/maildriver_types.c \
/src/driver/interface/maildriver_types_helper.c \
/src/driver/interface/mailfolder.c \
/src/driver/interface/mailmessage.c \
/src/driver/interface/mailmessage_tools.c \
/src/driver/interface/mailmessage_types.c \
/src/driver/interface/mailstorage.c \
/src/driver/interface/mailstorage_tools.c
libetpan_c_includes = \
/src \
/src/data-types \
/src/low-level \
/src/low-level/imap \
/src/low-level/imf \
/src/low-level/mime \
/src/low-level/nntp \
/src/low-level/pop3 \
/src/low-level/smtp \
/src/main \
/src/driver/implementation/data-message \
/src/driver/interface
LIBETPAN_LOCAL_C_INCLUDES = $(addprefix $(LIBETPAN_DIR), $(libetpan_c_includes)) \
  $(LIBETPAN_DIR)/build-android/include $(LIBETPAN_DIR)/build-android/include/libetpan
includes = \
    $(CURRENT_DIR)/../include \
    $(CTEMPLATE_PATH)/include \
    $(ICU4C_PATH)/include \
    $(LIBXML2_PATH)/include \
    $(TIDY_HTML5_PATH)/include \
    $(OPENSSL_PATH)/include \
    $(CYRUS_SASL_PATH)/include \
    $(ANDROID_NDK)/sources/cxx-stl/gnu-libstdc++/4.9/include \
    $(ANDROID_NDK)/sources/cxx-stl/gnu-libstdc++/4.9/libs/$(TARGET_ARCH_ABI)/include \
    $(addprefix $(src_dir)/, $(subdirs)) \
    $(LIBETPAN_LOCAL_C_INCLUDES)

core_excludes = MCWin32.cpp MCStringWin32.cpp MCMainThreadWin32.cpp MCMainThreadGTK.cpp
core_src_files := $(filter-out \
    $(addprefix $(src_dir)/core/basetypes/, $(core_excludes)), \
    $(wildcard $(src_dir)/core/basetypes/*.cpp) $(wildcard $(src_dir)/core/basetypes/*.c))

abstract_src_files := $(wildcard $(src_dir)/core/abstract/*.cpp)
imap_src_files := $(wildcard $(src_dir)/core/imap/*.cpp)
nntp_src_files := $(wildcard $(src_dir)/core/nntp/*.cpp)
pop_src_files := $(wildcard $(src_dir)/core/pop/*.cpp)
provider_src_files := $(wildcard $(src_dir)/core/provider/*.cpp)
renderer_src_files := $(wildcard $(src_dir)/core/renderer/*.cpp)
rfc822_src_files := $(wildcard $(src_dir)/core/rfc822/*.cpp)
security_src_files := $(wildcard $(src_dir)/core/security/*.cpp)
smtp_src_files := $(wildcard $(src_dir)/core/smtp/*.cpp)
zip_src_files := $(wildcard $(src_dir)/core/zip/*.cpp)
minizip_src_files := \
    $(src_dir)/core/zip/MiniZip/ioapi.c \
    $(src_dir)/core/zip/MiniZip/unzip.c \
    $(src_dir)/core/zip/MiniZip/zip.c
async_imap_src_files := $(wildcard $(src_dir)/async/imap/*.cpp)
async_nntp_src_files := $(wildcard $(src_dir)/async/nntp/*.cpp)
async_pop_src_files := $(wildcard $(src_dir)/async/pop/*.cpp)
async_smtp_src_files := $(wildcard $(src_dir)/async/smtp/*.cpp)
jni_src_files := $(wildcard $(src_dir)/java/native/*.cpp) $(wildcard $(src_dir)/java/*.cpp)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := MailCore
# LOCAL_C_INCLUDES := $(includes)
# LOCAL_SRC_FILES := $(core_src_files) $(abstract_src_files) $(imap_src_files) $(nntp_src_files) \
#   $(pop_src_files) $(provider_src_files) $(renderer_src_files) $(rfc822_src_files) \
#   $(security_src_files) $(smtp_src_files) $(zip_src_files) $(minizip_src_files) \
#   $(async_imap_src_files) $(async_nntp_src_files) $(async_pop_src_files) $(async_smtp_src_files)
# LOCAL_CPPFLAGS := -frtti
# LOCAL_CFLAGS := -DNOCRYPT
# include $(BUILD_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := etpan
# LOCAL_SRC_FILES := $(LIBETPAN_PATH)/libs/$(TARGET_ARCH_ABI)/libetpan.a
# include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := crypto
LOCAL_SRC_FILES := $(OPENSSL_PATH)/libs/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := ssl
LOCAL_SRC_FILES := $(OPENSSL_PATH)/libs/$(TARGET_ARCH_ABI)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := icu4c
LOCAL_SRC_FILES := $(ICU4C_PATH)/libs/$(TARGET_ARCH_ABI)/libicu4c.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := xml2
LOCAL_SRC_FILES := $(LIBXML2_PATH)/libs/$(TARGET_ARCH_ABI)/libxml2.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := tidy
LOCAL_SRC_FILES := $(TIDY_HTML5_PATH)/libs/$(TARGET_ARCH_ABI)/libtidy.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := ctemplate
LOCAL_SRC_FILES := $(CTEMPLATE_PATH)/libs/$(TARGET_ARCH_ABI)/libctemplate.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := sasl2
LOCAL_SRC_FILES := $(CYRUS_SASL_PATH)/libs/$(TARGET_ARCH_ABI)/libsasl2.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := MailCore

LOCAL_C_INCLUDES := $(includes)
LIBETPAN_LOCAL_SRC_FILES := $(addprefix $(LIBETPAN_DIR), $(libetpan_src_files))
LOCAL_SRC_FILES := \
    $(jni_src_files) \
    $(core_src_files) $(abstract_src_files) $(imap_src_files) $(nntp_src_files) \
    $(pop_src_files) $(provider_src_files) $(renderer_src_files) $(rfc822_src_files) \
    $(security_src_files) $(smtp_src_files) $(zip_src_files) $(minizip_src_files) \
    $(async_imap_src_files) $(async_nntp_src_files) $(async_pop_src_files) $(async_smtp_src_files) \
    $(LIBETPAN_LOCAL_SRC_FILES)
NDK_TOOLCHAIN_VERSION := clang
LOCAL_CPPFLAGS := -frtti
LOCAL_CFLAGS := -DNOCRYPT -DHAVE_CONFIG_H=1
# LOCAL_LDLIBS := -lz -llog \
#      -lc++_shared -L$(ANDROID_NDK)/sources/cxx-stl/llvm-libc++/libs/$(TARGET_ARCH_ABI)
LOCAL_LDLIBS := -lz -llog \
     -lgnustl_shared -L$(ANDROID_NDK)/sources/cxx-stl/gnu-libstdc++/4.9/libs/$(TARGET_ARCH_ABI)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_STATIC_LIBRARIES := sasl2 ssl crypto icu4c xml2 tidy ctemplate
include $(BUILD_SHARED_LIBRARY)
