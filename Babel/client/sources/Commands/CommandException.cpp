#include "CommandException.hpp"

CommandException::CommandException(const std::string &error)
: std::runtime_error(error), mWhat(error) {}

const char	*CommandException::what(void) const throw() {
	return mWhat.c_str();
}
