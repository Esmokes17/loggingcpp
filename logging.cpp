#include "logging.h"

LOG_CONF* Logging::config = new LOG_CONF();
bool Logging::isCallBefore = false;

std::string Logging::lastOutput;
std::string Logging::buffer;

std::string Logging::erase_space(std::string str){
    std::string res = "";
    for(int i = 0 ; i < str.size() ; i++)
        if(str.at(i) != ' ')
            res += str.at(i);

    return res;
}

std::string Logging::formattingDate(std::string date){
    std::string newDate = "";
    for(int i = 0 ; i < config->dateFormat.length() ; i++){
        if(config->dateFormat[i] == '{'){
            i++;
            int begin = i;
            while(config->dateFormat[i] != '}')
                i++;

            std::string word_date = config->dateFormat.substr(begin, i-begin);
            if(word_date == "month"){
                std::string month = date.substr(0, 3);
                if(config->dateFormat.at(++i) == 'n'){
                    if(month == "Jan")          month = "1";
                    else if(month == "Feb")     month = "2";
                    else if(month == "Mar")     month = "3";
                    else if(month == "Apr")     month = "4";
                    else if(month == "May")     month = "5";
                    else if(month == "Jun")     month = "6";
                    else if(month == "Jul")     month = "7";
                    else if(month == "Aug")     month = "8";
                    else if(month == "Sep")     month = "9";
                    else if(month == "Oct")     month = "10";
                    else if(month == "Nov")     month = "11";
                    else if(month == "Dec")     month = "12";
                }
                newDate += month;
            }
            else if(word_date == "day"){
                newDate += erase_space(date.substr(4, 2));
            }
            else if(word_date == "year"){
                newDate += date.substr(7, 4);
            }
        }
        else{
            newDate += config->dateFormat.at(i);
        }
    }
    return newDate;
}

std::string Logging::stdOutputLog(Level level,
                std::string message,
                std::string date,
                std::string time,
                std::string file,
                std::string function,
                int line){

    // convert level to string
    std::string strLevel = "";
    switch (level){
    case Info:
        strLevel = "INFO";
        break;
    case Warning:
        strLevel = "WARNING";
        break;
    case Error:
        strLevel = "ERROR";
        break;
    case Critical:
        strLevel = "CRITICAL";
    default:
        break;
    }

    date = formattingDate(date);

    // formatting output
    std::string output = "";
    for(int i = 0 ; i < config->format.length() ; i++){
        if(config->format[i] == '{'){
            i++;
            int begin = i;
            while(config->format[i] != '}')
                i++;

            std::string word = config->format.substr(begin, i-begin);
            if(word == "date")          output += date;
            else if(word == "time")     output += time;
            else if(word == "file")     output += file;
            else if(word == "func")     output += function;
            else if(word == "line")     output += (std::to_string(line));
            else if(word == "level")    output += strLevel;
            else if(word == "message")  output += message;
        }
        else
            output += config->format[i];
    }
    return output;
}

void Logging::writeFile(Level level,
            std::string message,
            std::string date,
            std::string time,
            std::string file,
            std::string function,
            int line){

    // chaeck at least level for writing
    if(level < config->level)
        return;

    std::ofstream out;
    // chaeck if is first time call function remove data in the file
    if(!isCallBefore){
        isCallBefore = true;
        out.open(config->fileName, std::ios::out | std::ios::trunc);
    }
    else{
        out.open(config->fileName, std::ios::out | std::ios::app);
    }
    lastOutput = stdOutputLog(level, message, date, time, file, function, line);
    out << lastOutput << std::endl;
    out.flush();
    out.close();
}

void Logging::writeConsole(Level level,
            std::string message,
            std::string date,
            std::string time,
            std::string file,
            std::string function,
            int line){
    
    if(level < config->level)
        return;
    
    lastOutput = stdOutputLog(level, message, date, time, file, function, line);
    std::cout << lastOutput << std::endl;
}

void Logging::reset(){
    config = new LOG_CONF();
    buffer = "";
    lastOutput = "";
    isCallBefore = false;
};