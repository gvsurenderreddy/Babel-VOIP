#include "SoundDeviceException.hpp"

SoundDeviceException::SoundDeviceException(const std::string &error)
: std::runtime_error(error), mWhat(error) {}

const char	*SoundDeviceException::what(void) const throw() {
	return mWhat.c_str();
}
