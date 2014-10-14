TEMPLATE        =       app
TARGET          =       client
QT              +=      core gui network

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui

INCLUDEPATH     +=      .                                       \
                        includes                                \
                        dependencies/includes

HEADERS         +=      includes/IClientSocket.hpp              \
                        includes/IServerSocket.hpp              \
                        includes/ISoundDevice.hpp               \
                        includes/SocketException.hpp            \
                        includes/SoundDeviceException.hpp       \
                        includes/SoundInputDevice.hpp           \
                        includes/SoundOutputDevice.hpp          \
                        includes/TcpClient.hpp                  \
                        includes/TcpServer.hpp                  \
			includes/UdpClient.hpp			\
			includes/IMutex.hpp			\
			includes/Mutex.hpp			\
			includes/ScopedLock.hpp			\
                        dependencies/includes/portaudio.h

SOURCES         +=      sources/main.cpp                        \
                        sources/SocketException.cpp             \
                        sources/SoundDeviceException.cpp        \
                        sources/SoundInputDevice.cpp            \
                        sources/SoundOutputDevice.cpp           \
                        sources/TcpClient.cpp                   \
			sources/UdpClient.cpp			\
                        sources/TcpServer.cpp			\
			sources/ScopedLock.cpp			\
			sources/Mutex.cpp

win32:LIBS      +=      dependencies/libs/portaudio_x86.lib
