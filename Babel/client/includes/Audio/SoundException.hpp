#pragma once

#include <stdexcept>

class SoundException : public std::runtime_error {

	// default ctor dtor
	public:
		SoundException(const std::string &error);
		~SoundException(void) throw() {}

	// private coplien form
	private:
		SoundException(const SoundException &) : std::runtime_error("") {}
		const SoundException &operator=(const SoundException &) { return *this; }

	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
