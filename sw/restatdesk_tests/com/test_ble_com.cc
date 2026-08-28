////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_ble_com.cc
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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <model/model_factory.h>
#include <com/ble/configurator/ble_com_configurator.h>
#include "test_mock_ible.h"
#include "test_mock_icom.h"

using namespace Electux::App::Com;
using namespace Electux::App::Model;
using namespace ::testing;

class BleComConfiguratorTest : public Test {
  protected:
    void SetUp() override {
        m_model = Electux::App::Model::createDefault();
        
        auto addrKey = m_model->toString(ModelBleKey::Address);
        auto serviceKey = m_model->toString(ModelBleKey::ServiceUuid);
        auto rxKey = m_model->toString(ModelBleKey::RxUuid);
        auto txKey = m_model->toString(ModelBleKey::TxUuid);

        m_model->add(addrKey, "00:11:22:33:44:55");
        m_model->add(serviceKey, "ffe0");
        m_model->add(rxKey, "ffe1");
        m_model->add(txKey, "ffe2");

        m_bleMock = std::make_unique<com::mock::MockIBle>();
        m_comMock = std::make_unique<com::mock::MockICom>();
        m_configurator = std::make_unique<BleComConfigurator>(m_bleMock.get());
    }

    std::unique_ptr<IModel> m_model;
    std::unique_ptr<com::mock::MockIBle> m_bleMock;
    std::unique_ptr<com::mock::MockICom> m_comMock;
    std::unique_ptr<BleComConfigurator> m_configurator;
};

TEST_F(BleComConfiguratorTest, ConfigureSuccessTest) {
    EXPECT_CALL(*m_comMock, open()).WillOnce(Return(true));

    bool result = m_configurator->configure(*m_model, m_comMock.get());

    EXPECT_TRUE(result);
    EXPECT_EQ(m_bleMock->m_address, "00:11:22:33:44:55");
    EXPECT_EQ(m_bleMock->m_serviceUuid, "ffe0");
    EXPECT_EQ(m_bleMock->m_rxUuid, "ffe1");
    EXPECT_EQ(m_bleMock->m_txUuid, "ffe2");
}

TEST_F(BleComConfiguratorTest, ConfigureFailureTest) {
    EXPECT_CALL(*m_comMock, open()).WillOnce(Return(false));

    bool result = m_configurator->configure(*m_model, m_comMock.get());

    EXPECT_FALSE(result);
}
