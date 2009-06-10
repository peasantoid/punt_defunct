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

/*
 * typedefs and misc. shiz
 */

#ifndef HAVE_COMMON_H
#define HAVE_COMMON_H

/* value (or token -- essentially the same thing) */
typedef struct {
  char *type; /* if null, not init'd */
  void *val;
} p_val;
/* 
 * note: value lists must be terminated by a "null" item; see above comment
 * next to < char *type; >
 *
 * a null value /pointer/ indicates a list of length 0
 */

/* variable */
typedef struct {
  char *id, *type;
  void *val;
} p_var;
/* same thing with variable lists */

#endif

