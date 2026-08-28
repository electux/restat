////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// application.cc
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

#include <application.h>
#include <com/com_factory.h>
#include <com/configurator_factory.h>
#include <config/config_factory.h>
#include <log/log_factory.h>
#include <command/command_factory.h>
#include <model/model_factory.h>
#include <app_controller_factory.h>
#include <glibmm/miscutils.h>
#include <glibmm/refptr.h>
#include <iapp_controller.h>
#include <iostream>
#include <string_view>
#include <view/about/about.h>
#include <view/about/iabout_view.h>
#include <view/help/help.h>
#include <view/help/ihelp_view.h>
#include <view/home.h>
#include <view/ihome_view.h>
#include <view/settings/isettings_view.h>
#include <view/settings/settings.h>
#include <view/settings_setup.h>

namespace {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Application Internal Constants
    /// @{
    constexpr std::string_view cApplicationId{"electux.io.restatdesk"};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Application Mapper Parameters
    /// @{
    constexpr std::string_view cDetailedActionName{"app.quit"};
    constexpr std::string_view cKeyboardAccelerator{"<Primary>q"};
    constexpr std::string_view cFileQuitActionName{"quit"};
    constexpr std::string_view cOptionSettingsActionName{"settings"};
    constexpr std::string_view cHelpDocActionName{"doc"};
    constexpr std::string_view cHelpAboutActionName{"about"};
    constexpr std::string_view cCmdAllOnActionName{"cmd_all_on"};
    constexpr std::string_view cCmdAllOffActionName{"cmd_all_off"};
    constexpr std::string_view cCmdAllStatActionName{"cmd_all_stat"};
    constexpr std::string_view cCmdSysResetActionName{"cmd_sys_reset"};
    constexpr std::string_view cCmdSysIdActionName{"cmd_sys_id"};
    constexpr std::string_view cCmdSysVersionActionName{"cmd_sys_version"};
    constexpr std::string_view cCmdExecutePlanActionName{"cmd_execute_plan"};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Application Menu Labels and Actions
    /// @{
    constexpr std::string_view cFileLabel{"File"};
    constexpr std::string_view cFileQuitLabel{"_Quit"};
    constexpr std::string_view cFileQuitDetailedAction{"app.quit"};
    constexpr std::string_view cOptionLabel{"Option"};
    constexpr std::string_view cOptionSettingsLabel{"_Settings"};
    constexpr std::string_view cOptionSettingsDetailedAction{"app.settings"};
    constexpr std::string_view cCommandLabel{"Command"};
    constexpr std::string_view cCmdAllOnLabel{"_All Channels On"};
    constexpr std::string_view cCmdAllOnDetailedAction{"app.cmd_all_on"};
    constexpr std::string_view cCmdAllOffLabel{"_All Channels Off"};
    constexpr std::string_view cCmdAllOffDetailedAction{"app.cmd_all_off"};
    constexpr std::string_view cCmdAllStatLabel{"_All Status"};
    constexpr std::string_view cCmdAllStatDetailedAction{"app.cmd_all_stat"};
    constexpr std::string_view cCmdSysResetLabel{"_System Reset"};
    constexpr std::string_view cCmdSysResetDetailedAction{"app.cmd_sys_reset"};
    constexpr std::string_view cCmdSysIdLabel{"_Get Board ID"};
    constexpr std::string_view cCmdSysIdDetailedAction{"app.cmd_sys_id"};
    constexpr std::string_view cCmdSysVersionLabel{"_Get Version"};
    constexpr std::string_view cCmdSysVersionDetailedAction{"app.cmd_sys_version"};
    constexpr std::string_view cCmdExecutePlanLabel{"_Execute Plan"};
    constexpr std::string_view cCmdExecutePlanDetailedAction{"app.cmd_execute_plan"};
    constexpr std::string_view cHelpLabel{"Help"};
    constexpr std::string_view cHelpDocLabel{"_Documentation"};
    constexpr std::string_view cHelpDocDetailedAction{"app.doc"};
    constexpr std::string_view cHelpAboutLabel{"_About"};
    constexpr std::string_view cHelpAboutDetailedAction{"app.about"};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Application Console Messages
    /// @{
    constexpr std::string_view cStartupMsg{"Startup application..."};
    constexpr std::string_view cStartupDoneMsg{"Startup application done."};
    constexpr std::string_view cActivateMsg{"Activate application..."};
    constexpr std::string_view cActivateDoneMsg{"Activate application done."};
    constexpr std::string_view cShutdownMsg{"Shutting down application..."};
    constexpr std::string_view cQuitMsg{"Quit application."};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App;

EntryApplication::EntryApplication(bool verbose) : Gtk::Application(cApplicationId.data()), m_verbose(verbose) {
    auto config = Model::createDefault();
    auto configManager = Config::createConfigManager(std::move(config), m_verbose);

    auto serial = Com::createSerialCom(m_verbose);
    auto *serialPtr = serial.get();
    auto serialConfigurator = Com::createSerialConfigurator(serialPtr);

    auto tcp = Com::createTcpCom(m_verbose);
    auto *tcpPtr = tcp.get();
    auto tcpConfigurator = Com::createTcpConfigurator(tcpPtr);

    auto ble = Com::createBleCom(m_verbose);
    auto *blePtr = ble.get();
    auto bleConfigurator = Com::createBleConfigurator(blePtr);

    auto switchableCom = Com::createSwitchableCom(
        m_verbose, std::move(serial), std::move(tcp), std::move(ble)
    );
    auto *switchableComPtr = switchableCom.get();
 
    auto configurator = Com::createSwitchableConfigurator(
        switchableComPtr, std::move(serialConfigurator),
        std::move(tcpConfigurator), std::move(bleConfigurator)
    );
 
    auto logger = Logger::createLogger();
    auto commandFormatter = Command::createCommandFormatter();
    auto responseProcessor = Command::createResponseProcessor();
 
    m_controller = createAppController(
        std::move(configManager), std::move(switchableCom),
        std::move(configurator), std::move(logger), std::move(commandFormatter),
        std::move(responseProcessor)
    );
 
    Glib::set_application_name(cApplicationId.data());
}
 
EntryApplication::~EntryApplication() = default;
 
Glib::RefPtr<EntryApplication> EntryApplication::create(bool verbose) {
    return Glib::make_refptr_for_instance<EntryApplication>(
        new EntryApplication(verbose)
    );
}

void EntryApplication::mapping() {
    set_accel_for_action(
        cDetailedActionName.data(), cKeyboardAccelerator.data()
    );

    add_action(
        cFileQuitActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionQuit)
    );
    add_action(
        cOptionSettingsActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionSettings)
    );
    add_action(
        cCmdAllOnActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdAllOn)
    );
    add_action(
        cCmdAllOffActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdAllOff)
    );
    add_action(
        cCmdAllStatActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdAllStat)
    );
    add_action(
        cCmdSysResetActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdSysReset)
    );
    add_action(
        cCmdSysIdActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdSysId)
    );
    add_action(
        cCmdSysVersionActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdSysVersion)
    );
    add_action(
        cCmdExecutePlanActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionCmdExecutePlan)
    );
    add_action(
        cHelpDocActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionDoc)
    );
    add_action(
        cHelpAboutActionName.data(),
        sigc::mem_fun(*this, &EntryApplication::onActionAbout)
    );

    m_home->connect_close_request(
        sigc::mem_fun(*this, &EntryApplication::onHandleClose)
    );
    m_settings->setupChanged().connect(
        sigc::mem_fun(*this, &EntryApplication::onSetupChanged)
    );
    m_home->controlChanged().connect(
        sigc::mem_fun(*this, &EntryApplication::onSetupChanged)
    );
    m_home->signal_execute_plan().connect(
        sigc::mem_fun(*this, &EntryApplication::onActionCmdExecutePlan)
    );
    m_controller->signal_data_received().connect(
        sigc::mem_fun(*m_home, &View::IHomeView::postData)
    );
}

void EntryApplication::on_startup() {
    if (m_verbose) {
        std::cout << cStartupMsg << std::endl;
    }
    Gtk::Application::on_startup();

    m_home = std::make_unique<View::AppHome>();
    m_settings = std::make_unique<View::Settings::AppSettings>();
    m_help = std::make_unique<View::Help::AppHelp>();
    m_about = std::make_unique<View::About::AppAbout>();

    m_controller->startup();

    auto menu = Gio::Menu::create();
    auto submenu_file = Gio::Menu::create();
    submenu_file->append(cFileQuitLabel.data(), cFileQuitDetailedAction.data());
    menu->append_submenu(cFileLabel.data(), submenu_file);

    auto submenu_option = Gio::Menu::create();
    submenu_option->append(
        cOptionSettingsLabel.data(), cOptionSettingsDetailedAction.data()
    );
    menu->append_submenu(cOptionLabel.data(), submenu_option);

    auto submenu_command = Gio::Menu::create();
    submenu_command->append(
        cCmdAllOnLabel.data(), cCmdAllOnDetailedAction.data()
    );
    submenu_command->append(
        cCmdAllOffLabel.data(), cCmdAllOffDetailedAction.data()
    );
    submenu_command->append(
        cCmdAllStatLabel.data(), cCmdAllStatDetailedAction.data()
    );
    submenu_command->append(
        cCmdSysResetLabel.data(), cCmdSysResetDetailedAction.data()
    );
    submenu_command->append(
        cCmdSysIdLabel.data(), cCmdSysIdDetailedAction.data()
    );
    submenu_command->append(
        cCmdSysVersionLabel.data(), cCmdSysVersionDetailedAction.data()
    );
    submenu_command->append(
        cCmdExecutePlanLabel.data(), cCmdExecutePlanDetailedAction.data()
    );
    menu->append_submenu(cCommandLabel.data(), submenu_command);

    auto submenu_help = Gio::Menu::create();
    submenu_help->append(cHelpDocLabel.data(), cHelpDocDetailedAction.data());
    submenu_help->append(
        cHelpAboutLabel.data(), cHelpAboutDetailedAction.data()
    );
    menu->append_submenu(cHelpLabel.data(), submenu_help);
    set_menubar(menu);
    mapping();
    add_window(m_home->getGtkWindow());

    m_controller->getModel().signal_changed().connect([this]() {
        SettingsSetup setup;
        setup.m_config = m_controller->getModel().clone();
        m_settings->setSettingsSetup(setup);
        m_settings->updateUiData();
        m_home->setControlSetup(setup);
        m_home->updateUiData();
    });

    SettingsSetup setup;
    setup.m_config = m_controller->getModel().clone();
    m_settings->setSettingsSetup(setup);
    m_settings->updateUiData();
    m_home->setControlSetup(setup);
    m_home->updateUiData();

    if (m_verbose) {
        std::cout << cStartupDoneMsg << std::endl;
    }
}

void EntryApplication::on_activate() {
    if (m_verbose) {
        std::cout << cActivateMsg << std::endl;
    }
    Gtk::Application::on_activate();
    m_home->show();
    if (m_verbose) {
        std::cout << cActivateDoneMsg << std::endl;
    }
}

void EntryApplication::on_shutdown() {
    if (m_verbose) {
        std::cout << cShutdownMsg << std::endl;
    }
    m_controller->shutdown();
    Gtk::Application::on_shutdown();
}

void EntryApplication::onActionQuit() {
    if (m_verbose) {
        std::cout << cQuitMsg << std::endl;
    }
    m_home->hide();
    remove_window(m_home->getGtkWindow());
    quit();
}

bool EntryApplication::onHandleClose() {
    onActionQuit();
    return false;
}

void EntryApplication::onActionSettings() { m_settings->show(); }

void EntryApplication::onActionDoc() { m_help->show(); }

void EntryApplication::onActionAbout() { m_about->show(); }

void EntryApplication::onSetupChanged(const SettingsSetup &setup) {
    m_controller->onSetupChanged(setup);
}

void EntryApplication::onActionCmdAllOn() {
    m_controller->turnOnAllChannels();
}

void EntryApplication::onActionCmdAllOff() {
    m_controller->turnOffAllChannels();
}

void EntryApplication::onActionCmdAllStat() {
    m_controller->requestAllChannelsStatus();
}

void EntryApplication::onActionCmdSysReset() {
    m_controller->resetSystem();
}

void EntryApplication::onActionCmdSysId() {
    m_controller->requestBoardId();
}

void EntryApplication::onActionCmdSysVersion() {
    m_controller->requestVersion();
}

void EntryApplication::onActionCmdExecutePlan() {
    m_controller->executePlan();
}
