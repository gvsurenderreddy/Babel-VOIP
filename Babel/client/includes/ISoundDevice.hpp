#pragma once

class ISoundDevice {

	// SoundBuffer
	public:
		struct SoundBuffer {
			float	*sound;
			int		nbFrames;
			int		currentFrame;

			~SoundBuffer(void) {
				if (sound)
					delete sound;
			}
		};

	// virtual destructor
	public:
		virtual ~ISoundDevice(void) {}

	// virtual methods
	public:
		virtual void	startStream(void) = 0;
		virtual void	stopStream(void) = 0;

		virtual ISoundDevice	&operator<<(SoundBuffer *soundBuffer) = 0;
		virtual ISoundDevice	&operator>>(SoundBuffer *&soundBuffer) = 0;

};
