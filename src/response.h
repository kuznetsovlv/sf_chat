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
	Response(bool,std::string)noexcept;
	Response(bool,std::string, T*)noexcept;
	Response(Response<T>&)noexcept;
	Response(Response<T>&&)noexcept;

	~Response() = default; //Память *_data может быть нужна после уничтожения объекта, удаляться она должна в другом месте

	bool success()const noexcept;
	std::string message()const noexcept;
	T *data()const noexcept;

	Response<T> &operator=(Response<T>&)noexcept;
	Response<T> &&operator=(Response<T>&&)noexcept;
};

#include "response.cpp"
