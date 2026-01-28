#ifndef LUMEN_GL_LOGGER_H
#define LUMEN_GL_LOGGER_H

#include <string>
#include <string_view>
#include <format>

namespace lumen::gl {

    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    class Logger {
        public:
            template<typename... Args>
                static void Log(LogLevel level, std::string_view fmt, Args&&... args) {
                    if (static_cast<int>(level) < static_cast<int>(m_minLevel)) {
                        return;
                    }

                    LogImpl(
                            level,
                            std::vformat(fmt, std::make_format_args(args...))
                           );
                }

            static void SetLevel(LogLevel minLevel);
            static LogLevel GetLevel();

        private:
            static void LogImpl(LogLevel level, const std::string& msg);
            static LogLevel m_minLevel;
    };

};

#define LOG_TRACE(...)    ::lumen::gl::Logger::Log(::lumen::gl::LogLevel::TRACE,    __VA_ARGS__)
#define LOG_DEBUG(...)    ::lumen::gl::Logger::Log(::lumen::gl::LogLevel::DEBUG,    __VA_ARGS__)
#define LOG_INFO(...)     ::lumen::gl::Logger::Log(::lumen::gl::LogLevel::INFO,     __VA_ARGS__)
#define LOG_WARN(...)     ::lumen::gl::Logger::Log(::lumen::gl::LogLevel::WARNING,  __VA_ARGS__)
#define LOG_ERROR(...)    ::lumen::gl::Logger::Log(::lumen::gl::LogLevel::ERROR,    __VA_ARGS__)
#define LOG_CRITICAL(...) ::lumen::gl::Logger::Log(::lumen::gl::LogLevel::CRITICAL, __VA_ARGS__)

#endif
