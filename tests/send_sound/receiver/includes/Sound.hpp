#pragma once

#include "opus.h"

namespace Sound {

	const int	SAMPLE_RATE = 48000;
	const int	NB_CHANNELS = 2;
	const int	FRAMES_PER_BUFFER = 480;

	struct Encoded {
		unsigned char	*buffer;
		int				size;
	};

	struct Decoded {
		float	*buffer;
		int		size;
	};

};



/* avant l'envoi */
/*char *message = new char[size * sizeof(float)]
memcpy(message, buffer, size * sizeof(float));
*/
/* quand tu reçois */
/*float *buffer = new float[taille_message / sizeof(float)]
memcpy(buffer, message, taille_message / sizeof(float))...
*/