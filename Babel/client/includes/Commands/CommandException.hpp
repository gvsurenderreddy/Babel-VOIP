#pragma once

#include <string>
#include <stdexcept>

class CommandException : public std::runtime_error {

	// default ctor dtor
	public:
		CommandException(const std::string &error);
		~CommandException(void) throw() {}

	// private coplien form
	private:
		CommandException(const CommandException &) : std::runtime_error("") {}
		const CommandException &operator=(const CommandException &) { return *this; }

	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
