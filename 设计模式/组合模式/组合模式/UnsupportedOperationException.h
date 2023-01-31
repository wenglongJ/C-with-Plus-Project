#pragma once
/*UnsupportedOperationException.h*/
#include <exception>
#include <string>
class UnsupportedOperationException : public std::exception
{
private:
	std::string message;
public:
	UnsupportedOperationException() : std::exception() {}

	UnsupportedOperationException(const std::string _message) :
		std::exception(_message.c_str()), message(_message) {}

	~UnsupportedOperationException() {}

	std::string getMessage() const
	{
		return message;
	}
};