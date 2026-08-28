restat
-------

**restat** is controlled relay-interface station for automatization.

The README is used to introduce the tool and provide instructions on
how to install the tool, any machine dependencies it may have and any
other information that should be provided before the tool is installed.

.. toctree::
   :hidden:

   self

|GitHub issues| |Documentation Status| |GitHub contributors| |restat_base C checker| |restatdesk CC checker| |restatdesk build checker| |restat toc|

.. |GitHub issues| image:: https://img.shields.io/github/issues/electux/restat.svg
   :target: https://github.com/electux/restat/issues

.. |GitHub contributors| image:: https://img.shields.io/github/contributors/electux/restat.svg
   :target: https://github.com/electux/restat/graphs/contributors

.. |Documentation Status| image:: https://readthedocs.org/projects/restat/badge/?version=latest
   :target: https://restat.readthedocs.io/projects/restat/en/latest/?badge=latest

.. |restat_base C checker| image:: https://github.com/electux/restat/actions/workflows/restat_base_c_checker.yml/badge.svg
   :target: https://github.com/electux/restat/actions/workflows/restat_base_c_checker.yml

.. |restatdesk CC checker| image:: https://github.com/electux/restat/actions/workflows/restat_desktop_cc_checker.yml/badge.svg
   :target: https://github.com/electux/restat/actions/workflows/restat_desktop_cc_checker.yml

.. |restatdesk build checker| image:: https://github.com/electux/restat/actions/workflows/restat_desktop_cc_checker_build.yml/badge.svg
   :target: https://github.com/electux/restat/actions/workflows/restat_desktop_cc_checker_build.yml

.. |restat toc| image:: https://github.com/electux/restat/actions/workflows/restat_toc.yml/badge.svg
   :target: https://github.com/electux/restat/actions/workflows/restat_toc.yml

System Components
-----------------

**restat** consists of two primary components:

1. restat Firmware (``restat_base``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A low-level C firmware designed for Pico RP2040 microcontrollers to actuate, time, and persist relay outputs.

* **Role**: Actuates 8 mechanical relay channels using high-precision timers and persists configurations directly to onboard Flash memory.
* **Features**:
  * Multi-interface Command Dispatcher (Serial, TCP/IP, BLE).
  * Variable Execution Plan Parser: Processes complex execution strings concurrently to set states and schedules.
  * Flash-Based Plan Persistence: Automatically stores execution plans at a ``1.5 MB`` flash offset (``0x180000``) and restores configurations upon reboot.
  * Precise Timing Engine: Millisecond-level accuracy for Timed modes.
  * Safety Watchdog & Sound Indicators: Recovery loops coupled with active buzzer signaling.

2. restatdesk GUI Application (``restatdesk``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A responsive, cross-platform C++ application built on **gtkmm 4** and **GTK 4**.

* **Role**: Configures, controls, and monitors the relay station in real-time.
* **Features**:

  * Real-Time LED Indicators: High-visibility green status lights showing live channel states.
  * Configurable Relay Modes:

    * **Toggle Mode**: Activates or deactivates relays on click.
    * **Timer Mode**: Executes timed sequences with flexible starting states (Active = ON on Start, Deactive = OFF on Start).

  * Dynamic Plan Builder: Serializes only active relay states into a single, variable-length plan command to protect relay lifespans.
  * Sleek Green-on-Black Dark Mode: Custom CSS styles compiled directly into the binary as GResource packages.
  * Multithreaded System Logs: Visualized console output and persistent file logging.


Command Interface (restat Protocol)
-----------------------------------

All commands sent to the ``restat_base`` firmware must be wrapped in start/end markers: ``<rs#TARGET#ACTION#PARAMS#end>``.

+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| Command                             | Action           | Description                                                                       |
+=====================================+==================+===================================================================================+
| ``<rs#sys#id#end>``                 | Identify         | Returns board identification (e.g. ``<rs#sys#rs:333:2023:0#end>``)                |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#sys#version#end>``            | Get Version      | Returns firmware version (e.g. ``<rs#sys#restat v1.0.0#end>``)                    |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#ch#X#on#end>``                | Channel ON       | Sets channel ``X`` (1-8) to ON (active) state                                     |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#ch#X#off#end>``               | Channel OFF      | Sets channel ``X`` (1-8) to OFF (deactive) state                                  |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#ch#X#tmr#MS#end>``            | Timed Channel    | Starts timer on channel ``X`` for ``MS`` milliseconds starting ON                 |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#all#on#end>``                 | All ON           | Turns all channels ON concurrently                                                |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#all#off#end>``                | All OFF          | Turns all channels OFF concurrently                                               |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#all#mask#MASK#end>``          | Binary Mask      | Sets all 8 channels to binary state ``MASK`` (e.g. ``10101010``)                  |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#all#plan#[plan_string]#end>`` | Execute Plan     | Sends a variable-length configuration plan containing relay states and saves      |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#ch#X#stat#end>``              | Channel Status   | Returns the status string of channel ``X``                                        |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#all#stat#end>``               | All Status       | Returns status dump for all channels                                              |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+
| ``<rs#sys#reset#end>``              | Reset            | Performs soft system reset using watchdog                                         |
+-------------------------------------+------------------+-----------------------------------------------------------------------------------+

Installation
------------

1. Firmware (``restat_base``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Setup the Raspberry Pi Pico SDK on your host system, then build:

.. code-block:: bash

   cd sw/restat_base
   mkdir -p build && cd build
   cmake ..
   make -j$(nproc)

Boot the board in BOOTSEL mode and copy the compiled ``restat_base.uf2`` to the Pico mass storage volume.

2. Desktop Application (``restatdesk``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Ensure all C++23 compiler tools and GTK 4 libraries are installed, then run:

.. code-block:: bash

   cd sw/restatdesk/build
   make all

The executable ``restatdesk`` will be ready inside the ``build/`` directory.

Usage
-----

1. GUI Panel
~~~~~~~~~~~~
Launch the desktop client:

.. code-block:: bash

   ./sw/restatdesk/build/restatdesk

Configure the connection (Serial, TCP/IP, or BLE) in the Settings window, toggle active relay options in the UI, and click **Execute Plan** in the main window or under the ``Command`` menu to transmit changes.

2. Test Commands
~~~~~~~~~~~~~~~~
Connect directly to the station via terminal console or socket connection (e.g. ``minicom`` or ``nc``) and send raw protocol frames:

.. code-block:: bash

   # Set channel 1 to ON
   <rs#ch#1#on#end>

Dependencies
------------

Firmware (``restat_base``)
~~~~~~~~~~~~~~~~~~~~~~~~~~
* Raspberry Pi Pico SDK (v1.5.0+)
* GCC ARM Embedded Toolchain (``arm-none-eabi-gcc``)
* CMake & GNU Make

Desktop GUI (``restatdesk``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* C++23 compatible compiler (GCC 13+)
* ``gtkmm-4.0`` & ``libgtk-4-dev``
* ``libserial-dev``
* ``pkg-config``
* GNU Make

Project Structure
-----------------

The codebase layout is structured as follows:

* `sw/restat_base/ <file:///data/dev/raspberry/restat/github/restat/sw/restat_base>`_ - Core Pico firmware:
  * ``src/command/`` - Dispatcher and frame parser.
  * ``src/device/`` - Watchdog, buzzer, relay, and flash persistence drivers.
* `sw/restat_base_tests/ <file:///data/dev/raspberry/restat/github/restat/sw/restat_base_tests>`_ - C++ GoogleTest suite for host-based firmware logic validation.
* `sw/restatdesk/ <file:///data/dev/raspberry/restat/github/restat/sw/restatdesk>`_ - GTK 4 client:
  * ``com/`` - Serial, TCP, and BLE client layers.
  * ``config/`` - File configuration load/store manager.
  * ``model/`` - Relay delegates, channel states, and business logic.
  * ``view/`` - GUI window tabs, widgets, and GResource styled assets.
* `sw/restatdesk_tests/ <file:///data/dev/raspberry/restat/github/restat/sw/restatdesk_tests>`_ - C++ GoogleTest suite for desktop client controllers and helpers.
* `docs/ <file:///data/dev/raspberry/restat/github/restat/docs>`_ - Documentation source files.

Copyright and licence
----------------------

|License: GPL v3| |License: Apache 2.0|

.. |License: GPL v3| image:: https://img.shields.io/badge/License-GPLv3-blue.svg
   :target: https://www.gnu.org/licenses/gpl-3.0

.. |License: Apache 2.0| image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg
   :target: https://opensource.org/licenses/Apache-2.0

Copyright (C) 2020 - 2024 by `electux.github.io/restat <https://electux.github.io/restat>`_

Lets help and support Raspberry PI && GNOME.

.. image:: https://raw.githubusercontent.com/electux/restat/master/docs/foundations.png
   :alt: Foundations
   :width: 192px
   :height: 109px


