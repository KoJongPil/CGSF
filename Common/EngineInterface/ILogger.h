#ifndef ILOGGER_H_
#define ILOGGER_H_

namespace cgsf
{
	enum class LOG_LEVEL : short
	{
		DEBUG	= 1,
		INFO	= 2,
		WARN	= 3,
		EERROR	= 4, // 구글 로그의 코드와 충돌 때문에 이름 조금 바꿈
		FATAL	= 5,
	};

	const int MAX_LOG_STRING_LENGTH = 256;

	class ILogger
	{
	public:
		ILogger(){}
		virtual ~ILogger() {};

		virtual bool Initialize(const char* pszLogFileName, const LOG_LEVEL UseLogLevel) = 0;
		virtual void Finally() = 0;

		virtual void Write(const LOG_LEVEL LogLevel, const char* pFormat, ...) = 0;
		virtual void Flush() = 0;

	protected:
		LOG_LEVEL m_UseLogLevel;
	};
}


#endif  // ILOGGER_H_