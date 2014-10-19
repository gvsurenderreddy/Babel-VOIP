#include "Babel.hpp"

Babel::Babel(void)
	: mState(Babel::NOT_CONNECTED) {}

Babel::~Babel(void) {
}

void	Babel::run(void) {
	mMainWindow.show();
}
