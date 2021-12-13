/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * restat_desktop.h
 * Copyright (C) 2021 Vladimir Roncevic <elektron.ronca@gmail.com>
 * 
 * restat is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * restat is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RESTAT_DESKTOP_H
#define RESTAT_DESKTOP_H

#include <gtkmm/window.h>
#include <gtkmm/grid.h>

#define RESTAT_TITLE "restat"
#define RESTAT_VERSION "1.0.0"
#define RESTAT_BORDER_WIDTH 10

class Restat : public Gtk::Window
{
public:
  Restat();
  ~Restat();

protected:
  Gtk::Grid main_grid;
};

#endif
