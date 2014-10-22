#pragma once

#include "ISoundDevice.hpp"
#include "EncodeManager.hpp"
#include <qobject.h>
#include <QThread>

class AudioManager : public QThread {

	Q_OBJECT

	// ctor - dtor
	public:
		AudioManager(void);
		~AudioManager(void);

	// coplien form
	private:
		AudioManager(const AudioManager &) {}
		const AudioManager &operator=(const AudioManager &) { return *this; }

	// play sound
	public slots:
		void	playSound(const Sound::Encoded &sound);
		void	run();

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
