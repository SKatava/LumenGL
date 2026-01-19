#include <LumenGL/Logger.h>

static std::vector<std::string> messages;

//Push a message to the log
void Logger::Log(const std::string& msg) {
    messages.push_back(msg);
}

//Get vector of messages in log
const std::vector<std::string>& Logger::Get_messages() {
    return messages;
}

