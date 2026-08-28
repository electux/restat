#include "gtest/gtest.h"
#include "mocks/mocks.h"
#include "command/parser.h"

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_clear_input();
    }
};

TEST_F(ParserTest, WellFormedCommand) {
    mock_push_input("<rs#ch#1#on#end>");
    char buf[64];
    bool success = parser_get_command(buf, sizeof(buf));
    EXPECT_TRUE(success);
    EXPECT_STREQ(buf, "rs#ch#1#on#end");
}

TEST_F(ParserTest, IncompleteCommand) {
    mock_push_input("<rs#ch#1");
    char buf[64];
    bool success = parser_get_command(buf, sizeof(buf));
    EXPECT_FALSE(success);
}

TEST_F(ParserTest, IgnoresWhitespace) {
    mock_push_input("\r\n<rs#ch#2#off#end>\n");
    char buf[64];
    bool success = parser_get_command(buf, sizeof(buf));
    EXPECT_TRUE(success);
    EXPECT_STREQ(buf, "rs#ch#2#off#end");
}

TEST_F(ParserTest, BufferOverflowHandling) {
    mock_push_input("<12345678901234567890>");
    char buf[10];
    bool success = parser_get_command(buf, sizeof(buf));
    EXPECT_FALSE(success);
}
