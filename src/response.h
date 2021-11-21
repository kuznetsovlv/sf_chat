#pragma once
#include <string>

template <class T>
class Response final
{
	private:
	bool _success;
	std::string _message;
	T *_data;

	public:
	Response(bool,std::string, T*)noexcept;
	Response(Response<T>&);
	Response(Response<T>&&)noexcept;

	~Response()noexcept;

	bool success()const noexcept;
	std::string message()const noexcept;
	T *data()const noexcept;

	Response &operator=(Response<T>&);
	Response &&operator=(Response<T>&&);
};

#include "response.cpp"
