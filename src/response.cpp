#include <string>
#include "response.h"

template<class T>
Response<T>::Response(bool success, std::string message)noexcept:Response(success, message, nullptr)
{
}

template<class T>
Response<T>::Response(bool success, std::string message, T *data)noexcept:_success(success),_message(message),_data(data)
{
}

template<class T>
Response<T>::Response(Response<T> &that)noexcept:_success(that._success),_message(that._message),_data(that._data)
{
}

template<class T>
Response<T>::Response(Response<T> &&that)noexcept:_success(that._success),_message(that._message),_data(that._data)
{
	that._data = nullptr;
}

template<class T>
bool Response<T>::success()const noexcept
{
	return _success;
}

template<class T>
std::string Response<T>::message()const noexcept
{
	return _message;
}

template<class T>
T *Response<T>::data()const noexcept
{
	return _data;
}

template<class T>
Response<T> &Response<T>::operator=(Response<T> &that)noexcept
{
	_success = that._succese;
	_message = that._message;
	_data = that._data;

	return *this;
}

template<class T>
Response<T> &&Response<T>::operator=(Response<T> &&that)noexcept
{
	_success = that._succese;
	_message = that._message;
	_data = that._data;

	that._data = nullptr;

	return *this;
}
