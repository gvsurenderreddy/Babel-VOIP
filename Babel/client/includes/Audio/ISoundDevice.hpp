#pragma once

#include "Sound.hpp"

class ISoundDevice {

	// listeners
	public:
		class OnSoundDeviceEvent {
			public:
				virtual void	onSoundAvailable(ISoundDevice *soundDevice) = 0;
		};

	// virtual destructor
	public:
		virtual ~ISoundDevice(void) {}

	// virtual methods
	public:
		virtual void	startStream(void) = 0;
		virtual void	stopStream(void) = 0;

		virtual ISoundDevice	&operator<<(const Sound::Decoded &soundBuffer) = 0;
		virtual ISoundDevice	&operator>>(Sound::Decoded &soundBuffer) = 0;

		virtual void	setOnSoundDeviceEventListener(ISoundDevice::OnSoundDeviceEvent *listener) = 0;

};
