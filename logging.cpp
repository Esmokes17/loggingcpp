#include "logging.h"

std::string Logging::stdOutputLog(Level level,
                std::string message,
                std::string date,
                std::string time,
                std::string file,
                std::string function,
                int line){
    
    std::string strLevel = "";
    switch (level){
    case Info:
        strLevel = "INFO";
        break;
    case Warnning:
        strLevel = "WARNNING";
        break;
    case Error:
        strLevel = "ERROR";
        break;
    case Critical:
        strLevel = "CRITICAL";
    default:
        break;
    }
    return date + ":" + time + " - " +
                    file + ":" + ":" + function + (std::to_string(line)) + " - " +
                    strLevel + " - " +
                    message;
}

void Logging::writeFile(Level level,
            std::string message,
            std::string date,
            std::string time,
            std::string file,
            std::string function,
            int line){
    
    std::ofstream out(LOG_FILE_NAME, std::ios::out | std::ios::app);
    out << stdOutputLog(level, message, date, time, file, function, line) << std::endl;
    out.close();
}

void Logging::writeConsole(Level level,
            std::string message,
            std::string date,
            std::string time,
            std::string file,
            std::string function,
            int line){

    std::cout << stdOutputLog(level, message, date, time, file, function, line) << std::endl;
}