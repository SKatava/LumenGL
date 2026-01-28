#include <LumenGL/Logger.h>

#include <iostream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace lumen::gl {

LogLevel Logger::m_minLevel = LogLevel::TRACE;

namespace {

const char* levelToString(LogLevel lvl) {
    switch (lvl) {
        case LogLevel::TRACE:    return "TRACE";
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO ";
        case LogLevel::WARNING:  return "WARN ";
        case LogLevel::ERROR:    return "ERROR";
        case LogLevel::CRITICAL: return "CRIT ";
        default:                 return "?????";
    }
}

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.'
        << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

} 

void Logger::SetLevel(LogLevel minLevel) {
    m_minLevel = minLevel;
}

LogLevel Logger::GetLevel() {
    return m_minLevel;
}

void Logger::LogImpl(LogLevel level, const std::string& msg) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    std::cerr << getCurrentTime() << "  "
              << levelToString(level) << "  "
              << msg << '\n';
}

} 

