#include <iostream>
#include <fstream>

#include "gtest/gtest.h"
#include "ParameterManager.h"

#define TEST_FILENAME "TEMP"

namespace {
class ParameterManagerTest : public ::testing::Test {
protected:
        std::ofstream test_file;

        ParameterManagerTest() {}

        virtual ~ParameterManagerTest()
        {
                remove(TEST_FILENAME);
        }

        virtual void SetUp()
        {
                test_file.open(TEST_FILENAME);
        }

        virtual void TearDown()
        {
                test_file.close();
        }
};

TEST_F(ParameterManagerTest, Create)
{
        ParameterManager pm;
}

}  /* namespace */

int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
