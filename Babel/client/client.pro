TEMPLATE        =       app
TARGET          =       client
QT              +=      core widgets gui network

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui

QMAKE_CXXFLAGS	+=	-Wall

INCLUDEPATH     +=      .                                       		\
                        includes                                		\
			includes/Network					\
			includes/Audio						\
			includes/Mutex						\
			includes/GUI						\
			includes/ServerCommunication				\
			../shared/includes					\
                        dependencies/includes					\
			build							\
			build/ui						\
			build/moc

HEADERS         +=      ../shared/includes/IClientSocket.hpp    		\
                        ../shared/includes/IServerSocket.hpp    		\
			../shared/includes/IMutex.hpp				\
                        includes/Network/SocketException.hpp    		\
                        includes/Network/TcpClient.hpp          		\
			includes/Network/UdpClient.hpp				\
			includes/Mutex/Mutex.hpp				\
			includes/Mutex/ScopedLock.hpp				\
                        includes/Audio/ISoundDevice.hpp         		\
			includes/Audio/Sound.hpp				\
                        includes/Audio/SoundException.hpp       		\
                        includes/Audio/SoundInputDevice.hpp     		\
                        includes/Audio/SoundOutputDevice.hpp    		\
			includes/Audio/AudioManager.hpp				\
			includes/Audio/SoundPacketBuilder.hpp			\
			includes/Audio/EncodeManager.hpp			\
			includes/Audio/CallManager.hpp				\
			includes/ServerCommunication/ServerCommunication.hpp	\
			includes/ServerCommunication/CommandPacketBuilder.hpp	\
			includes/GUI/BabelMainWindow.hpp			\
			includes/Contact.hpp					\
			includes/Babel.hpp

HEADERS		+=	dependencies/includes/portaudio.h

SOURCES         +=      sources/main.cpp                        		\
                        sources/Network/SocketException.cpp     		\
                        sources/Network/TcpClient.cpp           		\
			sources/Network/UdpClient.cpp				\
                        sources/Mutex/ScopedLock.cpp				\
			sources/Mutex/Mutex.cpp					\
                        sources/Audio/SoundException.cpp        		\
                        sources/Audio/SoundInputDevice.cpp      		\
                        sources/Audio/SoundOutputDevice.cpp     		\
			sources/Audio/EncodeManager.cpp				\
			sources/Audio/AudioManager.cpp				\
			sources/Audio/SoundPacketBuilder.cpp			\
			sources/Audio/CallManager.cpp				\
			sources/GUI/BabelMainWindow.cpp				\
			sources/ServerCommunication/ServerCommunication.cpp	\
			sources/ServerCommunication/CommandPacketBuilder.cpp	\
			sources/Babel.cpp					\
			sources/Contact.cpp

FORMS		+=	forms/BabelMainWindow.ui

RESOURCES	+=	resources/BabelMainWindow.qrc

win32:LIBS      +=      -ldependencies/libs/portaudio_x86	\
			-ldependencies/libs/celt 		\
			-ldependencies/libs/opus 		\
			-ldependencies/libs/silk_common 	\
			-ldependencies/libs/silk_fixed		\
			-ldependencies/libs/silk_float

unix:LIBS       +=      -Ldependencies -lopus                   \
                        -Ldependencies -lportaudio
