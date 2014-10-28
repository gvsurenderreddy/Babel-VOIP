#pragma once

#include <stdexcept>

class SoundException : public std::runtime_error {

	// default ctor dtor
	public:
		SoundException(const std::string &error);
		~SoundException(void) throw() {}

	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
