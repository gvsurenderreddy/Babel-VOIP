#include "SoundInputDevice.hpp"
#include "SoundDeviceException.hpp"

const int SoundInputDevice::SAMPLE_RATE = 44100;
const int SoundInputDevice::NB_CHANNELS = 2;
const int SoundInputDevice::FRAMES_PER_BUFFER = 512;
const float SoundInputDevice::SAMPLE_SILENCE = 0.0f;

SoundInputDevice::SoundInputDevice(void) {
	if (Pa_Initialize() != paNoError)
		throw new SoundDeviceException("fail Pa_Initialize");

	initInputDevice();
}

SoundInputDevice::~SoundInputDevice(void) {
	Pa_Terminate();
}


void	SoundInputDevice::initInputDevice(void) {
	mInputParameters.device = Pa_GetDefaultInputDevice();
	if (mInputParameters.device == paNoDevice)
		throw new SoundDeviceException("fail Pa_GetDefaultInputDevice");

	mInputParameters.channelCount = SoundInputDevice::NB_CHANNELS;
	mInputParameters.sampleFormat = paFloat32;
	mInputParameters.suggestedLatency = Pa_GetDeviceInfo(mInputParameters.device)->defaultLowInputLatency;
	mInputParameters.hostApiSpecificStreamInfo = NULL;
}

float	*SoundInputDevice::recordSound(int seconds) {
	SoundInputDevice::InputData	data;

	data.frameIndex = 0;
	data.maxFrameIndex = seconds * SoundInputDevice::SAMPLE_RATE;

	int nbSamples = data.maxFrameIndex * SoundInputDevice::NB_CHANNELS;
	data.recordedSamples = new float[nbSamples];

	int nbBytes = nbSamples * sizeof(float);
	std::memset(data.recordedSamples, 0, nbBytes);

	PaStream *stream;
	if (Pa_OpenStream(&stream, &mInputParameters, NULL, SoundInputDevice::SAMPLE_RATE, SoundInputDevice::FRAMES_PER_BUFFER, paClipOff, SoundInputDevice::recordCallback, &data) != paNoError)
		throw new SoundDeviceException("fail Pa_OpenStream");

	if (Pa_StartStream(stream) != paNoError)
		throw new SoundDeviceException("fail Pa_StartStream");

	while (Pa_IsStreamActive(stream) == 1)
		Pa_Sleep(1000);

	if (Pa_CloseStream(stream) != paNoError)
		throw new SoundDeviceException("fail Pa_StopStream");

	return data.recordedSamples;
}

int	SoundInputDevice::recordCallback(const void *inputBuffer, void */*outputBuffer*/, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo */*timeInfo*/, PaStreamCallbackFlags /*statusFlags*/, void *userData) {
	SoundInputDevice::InputData *data = (SoundInputDevice::InputData *)userData;
	float *readBuffer = (float*)inputBuffer;
	float *writeBuffer = &data->recordedSamples[data->frameIndex * SoundInputDevice::NB_CHANNELS];
	long framesToCalc;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

	if (framesLeft < framesPerBuffer) {
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else {
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}

	for (long i = 0; i < framesToCalc; i++) {
		*writeBuffer++ = (readBuffer ? *readBuffer++ : SoundInputDevice::SAMPLE_SILENCE);
		if (SoundInputDevice::NB_CHANNELS == 2)
			*writeBuffer++ = (readBuffer ? *readBuffer++ : SoundInputDevice::SAMPLE_SILENCE);
	}

	data->frameIndex += framesToCalc;
	
	return finished;
}
