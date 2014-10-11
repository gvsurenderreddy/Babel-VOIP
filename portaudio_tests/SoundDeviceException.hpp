#pragma once

#include <stdexcept>

class SoundDeviceException : public std::runtime_error {

	// default ctor dtor
	public:
		SoundDeviceException(const std::string &error);
		~SoundDeviceException(void) {}

	// private coplien form
	private:
		SoundDeviceException(const SoundDeviceException &) : std::runtime_error("") {}
		const SoundDeviceException &operator=(const SoundDeviceException &) { return *this; }

	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
