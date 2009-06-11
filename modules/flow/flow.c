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
 * flow control functions
 */

#include "../../src/common.h"
#include "../../src/value.c"
#include "../../src/engine.c"
#include <stdio.h>
#include <stdlib.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(5, sizeof(char *));

  funcs[0] = "if";
  funcs[1] = "elif";
  funcs[2] = "else";
  funcs[3] = "while";
  funcs[4] = NULL;

  return funcs;
}

p_val punt_if(p_val *args, p_var **vars) {
  p_val rval;
  return rval;
}

