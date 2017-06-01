/* our datatypes and global variables
 * Copyright (C) 2000, 2001, 2002, 2003, 2004 Shawn Betts <sabetts@vcn.bc.ca>
 *
 * This file is part of ratpoison.
 *
 * ratpoison is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * ratpoison is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA
 */

#ifndef _RATPOISON_SCREEN_MATCHERS_H
#define _RATPOISON_SCREEN_MATCHERS_H

#include "data.h"

void
rp_screen_matchers_init(struct rp_screen_matchers * matchers);

void
rp_screen_matchers_free(struct rp_screen_matchers * matchers);

int
rp_screen_matchers_set_regex(struct rp_screen_matchers * matchers,
                             int screen,
                             const char * fmt);

int
rp_screen_matchers_find_screen(struct rp_screen_matchers * matchers,
                               const char * str);

#endif // _RATPOISON_SCREEN_MATCHERS_H
