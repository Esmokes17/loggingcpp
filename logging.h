#ifndef CHAT_LOGGING_H
#define CHAT_LOGGING_H

#include <iostream>
#include <string>
#include <fstream>

#define logFile(message, level) Logging::writeFile(                                     \
                level, message, __DATE__, __TIME__, __FILE__, __func__, __LINE__        \
                )                                                                       \

#define logConsole(message, level) Logging::writeConsole(                               \
        level, message, __DATE__, __TIME__, __FILE__, __func__, __LINE__                \
        )                                                                               \

#define LOG_FILE_NAME "log.txt"

enum Level{
    Info,
    Warnning,
    Error,
    Critical    
};

class Logging{
    private:

    public:
        static std::string stdOutputLog(Level level,
                std::string message,
                std::string data,
                std::string time,
                std::string file,
                std::string function,
                int line);
        
        static void writeFile(Level level,
                std::string message,
                std::string data,
                std::string time,
                std::string file,
                std::string function,
                int line);
        
        static void writeConsole(Level level,
                std::string message,
                std::string data,
                std::string time,
                std::string file,
                std::string function,
                int line);
};

#endif