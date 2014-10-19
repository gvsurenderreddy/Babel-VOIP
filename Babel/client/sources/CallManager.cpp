#include "CallManager.hpp"

CallManager::CallManager(void)
	: mInCommunication(false) {}

CallManager::~CallManager(void) {
}

void	CallManager::startCall(const Contact &contact) {
}

void	CallManager::stopCall(void) {
}

bool	CallManager::isInCommunication(void) const {
	return mInCommunication;
}

const Contact	&CallManager::getCurrentCalledContact(void) const {
	return mCurrentCalledContact;
}
