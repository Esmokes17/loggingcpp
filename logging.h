#ifndef CHAT_LOGGING_H
#define CHAT_LOGGING_H

#include <iostream>
#include <string>
#include <fstream>

/** write message in format in file */
#define logFile(message, level) Logging::writeFile(                                     \
                level, message, __DATE__, __TIME__, __FILE__, __func__, __LINE__        \
                )                                                                       \

/** write message in format in console */
#define logConsole(message, level) Logging::writeConsole(                               \
        level, message, __DATE__, __TIME__, __FILE__, __func__, __LINE__                \
        )                                                                               \


enum Level{
    Info,
    Warning,
    Error,
    Critical    
};

typedef struct LogConfing{
        std::string format = "{date} : {time} - {file}:<{func}>:{line} - {level} - {message}";
        std::string dateFormat = "{month}w {day} {year}";
        Level level = Info;
        std::string fileName = "logfile.log";
} LOG_CONF;

class Logging{
    private:
        static LOG_CONF config;
        static bool isFirstTime;
        static std::string erase_space(std::string);
        static std::string stdOutputLog(Level level,
                std::string message,
                std::string data,
                std::string time,
                std::string file,
                std::string function,
                int line);
    public:
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

        static void setConfig(LOG_CONF conf){ config = conf; }
        static void setFormat(std::string format){ config.format = format; }
        static void setDateFormat(std::string format){ config.dateFormat = format; }
        static void setLevel(Level level){ config.level = level; }
        static void setFileName( std::string name){ config.fileName = name; }
};

#endif