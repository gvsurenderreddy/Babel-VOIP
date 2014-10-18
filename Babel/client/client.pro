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
			includes/Network			\
			includes/Audio				\
			includes/Mutex				\
			../shared/includes			\
                        dependencies/includes			\
			build					\
			build/ui				\
			build/moc

HEADERS         +=      ../shared/includes/IClientSocket.hpp    \
                        ../shared/includes/IServerSocket.hpp    \
			../shared/includes/IMutex.hpp		\
                        includes/Network/SocketException.hpp    \
                        includes/Network/TcpClient.hpp          \
                        includes/Network/TcpServer.hpp          \
			includes/Network/UdpClient.hpp		\
			includes/Mutex/Mutex.hpp		\
			includes/Mutex/ScopedLock.hpp		\
			includes/SimpleWindow.hpp		\
                        includes/Audio/ISoundDevice.hpp         \
			includes/Audio/Sound.hpp		\
                        includes/Audio/SoundException.hpp       \
                        includes/Audio/SoundInputDevice.hpp     \
                        includes/Audio/SoundOutputDevice.hpp    \
			includes/Audio/EncodeManager.hpp

HEADERS		+=	dependencies/includes/portaudio.h

SOURCES         +=      sources/main.cpp                        \
			sources/SimpleWindow.cpp		\
                        sources/Network/SocketException.cpp     \
                        sources/Network/TcpClient.cpp           \
			sources/Network/UdpClient.cpp		\
                        sources/Network/TcpServer.cpp		\
			sources/Mutex/ScopedLock.cpp		\
			sources/Mutex/Mutex.cpp			\
                        sources/Audio/SoundException.cpp        \
                        sources/Audio/SoundInputDevice.cpp      \
                        sources/Audio/SoundOutputDevice.cpp     \
			sources/Audio/EncodeManager.cpp

FORMS		+=	forms/SimpleWindow.ui

win32:LIBS      +=      -ldependencies/libs/portaudio_x86	\
			-ldependencies/libs/celt 		\
			-ldependencies/libs/opus 		\
			-ldependencies/libs/silk_common 	\
			-ldependencies/libs/silk_fixed		\
			-ldependencies/libs/silk_float

unix:LIBS       +=      -Ldependencies -lopus                     \
                        -Ldependencies -lportaudio
