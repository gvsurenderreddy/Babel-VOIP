#pragma once

#include "ISoundDevice.hpp"
#include "EncodeManager.hpp"
#include <qobject.h>

class AudioManager : public QObject, public ISoundDevice::OnSoundDeviceEvent {

	Q_OBJECT

	// ctor - dtor
	public:
		AudioManager(void);
		~AudioManager(void);

	// coplien form
	private:
		AudioManager(const AudioManager &) : QObject() {}
		const AudioManager &operator=(const AudioManager &) { return *this; }

	// play sound
	public slots:
		void	playSound(const Sound::Encoded &sound);
		void	onSoundAvailable(ISoundDevice *soundDevice);

	// sound available
	signals:
		void	soundAvailable(const Sound::Encoded &sound);

	// handle streams
	public:
		void	startRecording(void);
		void	stopRecording(void);
		void	startPlaying(void);
		void	stopPlaying(void);

	// attributes
	private:
		ISoundDevice	*mInputDevice;
		ISoundDevice	*mOutputDevice;
		EncodeManager	mEncodeManager;
		bool			mRecordEnable;
		bool			mPlayEnable;
};
