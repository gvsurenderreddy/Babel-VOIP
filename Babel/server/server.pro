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
	LIBPATH += $$_BOOST_ROOT/stage/lib
	
}

CONFIG			+=		console
TEMPLATE        =       app
TARGET          =       server

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui

QMAKE_CXXFLAGS  +=      -Wall -D_SCL_SECURE_NO_WARNINGS /MP

QMAKE_CFLAGS_WARN_ON -= -W3
QMAKE_CFLAGS_WARN_ON += -W2

QMAKE_CXXFLAGS_WARN_ON -= -W3
QMAKE_CXXFLAGS_WARN_ON += -W2

INCLUDEPATH     +=      .                                       \
						../shared/includes						\
                        includes                                \
                        dependencies/includes					\
						build									\
						build/ui								\
						build/moc								\
						includes/Command
						
HEADERS         +=      ../shared/includes/IClientSocket.hpp    \
                        ../shared/includes/IServerSocket.hpp    \
						includes/TcpClient.hpp             		\
						includes/TcpServer.hpp             		\
						includes/Client.hpp						\
						includes/BabelServer.hpp				\
						includes/Command/ICommand.hpp			\
						includes/Command/CommandUpdate.hpp		\
						includes/Command/CommandAdd.hpp			\
						includes/Command/CommandReg.hpp			\
						includes/Command/CommandLog.hpp			\
						includes/Command/CommandList.hpp		\
						includes/Command/CommandShow.hpp		\
						includes/Command/CommandAcceptAdd.hpp	\
						includes/Command/CommandDel.hpp			\
						includes/Command/CommandExit.hpp		\
						includes/Command/CommandSend.hpp		\
						includes/Command/CommandCall.hpp		\
						includes/Command/CommandAcceptCall.hpp	\
						includes/Command/CommandCloseCall.hpp	\
						includes/Command/CommandErr.hpp			\
						includes/Command/HandleCmd.hpp			\
						includes/Command/ErrorCodes.hpp			\
						includes/Database.hpp					\
						includes/Factory.hpp

SOURCES         +=      sources/main.cpp                        \
                        sources/TcpClient.cpp              		\
                        sources/TcpServer.cpp              		\
						sources/Client.cpp						\
                        sources/BabelServer.cpp					\
						sources/Command/ICommand.cpp			\
						sources/Command/CommandUpdate.cpp		\
						sources/Command/CommandAdd.cpp			\
						sources/Command/CommandReg.cpp			\
						sources/Command/CommandLog.cpp			\
						sources/Command/CommandList.cpp			\
						sources/Command/CommandShow.cpp			\
						sources/Command/CommandAcceptAdd.cpp	\
						sources/Command/CommandDel.cpp			\
						sources/Command/CommandExit.cpp			\
						sources/Command/CommandSend.cpp			\
						sources/Command/CommandCall.cpp			\
						sources/Command/CommandAcceptCall.cpp	\
						sources/Command/CommandCloseCall.cpp	\
						sources/Command/CommandErr.cpp			\
						sources/Command/HandleCmd.cpp			\
						sources/Factory.cpp


CharacterSet = 1

DEFINES			+=		_AFXDLL _MBCS UNICODE

win32:DEFINES	+=		_WIN32_WINNT=0x0501 _CRT_SECURE_NO_WARNINGS
