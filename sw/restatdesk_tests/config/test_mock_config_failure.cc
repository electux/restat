////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_mock_config_failure.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// restatdesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// restatdesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "mock_config.h"
#include <model/model.h>
#include <gtest/gtest.h>

using namespace Electux::App::Config;
using namespace Electux::App::Model;

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief A hypothetical component that relies on IConfig.
///
/// This class demonstrates how to test interaction with the Config interface
/// using a mock object, specifically for error handling scenarios.
////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConfigConsumer
{
public:
    explicit ConfigConsumer(IConfig& config) : m_config(config) {}

    bool initializeApp(const std::string& configPath)
    {
        // Attempt to load configuration
        if (!m_config.load())
        {
            // Unhappy flow: Configuration failed to load
            return false;
        }

        // Attempt to retrieve a critical setting
        auto &model = m_config.getConfig();

        if (model.getAllEntries().empty())
        {
            // Unhappy flow: Critical setting missing
            return false;
        }

        return true;
    }

private:
    IConfig& m_config;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the unhappy flow where configuration loading fails.
///
/// Verifies that the consumer handles the load failure gracefully.
///
/// @param MockConfigTest The test fixture.
/// @param LoadFailureHandlingTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockConfigTest, LoadFailureHandlingTest)
{
    MockConfig mockConfig;
    ConfigConsumer consumer(mockConfig);

    // Expectation: load() is called and returns false
    EXPECT_CALL(mockConfig, load()).WillOnce(Return(false));

    // Expectation: getString() should NOT be called if load fails
    EXPECT_CALL(mockConfig, getConfig()).Times(0);

    // Verify the result
    EXPECT_FALSE(consumer.initializeApp("/path/to/config.json"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the unhappy flow where a critical configuration key is missing.
///
/// Verifies that the consumer handles missing keys gracefully after a successful load.
///
/// @param MockConfigTest The test fixture.
/// @param MissingKeyHandlingTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockConfigTest, MissingKeyHandlingTest)
{
    MockConfig mockConfig;
    ConfigConsumer consumer(mockConfig);

    EXPECT_CALL(mockConfig, load()).WillOnce(Return(true));

    Model emptyModel;
    EXPECT_CALL(mockConfig, getConfig()).WillOnce(ReturnRef(emptyModel));

    // Verify the result
    EXPECT_FALSE(consumer.initializeApp("/path/to/config.json"));
}
