TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../include/AsyncHttpClient.h \
    ../include/Buffer.h \
    ../include/Channel.h \
    ../include/Event.h \
    ../include/EventLoop.h \
    ../include/EventLoopThread.h \
    ../include/EventLoopThreadPool.h \
    ../include/HttpContext.h \
    ../include/HttpMessage.h \
    ../include/HttpParser.h \
    ../include/HttpResponseWriter.h \
    ../include/HttpServer.h \
    ../include/HttpService.h \
    ../include/Status.h \
    ../include/TcpClient.h \
    ../include/TcpServer.h \
    ../include/ThreadLocalStorage.h \
    ../include/UdpClient.h \
    ../include/UdpServer.h \
    ../include/WebSocketChannel.h \
    ../include/WebSocketClient.h \
    ../include/WebSocketParser.h \
    ../include/WebSocketServer.h \
    ../include/axios.h \
    ../include/base64.h \
    ../include/hasync.h \
    ../include/hatomic.h \
    ../include/hbase.h \
    ../include/hbuf.h \
    ../include/hconfig.h \
    ../include/hdef.h \
    ../include/hdir.h \
    ../include/hendian.h \
    ../include/herr.h \
    ../include/hexport.h \
    ../include/hfile.h \
    ../include/hlog.h \
    ../include/hloop.h \
    ../include/hmain.h \
    ../include/hmap.h \
    ../include/hmath.h \
    ../include/hmutex.h \
    ../include/hobjectpool.h \
    ../include/hpath.h \
    ../include/hplatform.h \
    ../include/hproc.h \
    ../include/hscope.h \
    ../include/hsocket.h \
    ../include/hssl.h \
    ../include/hstring.h \
    ../include/hsysinfo.h \
    ../include/hthread.h \
    ../include/hthreadpool.h \
    ../include/htime.h \
    ../include/http_client.h \
    ../include/http_content.h \
    ../include/httpdef.h \
    ../include/hurl.h \
    ../include/hv.h \
    ../include/hversion.h \
    ../include/ifconfig.h \
    ../include/iniparser.h \
    ../include/json.hpp \
    ../include/md5.h \
    ../include/nlog.h \
    ../include/requests.h \
    ../include/sha1.h \
    ../include/singleton.h \
    ../include/wsdef.h \
    ../inter_sock.hpp

unix:!macx: LIBS += -L$$PWD/../lib/ -lhv

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
