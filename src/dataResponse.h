#pragma once
#include <string>
#include "response.h"

template<class T>
class DataResponse final: public Response
{
	private:
	const T _data;

	public:
	DataResponse(std::string)noexcept;
	DataResponse(bool,std::string,T)noexcept;

	const T &data()const noexcept;
};

#include "dataResponse.cpp"
