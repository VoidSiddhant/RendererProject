#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <fstream>
#include <assert.h>
#include <stdarg.h>

namespace EngineSpace
{
	
	Logger::Logger(const char* filename)
	{
		//assert(strlen(filename) <= 256);
		if (m_filename == filename)
			return;

		if (strlen(filename) > 4 && filename[strlen(filename) - 4] == '.')
		{
			sprintf(m_filename,"%s",filename);
		}
		else
			sprintf(m_filename,"%s.txt" ,filename);
		FILE* file;
		file = fopen(m_filename, "a+");
		//TODO:: ...............................????????????????????????????????????????
		wchar_t tmpBuf[256];
		_wstrdate(tmpBuf);
		fwprintf(file, L"%s M/D/Y\t", tmpBuf);
		//delete tmpBuf;
		_wstrtime(tmpBuf);
		fwprintf(file, L"%s\n\n", tmpBuf);
		//delete tmpBuf;
		fclose(file);
	}
	void Logger::SetLog(const char* log_string, ...)
	{
		if (!m_filename)
			return;

		//open file
		FILE* file;
		file = fopen(m_filename, "a+");
		va_list va_log_args;
		va_start(va_log_args, log_string);
		wchar_t tmpBuf[256];
		_wstrtime(tmpBuf);
		fwprintf(file, L"\n%s\t", tmpBuf);
		vfprintf(file,log_string, va_log_args);
		va_end(va_log_args);
		//delete tmpBuf;

		fclose(file);
	}

	void Logger::SetLog(const wchar_t* log_string_format, ...)
	{
		if (!m_filename)
			return;

		//open file
		FILE* file;
		file = fopen(m_filename, "a+");
		va_list va_log_args;
		va_start(va_log_args, log_string_format);
		wchar_t tmpBuf[256];
		_wstrtime(tmpBuf);
		fwprintf(file, L"\n%S\t", tmpBuf);
		vfwprintf(file, log_string_format, va_log_args);
		va_end(va_log_args);
		//delete tmpBuf;
		fclose(file);
	}

	void Logger::ClearLog()
	{
		FILE* file;
		file = fopen(m_filename, "w+");
		fclose(file);
	}


	Logger::~Logger()
	{

	}

}
