#pragma once

#include <string>
#include <stdexcept>

class CommandException : public std::runtime_error {

	// default ctor dtor
	public:
		CommandException(const std::string &error);
		~CommandException(void) throw() {}

	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
