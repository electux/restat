#
# @brief   restatdesk
# @version 1.1.6
# @date    2024-07-21 16:05:11.341582
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

SOURCES = \
	../log/log.cc \
	../log/log_factory.cc \
	../config/config_manager_utils.cc \
	../config/config_manager.cc \
	../config/config_factory.cc \
	../com/serial/serialw/serial_lib_wrapper.cc \
	../com/serial/serial_utils.cc \
	../com/serial/serial_com.cc \
	../com/serial/configurator/serial_com_configurator.cc \
	../com/tcp/tcp_com.cc \
	../com/tcp/configurator/tcp_com_configurator.cc \
	../com/ble/ble_com.cc \
	../com/ble/configurator/ble_com_configurator.cc \
	../com/ble/bluez/bluez_ble_client.cc \
	../com/ble/bluez/bluez_device_resolver.cc \
	../com/switchable_com.cc \
	../com/com_factory.cc \
	../com/switchable_com_configurator.cc \
	../com/configurator_factory.cc \
	../model/model.cc \
	../model/model_factory.cc \
	../model/delegate/control/control_model_delegate.cc \
	../model/delegate/serial/serial_model_delegate.cc \
	../model/delegate/general/general_model_delegate.cc \
	../model/delegate/ble/ble_model_delegate.cc \
	../model/delegate/log/log_model_delegate.cc \
	../view/settings_setup.cc \
	../view/channel/channel_widget.cc \
	../view/channel/page/mode_page_toggle.cc \
	../view/channel/page/mode_page_timer.cc \
	../view/home.cc \
	../view/about/about.cc \
	../view/help/help.cc \
	../view/settings/general/general_settings_tab.cc \
	../view/settings/serial/serial_settings_tab.cc \
	../view/settings/tcp/tcp_settings_tab.cc \
	../view/settings/ble/ble_settings_tab.cc \
	../view/settings/log/log_settings_tab.cc \
	../view/settings/settings.cc \
	../application.cc \
	../app_controller.cc \
	../app_controller_factory.cc \
	../command/formatter/command_formatter.cc \
	../command/command_factory.cc \
	../command/processor/response_processor.cc \
	../resources.cc \
	../main.cc
