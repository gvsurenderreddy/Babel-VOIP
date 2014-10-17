#pragma once

#include "opus.h"
#include "Sound.hpp"

class EncodeManager {

	// ctor - dtor
	public:
		EncodeManager(void);
		~EncodeManager(void);

	// coplien form
	private:
		EncodeManager(const EncodeManager &) {}
		const EncodeManager &operator=(const EncodeManager &) { return *this; }

	// encode - decode
	public:
		Sound::Encoded	encode(const Sound::Decoded &sound);
		Sound::Decoded	decode(const Sound::Encoded &sound);

	// attributes
	private:
		OpusEncoder	*mEncoder;
		OpusDecoder	*mDecoder;

};
