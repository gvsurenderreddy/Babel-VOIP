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
                        includes/ISoundDevice.hpp               \
                        includes/SocketException.hpp            \
                        includes/SoundException.hpp       	\
                        includes/SoundOutputDevice.hpp          \
                        includes/UdpClient.hpp			\
			includes/IMutex.hpp			\
			includes/Mutex.hpp			\
			includes/ScopedLock.hpp			\
			includes/Sound.hpp			\
			includes/ReceiveSound.hpp
			
HEADERS		+=	dependencies/includes/portaudio.h

SOURCES         +=      sources/main.cpp                        \
                        sources/SocketException.cpp             \
                        sources/SoundException.cpp        	\
                        sources/SoundOutputDevice.cpp           \
                        sources/UdpClient.cpp			\
                        sources/ScopedLock.cpp			\
			sources/Mutex.cpp			\
			sources/ReceiveSound.cpp

FORMS		+=	forms/SimpleWindow.ui

win32:LIBS      +=      -ldependencies/libs/portaudio_x86	\
			-ldependencies/libs/celt 		\
			-ldependencies/libs/opus 		\
			-ldependencies/libs/silk_common 	\
			-ldependencies/libs/silk_fixed		\
			-ldependencies/libs/silk_float
