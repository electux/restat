////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// about.cc
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

#include <vector>
#include <view/about/about.h>

namespace {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Application About Dialog Metadata
    /// @{
    constexpr std::string_view cProgramName{"restatdesk"};
    constexpr std::string_view cProgramVersion{"1.0.0"};
    constexpr std::string_view cProgramCopyright{
        "Vladimir Roncevic <elektron.ronca@gmail.com>"
    };
    constexpr std::string_view cProgramComments{
        "This is restatdesk application."
    };
    constexpr std::string_view cProgramLicense{"GPLv3"};
    constexpr std::string_view cProgramWebsite{
        "https://electux.github.io/restat"
    };
    constexpr std::string_view cProgramWebsiteLabel{"electux.github.io/restat"
    };
    constexpr std::string_view cProgramAuthors{"Vladimir Roncevic"};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::View::About;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief AppAbout constructor.
///
/// Configures the Gtk::AboutDialog with application-specific information
/// including name, version, copyright, and developer credits.
////////////////////////////////////////////////////////////////////////////////////////////////////////
AppAbout::AppAbout() {
    set_program_name(cProgramName.data());
    set_version(cProgramVersion.data());
    set_copyright(cProgramCopyright.data());
    set_comments(cProgramComments.data());
    set_license(cProgramLicense.data());
    set_website(cProgramWebsite.data());
    set_website_label(cProgramWebsiteLabel.data());

    // Setup authors list
    std::vector<Glib::ustring> list_authors;
    list_authors.push_back(cProgramAuthors.data());
    set_authors(list_authors);

    set_hide_on_close(true);
}

void AppAbout::show() { set_visible(true); }
