TEMPLATE        =       app
TARGET          =       client
QT              +=      core widgets gui network

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui

QMAKE_CXXFLAGS	+=	-Wall

INCLUDEPATH     +=      .                                       \
                        includes                                \
                        dependencies/includes			\
			build					\
			build/ui				\
			build/moc

HEADERS         +=      includes/IClientSocket.hpp              \
                        includes/IServerSocket.hpp              \
                        includes/ISoundDevice.hpp               \
                        includes/SocketException.hpp            \
                        includes/SoundException.hpp       	\
                        includes/SoundInputDevice.hpp           \
                        includes/SoundOutputDevice.hpp          \
                        includes/TcpClient.hpp                  \
                        includes/TcpServer.hpp                  \
			includes/UdpClient.hpp			\
			includes/IMutex.hpp			\
			includes/Mutex.hpp			\
			includes/ScopedLock.hpp			\
			includes/SimpleWindow.hpp		\
			includes/Sound.hpp			\
			includes/ReceiveSound.hpp	\
			includes/myThread.hpp	\
			includes/EncodeManager.hpp

HEADERS		+=	dependencies/includes/portaudio.h

SOURCES         +=      sources/main.cpp                        \
                        sources/SocketException.cpp             \
                        sources/SoundException.cpp        	\
                        sources/SoundInputDevice.cpp            \
                        sources/SoundOutputDevice.cpp           \
                        sources/TcpClient.cpp                   \
			sources/UdpClient.cpp			\
                        sources/TcpServer.cpp			\
			sources/ScopedLock.cpp			\
			sources/Mutex.cpp			\
			sources/SimpleWindow.cpp		\
			sources/ReceiveSound.cpp		\
			sources/myThread.cpp			\
			sources/EncodeManager.cpp

FORMS		+=	forms/SimpleWindow.ui

win32:LIBS      +=      -ldependencies/libs/portaudio_x86	\
			-ldependencies/libs/celt 		\
			-ldependencies/libs/opus 		\
			-ldependencies/libs/silk_common 	\
			-ldependencies/libs/silk_fixed		\
			-ldependencies/libs/silk_float
