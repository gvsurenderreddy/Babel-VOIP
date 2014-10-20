# Find Boost library.

# Try to use qmake variable's value.
_BOOST_ROOT = $$BOOST_ROOT
isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" qmake value not detected...)

    # Try to use the system environment value.
    _BOOST_ROOT = $$(BOOST_ROOT)
}

isEmpty(_BOOST_ROOT) {
    message(\"Boost Library\" environment variable not detected... => `qmake BOOST_ROOT=C:\Boost\1.56.0\VC\12.0`)
    !build_pass:error(Please set the environment variable `BOOST_ROOT`. For example, BOOST_ROOT=c:\\boost_1_53_0)
} else {
    message(\"Boost Library\" detected in BOOST_ROOT = \"$$_BOOST_ROOT\")
    INCLUDEPATH += $$_BOOST_ROOT
	LIBS += -L$$_BOOST_ROOT/stage/lib
}

CONFIG			+=		console
TEMPLATE        =       app
TARGET          =       server

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui

QMAKE_CXXFLAGS  +=      -Wall

INCLUDEPATH     +=      .                                       \
						../shared/includes						\
                        includes                                \
                        dependencies/includes					\
						build									\
						build/ui								\
						build/moc
						
HEADERS         +=      ../shared/includes/IClientSocket.hpp    \
                        ../shared/includes/IServerSocket.hpp    \
						includes/BoostTcpClient.hpp             \
						includes/BoostTcpServer.hpp             \
						includes/ServerManager.hpp

SOURCES         +=      sources/main.cpp                        \
                        sources/BoostTcpClient.cpp              \
                        sources/BoostTcpServer.cpp              \
                        sources/ServerManager.cpp

DEFINES			+=		_AFXDLL _MBCS

win32:DEFINES	+=		_WIN32_WINNT=0x0501