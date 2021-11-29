#include <string>
#include "dataResponse.h"

template<class T>
DataResponse<T>::DataResponse(const std::string &message)noexcept:Response(false, message)
{
}

template<class T>
DataResponse<T>::DataResponse(bool success, const std::string &message, const T &data)noexcept:Response(success, message),_data(data)
{
}

template<class T>
const T &DataResponse<T>::data()const noexcept
{
	return _data;
}
