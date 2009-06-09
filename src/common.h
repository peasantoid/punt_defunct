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

/* value */
typedef struct {
  char *type; /* test: if null, not init'd */
  void *val;
} p_val;
typedef p_val p_tok; /* essentially the same thing; this is for clarity */
/* 
 * note: value/token lists must be terminated by a "null" token; see above comment
 * next to < char *type; >
 */

/* variable */
typedef struct {
  char *id, *type;
  void *val;
} p_var;
/* same thing with variable lists */

#endif

