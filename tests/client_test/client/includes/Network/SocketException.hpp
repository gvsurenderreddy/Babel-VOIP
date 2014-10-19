#pragma once

#include <string>
#include <stdexcept>

class SocketException : public std::runtime_error {

	// default ctor dtor
	public:
		SocketException(const std::string &error);
		~SocketException(void) throw() {}
	
	// private coplien form
	private:
		SocketException(const SocketException &) : std::runtime_error("") {}
		const SocketException &operator=(const SocketException &) {	return *this; }

	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
