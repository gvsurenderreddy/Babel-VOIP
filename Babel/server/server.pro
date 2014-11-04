_BOOST_ROOT = $$BOOST_ROOT
isEmpty(_BOOST_ROOT) {
    message(Boost Library qmake value not detected...)
    _BOOST_ROOT = $$(BOOST_ROOT)
}
isEmpty(_BOOST_ROOT) {
    message(Boost Library environment variable not detected... try below)
    message(qmake BOOST_ROOT=C:\\Boost\\1.56.0\\VC\\12.0 -tp vc)
} else {
    message(Boost Library detected in BOOST_ROOT = $$_BOOST_ROOT)
    INCLUDEPATH += $$_BOOST_ROOT
	win32:LIBS += -L$$_BOOST_ROOT/stage/lib
	win32:QMAKE_LIBDIR += $$_BOOST_ROOT/stage/lib
	unix:LIBS += -L$$_BOOST_ROOT/lib
	unix:QMAKE_LIBDIR += $$_BOOST_ROOT/lib
}

unix:LIBS += -lboost_system -lboost_serialization -lboost_filesystem
unix::CXX = clang++

CONFIG			+=		console c++11
TEMPLATE        =       app
TARGET          =       server

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui

win32:QMAKE_CXXFLAGS	+=	-Wall -D_SCL_SECURE_NO_WARNINGS /MP
unix:QMAKE_CXXFLAGS		+=	-Wall -std=gnu++11 -g

win32:QMAKE_CFLAGS_WARN_ON -= -W3
win32:QMAKE_CFLAGS_WARN_ON += -W2

win32:QMAKE_CXXFLAGS_WARN_ON -= -W3
win32:QMAKE_CXXFLAGS_WARN_ON += -W2

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
						includes/Command/ErrorCode.hpp			\
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
						sources/Command/ErrorCode.cpp			\
						sources/Factory.cpp


CharacterSet = 1

DEFINES			+=		_AFXDLL _MBCS UNICODE

win32:DEFINES	+=		_WIN32_WINNT=0x0501 _CRT_SECURE_NO_WARNINGS
