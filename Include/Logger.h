#ifndef _LOGGER_H
#define _LOGGER_H

namespace EngineSpace
{
	class Logger
	{
	public:
		Logger(const char* filename);
		void SetLog(const char* log_string_format, ...);
		void SetLog(const wchar_t* log_string_format,...);
		void ClearLog();
		~Logger();

	private:
		char m_filename[256];
	};
}

#endif // !_LOGGER_H

