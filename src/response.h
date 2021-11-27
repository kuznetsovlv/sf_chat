#pragma once
#include <memory>
#include <string>

template <class T>
class Response final
{
	private:
	const bool _success;
	const std::string _message;
	const std::shared_ptr<T> _data;

	public:
	Response(const bool,const std::string)noexcept;
	Response(const bool,const std::string,const std::shared_ptr<T>)noexcept;

	bool success()const noexcept;
	const std::string &message()const noexcept;
	std::shared_ptr<T> data()const noexcept;
};

#include "response.cpp"
