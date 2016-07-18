AUTOMAKE_OPTIONS = foreign

noinst_LIBRARIES = libwebrtc_base.a
libwebrtc_base_a_SOURCES = asyncfile.cc \
asyncinvoker.cc \
asyncsocket.cc \
asynctcpsocket.cc \
asyncudpsocket.cc \
autodetectproxy.cc \
base64.cc \
common.cc \
crc32.cc \
diskcache.cc \
fileutils.cc \
firewallsocketserver.cc \
flags.cc \
helpers.cc \
httpbase.cc \
httpclient.cc \
httpcommon.cc \
httprequest.cc \
ipaddress.cc \
messagedigest.cc \
messagehandler.cc \
messagequeue.cc \
nethelpers.cc \
network.cc \
openssladapter.cc \
openssldigest.cc \
opensslidentity.cc \
opensslstreamadapter.cc \
pathutils.cc \
physicalsocketserver.cc \
proxydetect.cc \
proxyinfo.cc \
ratelimiter.cc \
sha1.cc \
sharedexclusivelock.cc \
signalthread.cc \
socketadapters.cc \
socketaddress.cc \
socketaddresspair.cc \
socketpool.cc \
socketstream.cc \
ssladapter.cc \
sslfingerprint.cc \
sslidentity.cc \
sslsocketfactory.cc \
sslstreamadapter.cc \
stream.cc \
task.cc \
taskparent.cc \
taskrunner.cc \
thread.cc \
timing.cc \
urlencode.cc \
worker.cc \
bandwidthsmoother.cc \
httpserver.cc \
json.cc \
multipart.cc \
natserver.cc \
natsocketfactory.cc \
nattypes.cc \
optionsfile.cc \
profiler.cc \
proxyserver.cc \
testclient.cc \
transformadapter.cc \
versionparsing.cc \
virtualsocketserver.cc \
dbus.cc \
libdbusglibsymboltable.cc \
linuxfdwalk.c \
latebindingsymboltable.cc \
posix.cc \
x11windowpicker.cc \
unixfilesystem.cc \
linux.cc

INCLUDES = -I../../ -I../../third_party/jsoncpp/source/include
AM_CXXFLAGS = -DWEBRTC_POSIX -std=gnu++11 -fPIC
AM_CXXFLAGS += -DFEATURE_ENABLE_SSL -DSSL_USE_OPENSSL
