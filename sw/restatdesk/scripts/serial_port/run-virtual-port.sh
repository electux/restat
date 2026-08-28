#!/usr/bin/env bash
#
# @brief   Run socat for virtual serial port
# @version ver.1.0
# @date    Sat Aug 22 10:19:45 AM CEST 2026
# @company None, free software to use 2026
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

socat -d -d pty,raw,echo=0,link=/tmp/ttyV0 pty,raw,echo=0,link=/tmp/ttyV1
