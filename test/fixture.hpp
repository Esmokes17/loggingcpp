#include <sstream>
#include <fstream>

#include <gtest/gtest.h>

#include "../logging.h"

#pragma once

class FormatFixure : public ::testing::Test{
    protected:
        void SetUp(){ Logging::reset(); }
};

class OutputConsoleFixture : public ::testing::Test{
    protected:
        std::stringstream buffer;
        void SetUp(){
            Logging::reset();
            buffer.str("");
            sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());
        }
        void TearDown(){ std::cout.rdbuf(sbuf); }
        std::streambuf *sbuf;
};

class OutputFileFixture : public ::testing::Test{
    protected:
        void SetUp(){
            Logging::reset();
        }
};
