#include "EncodeManager.hpp"
#include "SoundException.hpp"

EncodeManager::EncodeManager(void) {
	int error;

	mEncoder = opus_encoder_create(Sound::SAMPLE_RATE, Sound::NB_CHANNELS, OPUS_APPLICATION_VOIP, &error);
	if (error != OPUS_OK)
		throw SoundException("fail opus_encoder_create");

	mDecoder = opus_decoder_create(Sound::SAMPLE_RATE, Sound::NB_CHANNELS, &error);
	if (error != OPUS_OK)
		throw SoundException("fail opus_decoder_create");
}

EncodeManager::~EncodeManager(void) {
	if (mEncoder)
		opus_encoder_destroy(mEncoder);

	if (mDecoder)
		opus_decoder_destroy(mDecoder);
}

Sound::Encoded	EncodeManager::encode(const Sound::Decoded &sound) {
	Sound::Encoded encoded;

	encoded.buffer.resize(sound.size);
	encoded.size = opus_encode_float(mEncoder, sound.buffer.data(), Sound::FRAMES_PER_BUFFER, encoded.buffer.data(), sound.size);

	if (encoded.size < 0)
		throw SoundException("fail opus_encode_float");

	return encoded;
}

Sound::Decoded	EncodeManager::decode(const Sound::Encoded &sound) {
	Sound::Decoded decoded;

	decoded.buffer.resize(Sound::FRAMES_PER_BUFFER * Sound::NB_CHANNELS);
	decoded.size = opus_decode_float(mDecoder, sound.buffer.data(), sound.size, decoded.buffer.data(), Sound::FRAMES_PER_BUFFER, 0) * Sound::NB_CHANNELS;

	if (decoded.size < 0)
		throw SoundException("fail opus_decode_float");

	return decoded;
}
