#pragma once
#include <string>
#include "response.h"

template<class T>
class DataResponse final: public Response
{
	private:
	const T _data;

	public:
	explicit DataResponse(const std::string&)noexcept;
	DataResponse(bool,const std::string&,const T&)noexcept;

	const T &data()const noexcept;
};

#include "dataResponse.cpp"
