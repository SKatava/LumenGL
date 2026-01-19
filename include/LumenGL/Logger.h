#ifndef LOGGER_CLASS_H
#define LOGGER_CLASS_H

#include <string>
#include <vector>

class Logger {
    public:
        static void Log(const std::string& msg);
        static const std::vector<std::string>& Get_messages();
        Logger() = delete;
};

#endif
