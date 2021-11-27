#include <memory>
#include <string>
#include "response.h"

template<class T>
Response<T>::Response(const bool success, const std::string message)noexcept:_success(success),_message(message)
{
}

template<class T>
Response<T>::Response(const bool success, const std::string message, const std::shared_ptr<T> data)noexcept:_success(success),_message(message),_data(data)
{
}

template<class T>
bool Response<T>::success()const noexcept
{
	return _success;
}

template<class T>
const std::string &Response<T>::message()const noexcept
{
	return _message;
}

template<class T>
std::shared_ptr<T> Response<T>::data()const noexcept
{
	return _data;
}
