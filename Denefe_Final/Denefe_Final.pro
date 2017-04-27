TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    docparser.cpp \
    findpaths.cpp

HEADERS += \
    avltree.h \
    docparser.h \
    dsvector.h \
    stemmer.h \
    docledger.h \
    word.h \
    findpaths.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/release/ -lpodofo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/debug/ -lpodofo
else:unix: LIBS += -L$$PWD/../../../../../../usr/lib/ -lpodofo

INCLUDEPATH += $$PWD/../../../../../../usr/include/podofo
DEPENDPATH += $$PWD/../../../../../../usr/include/podofo

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/release/ -lfontconfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/debug/ -lfontconfig
else:unix: LIBS += -L$$PWD/../../../../../../usr/lib/x86_64-linux-gnu/ -lfontconfig

INCLUDEPATH += $$PWD/../../../../../../usr/include/fontconfig
DEPENDPATH += $$PWD/../../../../../../usr/include/fontconfig

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu/release/libfontconfig.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu/debug/libfontconfig.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu/release/fontconfig.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu/debug/fontconfig.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../usr/lib/x86_64-linux-gnu/libfontconfig.a


