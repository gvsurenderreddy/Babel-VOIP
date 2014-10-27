TEMPLATE        =       app
TARGET          =       client
QT              +=      core widgets gui network
CONFIG		+=	console

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui
RCC_DIR         =       build/rcc

QMAKE_CXXFLAGS	+=	-Wall

INCLUDEPATH     +=      .                                       		\
                        includes                                		\
			includes/Network					\
			includes/Audio						\
			includes/Mutex						\
			includes/GUI						\
			includes/ServerCommunication				\
			includes/Commands					\
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
			includes/Commands/ICommand.hpp				\
			includes/Commands/CommandAcceptAdd.hpp			\
			includes/Commands/CommandAcceptCall.hpp			\
			includes/Commands/CommandAdd.hpp			\
			includes/Commands/CommandCall.hpp			\
			includes/Commands/CommandCloseCall.hpp			\
			includes/Commands/CommandDel.hpp			\
			includes/Commands/CommandErr.hpp			\
			includes/Commands/CommandExit.hpp			\
			includes/Commands/CommandList.hpp			\
			includes/Commands/CommandLog.hpp			\
			includes/Commands/CommandReg.hpp			\
			includes/Commands/CommandSend.hpp			\
			includes/Commands/CommandShow.hpp			\
			includes/Commands/CommandUpdate.hpp			\
			includes/Commands/CommandException.hpp			\
			includes/GUI/BabelDialog.hpp				\
			includes/GUI/BabelFlyer.hpp				\
			includes/GUI/BabelIdentification.hpp			\
			includes/GUI/BabelContactWidget.hpp			\
			includes/GUI/BabelInscription.hpp			\
			includes/GUI/BabelSetting.hpp				\
			includes/GUI/BabelMain.hpp				\
			includes/GUI/BabelMainWindow.hpp			\
			includes/Contact.hpp					\
			includes/Babel.hpp					\
			includes/ErrorStatus.hpp

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
			sources/GUI/BabelDialog.cpp				\
			sources/GUI/BabelMainWindow.cpp				\
			sources/GUI/BabelContactWidget.cpp			\
			sources/GUI/BabelFlyer.cpp				\
			sources/GUI/BabelInscription.cpp			\
			sources/GUI/BabelSetting.cpp				\
			sources/GUI/BabelMain.cpp				\
			sources/GUI/BabelIdentification.cpp			\
			sources/ServerCommunication/ServerCommunication.cpp	\
			sources/ServerCommunication/CommandPacketBuilder.cpp	\
			sources/Commands/CommandAcceptAdd.cpp			\
			sources/Commands/CommandAcceptCall.cpp			\
			sources/Commands/CommandAdd.cpp				\
			sources/Commands/CommandCall.cpp			\
			sources/Commands/CommandCloseCall.cpp			\
			sources/Commands/CommandDel.cpp				\
			sources/Commands/CommandErr.cpp				\
			sources/Commands/CommandExit.cpp			\
			sources/Commands/CommandList.cpp			\
			sources/Commands/CommandLog.cpp				\
			sources/Commands/CommandReg.cpp				\
			sources/Commands/CommandSend.cpp			\
			sources/Commands/CommandShow.cpp			\
			sources/Commands/CommandUpdate.cpp			\
			sources/Commands/ICommand.cpp				\
			sources/Commands/CommandException.cpp			\
			sources/Babel.cpp					\
			sources/Contact.cpp					\
			sources/ErrorStatus.cpp

FORMS		+=	forms/BabelMainWindow.ui				\
			forms/BabelDialog.ui					\
			forms/BabelFlyer.ui					\
			forms/BabelIdentification.ui				\
			forms/BabelInscription.ui				\
			forms/BabelSetting.ui					\
			forms/BabelMain.ui					\
			forms/BabelContactWidget.ui

RESOURCES	+=	resources/BabelMainWindow.qrc

win32:LIBS      +=      -ldependencies/libs/portaudio_x86	\
			-ldependencies/libs/celt 		\
			-ldependencies/libs/opus 		\
			-ldependencies/libs/silk_common 	\
			-ldependencies/libs/silk_fixed		\
			-ldependencies/libs/silk_float

unix:LIBS       +=      -Ldependencies -lopus                   \
                        -Ldependencies -lportaudio
