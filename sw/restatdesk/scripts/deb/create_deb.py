# -*- coding: UTF-8 -*-

'''
Module
    create_deb.py
Copyright
    Copyright (C) 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
    restat is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    restat is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    A Python script for creating a Debian installation package (.deb) for restatdesk.
'''

from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
from typing import Final

__author__: str = 'Vladimir Roncevic'
__copyright__: str = '(C) 2026, https://vroncevic.github.io/restat'
__credits__: list[str] = ['Vladimir Roncevic', 'Python Software Foundation']
__license__: str = 'https://github.com/vroncevic/restat/blob/dev/LICENSE'
__version__: str = '1.0.0'
__maintainer__: str = 'Vladimir Roncevic'
__email__: str = 'elektron.ronca@gmail.com'
__status__: str = 'Updated'

# Resolve paths dynamically relative to script location
SCRIPT_DIR: Final[str] = os.path.dirname(os.path.abspath(__file__))
SW_DIR: Final[str] = os.path.abspath(os.path.join(SCRIPT_DIR, '..', '..'))
REPO_ROOT: Final[str] = os.path.abspath(os.path.join(SW_DIR, '..', '..'))

BUILD_DIR: Final[str] = os.path.join(SW_DIR, 'build')
MAKEFILE_PATH: Final[str] = os.path.join(BUILD_DIR, 'Makefile')
BINARY_PATH: Final[str] = os.path.join(BUILD_DIR, 'restatdesk')
LOGO_PATH: Final[str] = os.path.join(REPO_ROOT, 'docs', 'restat_logo.png')
DEB_DIST_DIR: Final[str] = os.path.join(BUILD_DIR, 'deb_dist')


def get_version(makefile_path: str) -> str:
    """
    Extract the version number from the Makefile.

    :param makefile_path: Absolute path to the Makefile.
    :return: Version string, or '1.0.0' if not found or readable.
    """
    try:
        with open(makefile_path, 'r', encoding='utf-8') as f:
            for line in f:
                match = re.match(r'^\s*#\s*@version\s+(\S+)', line)
                if match:
                    return match.group(1)
    except OSError as e:
        print(f"Warning: Could not read version from Makefile: {e}")
    return '1.0.0'


def get_architecture() -> str:
    """
    Query the package architecture of the host system.

    :return: Architecture string (e.g., 'amd64', 'arm64').
    """
    try:
        result = subprocess.run(
            ['dpkg', '--print-architecture'],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout.strip()
    except (subprocess.SubprocessError, FileNotFoundError):
        print("Warning: dpkg not found or failed to run. Defaulting to 'amd64'.")
        return 'amd64'


def create_control_file(
    dest_path: str,
    version: str,
    arch: str
) -> None:
    """
    Generate the DEBIAN/control file.

    :param dest_path: Absolute path to write the control file to.
    :param version: Package version.
    :param arch: Package architecture.
    """
    content = f"""Package: restatdesk
Version: {version}
Section: utils
Priority: optional
Architecture: {arch}
Maintainer: Vladimir Roncevic <elektron.ronca@gmail.com>
Depends: libgtkmm-4.0-1 | libgtkmm-4.0-1t64, libc6, libgcc-s1, libstdc++6
Description: Desktop GUI application for restat hardware controller
 A desktop GUI application built in C++ using gtkmm for orchestrating
 and controlling restat hardware controllers (relays, LED, buzzer, etc.)
 over Serial, TCP, and BLE interfaces.
"""
    with open(dest_path, 'w', encoding='utf-8') as f:
        f.write(content)


def create_desktop_entry(dest_path: str) -> None:
    """
    Generate the desktop application launcher entry.

    :param dest_path: Absolute path to write the desktop file to.
    """
    content = """[Desktop Entry]
Version=1.0
Type=Application
Name=restat Desk
Comment=Desktop GUI for restat hardware controller
Exec=restatdesk
Icon=restatdesk
Terminal=false
Categories=Utility;Development;
"""
    with open(dest_path, 'w', encoding='utf-8') as f:
        f.write(content)


def main() -> int:
    """
    Main entry point for creating the .deb installation package.

    :return: Exit status code (0 for success, 1 for failure).
    """
    print("Starting Debian package creation for restatdesk...")

    # 1. Validation checks
    if not os.path.exists(BINARY_PATH):
        print(f"Error: Executable not found at '{BINARY_PATH}'.")
        print("Please build the application first by running 'make release' or 'make' in sw/restatdesk/build/")
        return 1

    if not os.path.exists(LOGO_PATH):
        print(f"Warning: Logo not found at '{LOGO_PATH}'. Package will be created without an application icon.")

    if not shutil.which('dpkg-deb'):
        print("Error: 'dpkg-deb' utility is not installed. Debian packaging is not supported on this host.")
        return 1

    # 2. Package parameters
    version = get_version(MAKEFILE_PATH)
    arch = get_architecture()
    package_name = f"restatdesk_{version}_{arch}"
    tmp_pkg_dir = os.path.join(DEB_DIST_DIR, package_name)

    print(f"Target package: {package_name}.deb")
    print(f"Version: {version}")
    print(f"Architecture: {arch}")

    # 3. Create clean temporary directory structure
    if os.path.exists(tmp_pkg_dir):
        shutil.rmtree(tmp_pkg_dir)

    debian_dir = os.path.join(tmp_pkg_dir, "DEBIAN")
    bin_dir = os.path.join(tmp_pkg_dir, "usr", "bin")
    apps_dir = os.path.join(tmp_pkg_dir, "usr", "share", "applications")
    pixmaps_dir = os.path.join(tmp_pkg_dir, "usr", "share", "pixmaps")

    os.makedirs(debian_dir, exist_ok=True)
    os.makedirs(bin_dir, exist_ok=True)
    os.makedirs(apps_dir, exist_ok=True)
    os.makedirs(pixmaps_dir, exist_ok=True)

    # 4. Copy and process binary
    pkg_binary_path = os.path.join(bin_dir, "restatdesk")
    print(f"Copying binary to {pkg_binary_path}...")
    shutil.copy2(BINARY_PATH, pkg_binary_path)

    # Strip binary to remove debugging symbols
    if shutil.which('strip'):
        print("Stripping debug symbols from packaged binary...")
        try:
            subprocess.run(['strip', pkg_binary_path], check=True)
        except subprocess.SubprocessError as e:
            print(f"Warning: Failed to strip binary: {e}")
    else:
        print("Warning: 'strip' utility not found. Packaging unstripped binary.")

    # Set binary permission to 755 (executable)
    os.chmod(pkg_binary_path, 0o755)

    # 5. Copy logo/icon
    if os.path.exists(LOGO_PATH):
        pkg_icon_path = os.path.join(pixmaps_dir, "restatdesk.png")
        print(f"Copying application icon to {pkg_icon_path}...")
        shutil.copy2(LOGO_PATH, pkg_icon_path)
        os.chmod(pkg_icon_path, 0o644)

    # 6. Generate control file and desktop entry
    print("Generating DEBIAN/control file...")
    create_control_file(os.path.join(debian_dir, "control"), version, arch)
    os.chmod(os.path.join(debian_dir, "control"), 0o644)

    print("Generating desktop launcher...")
    create_desktop_entry(os.path.join(apps_dir, "restatdesk.desktop"))
    os.chmod(os.path.join(apps_dir, "restatdesk.desktop"), 0o644)

    # 7. Run dpkg-deb --build
    os.makedirs(DEB_DIST_DIR, exist_ok=True)
    deb_output_path = os.path.join(DEB_DIST_DIR, f"{package_name}.deb")
    print(f"Building Debian package in {deb_output_path}...")

    try:
        subprocess.run(
            ['dpkg-deb', '--root-owner-group', '--build', tmp_pkg_dir, deb_output_path],
            check=True
        )
        print("Debian package built successfully!")
    except subprocess.SubprocessError as e:
        print(f"Error: dpkg-deb build failed: {e}")
        return 1
    finally:
        # Cleanup temporary files
        print("Cleaning up temporary packaging directory...")
        shutil.rmtree(tmp_pkg_dir)

    print(f"Finished. Package is available at: {deb_output_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
