#pragma once

#include <QMetaType>
#include <vector>
#include "opus.h"

namespace Sound {

	const int	SAMPLE_RATE = 48000;
	const int	NB_CHANNELS = 2;
	const int	FRAMES_PER_BUFFER = 480;

	struct Encoded {
		std::vector<unsigned char> buffer;
		int	size;
	};

	struct Decoded {
		std::vector<float> buffer;
		int	size;
	};

};

Q_DECLARE_METATYPE(Sound::Encoded);