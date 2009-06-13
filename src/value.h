/*
 * This file is part of punt.
 *
 * punt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * punt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with punt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HAVE_TOKEN_H
#define HAVE_TOKEN_H

#include "common.h"

p_val val_make();
int val_true(p_val);
double val_getnum(p_val);
int val_cmp(p_val, p_val, char *);
int val_llen(p_val *);
void val_ldup(p_val *, p_val *);
void val_lappend(p_val **, char *, void *);

#endif

