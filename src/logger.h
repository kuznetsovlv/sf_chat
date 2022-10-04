#pragma once
#include <exception>
#include <filesystem>
#include <fstream>
#include <shared_mutex>
#include <string>

class file_exception final: public std::exception
{
	private:
	const std::filesystem::path _path;

	public:
	explicit file_exception(const std::filesystem::path&) noexcept;

	virtual const char *what()const noexcept override final;
};

class Logger
{
	private:
	std::filesystem::path _path;
	std:: fstream _file;
	std::shared_mutex _mutex;
	void init();

	protected:
	void input(std::string&);
	void output(const std::string&);

	public:
	Logger(const std::filesystem::path&);
	Logger(Logger&) = delete;
	Logger(Logger&&) = delete;
	virtual ~Logger();

	void setPath(const std::filesystem::path&);

	Logger &operator=(Logger&) = delete;
	Logger &operator=(Logger&&) = delete;
};
