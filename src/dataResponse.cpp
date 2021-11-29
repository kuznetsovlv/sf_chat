#include <string>
#include "dataResponse.h"

template<class T>
DataResponse<T>::DataResponse(bool success, std::string message, T data)noexcept:Response(success, message),_data(data)
{
}

template<class T>
const T &DataResponse<T>::data()const noexcept
{
	return _data;
}
