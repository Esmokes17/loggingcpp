#include <sstream>
#include <fstream>

#include <gtest/gtest.h>

#include "../logging.h"

#pragma once

class FormatFixure : public ::testing::Test{
    protected:
        void SetUp(){ Logging::reset(); }
        // ~FormatFixure();
};

static std::stringstream buffer;
class OutputConsoleFixture : public ::testing::Test{
    protected:
        void SetUp(){
            Logging::reset();
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
