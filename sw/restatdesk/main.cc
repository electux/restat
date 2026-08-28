////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// main.cc
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
#include <application.h>
#include <string>

using namespace Electux::App;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief The main entry point of the restatdesk application.
///
/// This function initializes the entry application and starts the main
/// execution loop, returning the final exit status.
///
/// @param argc [in] The number of command-line arguments.
/// @param argv [in] The array of command-line arguments.
/// @return The exit status of the application (0 for success).
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    bool verbose = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-v" || std::string(argv[i]) == "--verbose") {
            verbose = true;
            break;
        }
    }

    auto app = EntryApplication::create(verbose);
    const int status = app->run(argc, argv);

    return status;
}
