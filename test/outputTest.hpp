#include "fixture.hpp"

#define consoleOut_written ASSERT_NE(buffer.str().length(), 0)
#define fileOut_written ASSERT_NE(data.length(), 0)

#define consoleOut_asert ASSERT_EQ(buffer.str(), Logging::getLastOutput()+(char)(0x0A));
#define fileOut_assert ASSERT_EQ(data, Logging::getLastOutput());
#define clean(fileName) std::remove(fileName);

TEST_F(OutputConsoleFixture, console_output_default){
    logConsole("console_output_default", Info);
    consoleOut_written;
    consoleOut_asert;
}

TEST_F(OutputConsoleFixture, console_output_anotherFormat){
    Logging::setFormat("{level} - {message}");
    logConsole("console_output_anotherFormar", Error);
    consoleOut_written;
    consoleOut_asert;
}

TEST_F(OutputConsoleFixture, console_output_levelStat1){
    Logging::setLevel(Error);
    logConsole("console_output_levelStat1", Info);
    ASSERT_EQ(buffer.str().length(), 0);
}

TEST_F(OutputConsoleFixture, console_output_levelStat2){
    Logging::setLevel(Error);
    logConsole("console_output_levelStat2", Error);
    consoleOut_written;
    consoleOut_asert;
}

TEST_F(OutputConsoleFixture, console_output_levelStat3){
    Logging::setLevel(Error);
    logConsole("console_output_levelStat3", Critical);
    consoleOut_written;
    consoleOut_asert;
}

TEST_F(OutputFileFixture, clean_file_output){
    std::fstream file("logfile.log", std::ios::out | std::ios::trunc);
    file.write("somthings", 10);
    file.close();
    file.open("logfile.log", std::ios::in);
    logFile("file_output_default", Info);
    std::string data;
    std::getline(file, data) ;
    file.close();
    clean("logfile.log");
    fileOut_assert;
}

TEST_F(OutputFileFixture, file_output_default){
    logFile("file_output_default", Info);
    std::ifstream file("logfile.log", std::ios::in);
    std::string data;
    std::getline(file, data) ;
    file.close();
    clean("logfile.log");
    fileOut_assert;
}


TEST_F(OutputFileFixture, file_output_anotherFormat){
    const char * fileName = "test.log";
    Logging::setFileName(fileName);
    logFile("file_output_anotherFormat", Info);
    std::ifstream file(fileName, std::ios::in);
    std::string data;
    std::getline(file, data) ;
    file.close();
    clean(fileName);
    fileOut_assert;
}

TEST_F(OutputFileFixture, file_output_multiplyLine_countLine){
    logFile("file_output_multiplyLine_countLine1", Info);
    std::ifstream file("logfile.log", std::ios::in);
    std::string data;
    std::getline(file, data) ;
    logFile("file_output_multiplyLine_countLine2", Warning);
    std::getline(file, data);
    ASSERT_EQ(file.get(), (char)(-1));
    ASSERT_TRUE(file.eof());
    file.close();
    clean("logfile.log");
}

TEST_F(OutputFileFixture, file_output_multiplyLine_out){
    logFile("file_output_multiplyLine1", Info);
    std::ifstream file("logfile.log", std::ios::in);
    std::string data;
    std::getline(file, data) ;
    fileOut_assert;
    logFile("file_output_multiplyLine2", Warning);
    std::getline(file, data) ;
    fileOut_assert;
    file.close();
    clean("logfile.log");
}

TEST_F(OutputConsoleFixture, file_output_levelStat1){
    Logging::setLevel(Error);
    const char * fileName = "test.log";
    Logging::setFileName(fileName);
    logFile("file_output_levelStat1", Info);
    std::ifstream file(fileName, std::ios::in);
    std::string data;
    std::getline(file, data) ;
    file.close();
    clean(fileName);
    fileOut_assert;
    ASSERT_EQ(data.length(), 0);
}

TEST_F(OutputConsoleFixture, file_output_levelStat2){
    Logging::setLevel(Error);
    const char * fileName = "test.log";
    Logging::setFileName(fileName);
    logFile("file_output_levelStat2", Error);
    std::ifstream file(fileName, std::ios::in);
    std::string data;
    std::getline(file, data) ;
    file.close();
    clean(fileName);
    fileOut_assert;
    fileOut_written;
}

TEST_F(OutputConsoleFixture, file_output_levelStat3){
    Logging::setLevel(Error);
    const char * fileName = "test.log";
    Logging::setFileName(fileName);
    logFile("file_output_levelStat2", Critical);
    std::ifstream file(fileName, std::ios::in);
    std::string data;
    std::getline(file, data) ;
    file.close();
    clean(fileName);
    fileOut_assert;
    fileOut_written;
}