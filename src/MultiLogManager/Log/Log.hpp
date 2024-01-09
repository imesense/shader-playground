#pragma once

namespace ShaderPlayground
{
	class LOG_API CLog
	{
	public: 
		CLog();
		virtual ~CLog();

		char logFileName[256]{};

		unsigned CreateLog();

		void CreateFileSettings();
		void Write(const char* level, const char* format, ...);
		void Close();

	protected:
		class Impl;

		Impl* pImpl;
	};

	extern LOG_API CLog* pLog;
}
