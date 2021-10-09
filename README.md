# loggingCPP

this is a logging header in c/c++

# usage

&NewLine;

## log in console 
for logging in to the console you can write like this:

    #include "logging"

    int main(int argc, char * argv[]){
        logConsole("testing", Info);
        return 0;
    }

above code write a message in console like this:

    Oct 9 2021 : 00:28:32 - .\main.cpp:<main>:6 - INFO - testing

## log in file
for logging in to the file you can write like console mode.

    #include "logging.h"

    int main(int argc, char * argv[]){
        logFile("testing", Info);
        return 0;
    }

and output is like console mode.

## config
you can change the configuration and format of logging in some way. options that you can change:

- filename
- format of writing
- format of date
- minimum level for logging

&NewLine;
#### directly
you should declare a variable from LOG_CONF

    LOG_CONF config

then you can change every option that you want to change.
for example:

    #include "logging.h"

    int main(int argc, char * argv[]){
        LOG_CONF config;
        config.format("{level} - {message}");
        logConsole("testing LOG_CONF", Info);
        return 0;
    }

#### no directly
you can call the function to change every option
for example:

    #include "logging.h"

    int main(int argc, char * argv[]){
        config.setFileName("test.log");
        logFile("testing filename", Info);
        return 0;
    }

#### format type
if you want to change the format of writing, you should make a string and for every element like level, message, ... write in {} then in writing logging they will be replaced. elements that you can use:
- level
- date
- time
- file
- func (function)
- line
- message

#### format date type
if you want to change the date format you could make a string like above that "month", "year", "day", ... write in {}
just different in "month" you can add 'n' end of "{month}" for write-in number format and not in word format.

#### minimum level
the sort of level is :
- Info
- Warning
- Error
- Critical
for example, if you choose Warning, Info will not be written any.