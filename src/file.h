#pragma once
#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class file_exception final: public std::exception
{
	private:
	const std::filesystem::path _path;

	public:
	file_exception(const std::filesystem::path&) noexcept;

	virtual const char *what()const noexcept override final;

};

class File
{
	private:
	std::fstream _file;
	std::vector<std::fstream::pos_type> _line_positions;

	public:
	File(const std::filesystem::path&);
	File(const File&) = delete;
	File(const File&&) = delete;
	~File();

	std::string getLine(size_t)const;
	void output(const std::string&);
	size_t lines()const noexcept;
	size_t bites()const;


	File &operator=(File&) = delete;
	File &operator=(File&&) = delete;
};