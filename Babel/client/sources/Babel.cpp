#include <QMetaType>
#include "Sound.hpp"
#include "Babel.hpp"

Babel::Babel(void) : mState(Babel::NOT_CONNECTED) {
	qRegisterMetaType<Sound::Encoded>();
}

Babel::~Babel(void) {
}

void	Babel::run(void) {
	Contact simon;

	simon.setHost("127.0.0.1");
	simon.setPort(4242);
	mCallManager.startCall(simon);
	mMainWindow.show();
}
