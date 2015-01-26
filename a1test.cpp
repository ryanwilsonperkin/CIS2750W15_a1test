#include "gtest/gtest.h"
#include "ParameterManager.h"

namespace {
class ParameterManagerTest : public ::testing::Test {
protected:
        ParameterManagerTest() {}
        virtual ~ParameterManagerTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
};
TEST_F(ParameterManagerTest, Create) {
        ParameterManager pm;
}
}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
