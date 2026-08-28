////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_model.cc
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

#include <gtest/gtest.h>
#include <model/model_factory.h>

using namespace Electux::App::Model;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class ModelTest
/// @brief Fixture for testing the Model class.
////////////////////////////////////////////////////////////////////////////////////////////////////////
class ModelTest : public ::testing::Test
{
protected:
	std::unique_ptr<IModel> m_model;

	void SetUp() override
	{
		m_model = Electux::App::Model::createDefault();
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test basic key validation.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, ValidateKeyTest)
{
	// Valid control keys
	EXPECT_TRUE(m_model->validateKey("enable"));
	EXPECT_TRUE(m_model->validateKey("mode"));
	EXPECT_TRUE(m_model->validateKey("toggle"));
	EXPECT_TRUE(m_model->validateKey("timer"));
	EXPECT_TRUE(m_model->validateKey("timerEnable"));

	// Valid log keys
	EXPECT_TRUE(m_model->validateKey("log_level"));
	EXPECT_TRUE(m_model->validateKey("log_file_path"));

	// Valid serial keys
	EXPECT_TRUE(m_model->validateKey("device"));
	EXPECT_TRUE(m_model->validateKey("baud"));
	EXPECT_TRUE(m_model->validateKey("data"));
	EXPECT_TRUE(m_model->validateKey("parity"));
	EXPECT_TRUE(m_model->validateKey("stop"));
	EXPECT_TRUE(m_model->validateKey("flow"));

	// Invalid keys
	EXPECT_FALSE(m_model->validateKey("invalid_key"));
	EXPECT_FALSE(m_model->validateKey(""));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test adding and retrieving entities.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, AddAndGetEntityTest)
{
	// Empty model
	EXPECT_EQ(m_model->getEntity("device"), "");

	// Add unique key
	EXPECT_TRUE(m_model->add("device", "/dev/ttyUSB0"));
	EXPECT_EQ(m_model->getEntity("device"), "/dev/ttyUSB0");

	// Add duplicate key
	EXPECT_FALSE(m_model->add("device", "/dev/ttyUSB1"));
	EXPECT_EQ(m_model->getEntity("device"), "/dev/ttyUSB0");

	// Add another key
	EXPECT_TRUE(m_model->add("baud", "115200"));
	EXPECT_EQ(m_model->getEntity("baud"), "115200");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test updating entities.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, UpdateEntityTest)
{
	// Update non-existent key
	EXPECT_FALSE(m_model->update("device", "/dev/ttyUSB0"));

	// Add and then update key
	EXPECT_TRUE(m_model->add("device", "/dev/ttyUSB0"));
	EXPECT_TRUE(m_model->update("device", "/dev/ttyUSB1"));
	EXPECT_EQ(m_model->getEntity("device"), "/dev/ttyUSB1");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test clear functionality.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, ClearTest)
{
	EXPECT_TRUE(m_model->add("device", "/dev/ttyUSB0"));
	EXPECT_TRUE(m_model->add("baud", "115200"));
	EXPECT_EQ(m_model->get().size(), 2);

	m_model->clear();
	EXPECT_EQ(m_model->get().size(), 0);
	EXPECT_EQ(m_model->getEntity("device"), "");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test converting enum keys to strings.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, ToStringEnumTest)
{
	EXPECT_EQ(m_model->toString(ModelControlKey::Enable), "enable");
	EXPECT_EQ(m_model->toString(ModelLogKey::LogLevel), "log_level");
	EXPECT_EQ(m_model->toString(ModelSerialKey::Device), "device");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test getChannelState and setChannelState methods.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, ChannelStateTest)
{
	// Initialize entities with space-separated values for 8 channels
	m_model->add("enable", "false false false false false false false false");
	m_model->add("mode", "0 0 0 0 0 0 0 0");
	m_model->add("toggle", "false false false false false false false false");
	m_model->add("timer", "0 0 0 0 0 0 0 0");
	m_model->add("timerEnable", "false false false false false false false false");

	// Get initial channel state for channel 3
	ChannelState state = m_model->getChannelState(3);
	EXPECT_FALSE(state.enabled);
	EXPECT_EQ(state.mode, Channel::ChannelMode::Toggle);
	EXPECT_FALSE(state.toggle);
	EXPECT_EQ(state.timer, 0);
	EXPECT_FALSE(state.timerEnabled);

	// Modify and set channel state for channel 3
	state.enabled = true;
	state.mode = Channel::ChannelMode::Timer;
	state.toggle = true;
	state.timer = 100;
	state.timerEnabled = true;

	m_model->setChannelState(3, state);

	// Verify update
	ChannelState updatedState = m_model->getChannelState(3);
	EXPECT_TRUE(updatedState.enabled);
	EXPECT_EQ(updatedState.mode, Channel::ChannelMode::Timer);
	EXPECT_TRUE(updatedState.toggle);
	EXPECT_EQ(updatedState.timer, 100);
	EXPECT_TRUE(updatedState.timerEnabled);

	// Check that other channels remain unaffected (e.g. channel 2)
	ChannelState otherState = m_model->getChannelState(2);
	EXPECT_FALSE(otherState.enabled);
	EXPECT_EQ(otherState.mode, Channel::ChannelMode::Toggle);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test signal changed functionality.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, SignalChangedTest)
{
	bool signalTriggered = false;
	auto connection = m_model->signal_changed().connect([&]() {
		signalTriggered = true;
	});

	m_model->emit_changed();
	EXPECT_TRUE(signalTriggered);
	connection.disconnect();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test clone method.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ModelTest, CloneTest)
{
	m_model->add("device", "/dev/ttyUSB0");
	m_model->add("baud", "115200");

	auto clonedModel = m_model->clone();
	ASSERT_NE(clonedModel, nullptr);
	EXPECT_EQ(clonedModel->getEntity("device"), "/dev/ttyUSB0");
	EXPECT_EQ(clonedModel->getEntity("baud"), "115200");
}
