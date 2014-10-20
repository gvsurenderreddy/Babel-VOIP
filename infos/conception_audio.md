## Conception Audio

La conception audio n'est pas encore terminée: elle ne contient pas encore l'encodage/décodage.


### ISoundDevice

Interface principale, héritée par SoundInputDevice et SoundOutputDevice

```cpp
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
```

* La struct ISoundDevice::SoundBuffer permettra de stocker les infos concernant une frame de son.
* La structure devrait évoluer lorsque l'encodage/décodage sera géré.
* startStream et stopStream permettront respectivement de démarrer et de close un stream d'input (micro) ou d'output (enceintes).
* les opérateurs >> et << sont overloadés et serviront respectivement à ajouter un packet à la liste de buffer ou à en récupérer un (cf SoundInputDevice et SoundOutputDevice)


### SoundInputDevice

Hérite de ISoundDevice et gère le micro

```cpp
class SoundInputDevice : public ISoundDevice {

	// ctor - dtor
	public:
		SoundInputDevice(void);
		~SoundInputDevice(void);

	// private coplien form
	private:
		SoundInputDevice(const SoundInputDevice &) {}
		const SoundInputDevice &operator=(const SoundInputDevice &) { return *this; }

	// init
	private:
		void	initInputDevice(void);

	// handle sound
	public:
		void	startStream(void);
		void	stopStream(void);

		ISoundDevice	&operator<<(SoundBuffer *soundBuffer);
		ISoundDevice	&operator>>(SoundBuffer *&soundBuffer);
		static int		callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	// attributes
	private:
		std::list<ISoundDevice::SoundBuffer *> mBuffers;
		PaStreamParameters	mInputParameters;
		PaStream *mStream;

		static const int	SAMPLE_RATE;
		static const int	NB_CHANNELS;
		static const int	FRAMES_PER_BUFFER;

};

```

On peut voir ici la list de ISoundDevice::SoundBuffer*.

* L'opérateur >> ajoute un élément dans la liste
* L'opérateur << en depop un et le retourne

Concrètement, startStream lance le stream de manière indéfinie. Cela va créer des packets régulièrements qui seront ajoutés à la liste.


### SoundOutputDevice

```cpp
class SoundOutputDevice : public ISoundDevice {

	// ctor - dtor
	public:
		SoundOutputDevice(void);
		~SoundOutputDevice(void);

	// private coplien form
	private:
		SoundOutputDevice(const SoundOutputDevice &) {}
		const SoundOutputDevice &operator=(const SoundOutputDevice &) { return *this; }

	// init
	private:
		void	initOutputDevice(void);

	// handle sound
	public:
		void	startStream(void);
		void	stopStream(void);

		ISoundDevice	&operator<<(SoundBuffer *soundBuffer);
		ISoundDevice	&operator>>(SoundBuffer *&soundBuffer);
		static int		callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	// attributes
	private:
		std::list<ISoundDevice::SoundBuffer *> mBuffers;
		PaStreamParameters	mOutputParameters;
		PaStream *mStream;

		static const int	SAMPLE_RATE;
		static const int	NB_CHANNELS;
		static const int	FRAMES_PER_BUFFER;

};
```

Presque similaire à SoundInputDevice.

Ici, startStream lance un stream de manière infinie. Lors du callback, on va regarder s'il y a qqc dans la liste de buffers.

Si oui, on le balance dans l'enceinte, si non, on wait le prochain callback.


### Info Annexe

Vu comme ça, ça peut paraître simple. En réalité, c'est bcp plus complexe que ça.

La lib portaudio est très relou à installer et encore plus à prendre en main et à comprendre.

Je vous conseille d'aller voir le code d'exemple que j'ai poster sur github (allez-y à tête reposée). Et encore, le code a été super simplifié par rapport à ce qu'on avait au début.

#### Commentaire d'alain qui suce des ours
