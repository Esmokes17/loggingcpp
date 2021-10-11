#include "fixture.hpp"

TEST_F(FormatFixure, configuration_defualt){
    LOG_CONF* tester = Logging::getConfig();
    ASSERT_EQ("{date} : {time} - {file}:<{func}>:{line} - {level} - {message}", tester->format);
    ASSERT_EQ("{month} {day} {year}", tester->dateFormat);
    ASSERT_EQ(Info, tester->level);
    ASSERT_EQ("logfile.log", tester->fileName);
}

TEST_F(FormatFixure, configuraton_format_default){
    ASSERT_EQ("{date} : {time} - {file}:<{func}>:{line} - {level} - {message}", Logging::getConfig()->format);
    std::string time = __TIME__;
    int line = __LINE__;
    std::string expect = Logging::formattingDate(__DATE__) +
                        " : " + time+
                        " - " + __FILE__ + ":<" + __func__ + ">:" + std::to_string(line)+
                        " - " + "ERROR"+
                        " - " + "testing";

    ASSERT_EQ(Logging::stdOutputLog(Error, "testing", __DATE__, __TIME__, __FILE__, __func__, line), expect);
}

TEST_F(FormatFixure, configuraton_format1){
    Logging::setFormat("{level} - {message}");
    ASSERT_EQ("{level} - {message}", Logging::getConfig()->format);
    ASSERT_EQ(Logging::stdOutputLog(Info, "testing", __DATE__, __TIME__, __FILE__, __func__, __LINE__),
        "INFO - testing");

    Logging::setFormat("{date} = {level} - {message}");
    ASSERT_EQ(Logging::stdOutputLog(Warning, "testing", __DATE__, __TIME__, __FILE__, __func__, __LINE__),
        (Logging::formattingDate(__DATE__) + " = WARNING - testing"));
}

TEST_F(FormatFixure, configuraton_dateFormat_default){
    Logging::setFormat("{date}");
    ASSERT_EQ(Logging::stdOutputLog(Info, "", __DATE__, __TIME__, __FILE__, __func__, __LINE__),
        Logging::formattingDate(__DATE__));
}

TEST_F(FormatFixure, configuraton_dateFormat1){
    Logging::setDateFormat("{year} {month} {day}");
    Logging::setFormat("{date}");
    ASSERT_EQ("{year} {month} {day}", Logging::getConfig()->dateFormat);
    ASSERT_EQ(Logging::stdOutputLog(Info, "testing", __DATE__, __TIME__, __FILE__, __func__, __LINE__),
        Logging::formattingDate(__DATE__));
}

TEST_F(FormatFixure, configuraton_dateFormat2){
    Logging::setDateFormat("{day} {month}n");
    Logging::setFormat("{date}");
    ASSERT_EQ(Logging::stdOutputLog(Info, "testing", __DATE__, __TIME__, __FILE__, __func__, __LINE__),
        Logging::formattingDate(__DATE__));
}
