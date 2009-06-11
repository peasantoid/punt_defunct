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
 * variables
 */

#include "../../src/common.h"
#include "../../src/value.c"
#include "../../src/variable.c"
#include <stdio.h>
#include <stdlib.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(2, sizeof(char *));

  funcs[0] = "bind";

  return funcs;
}

p_val punt_bind(p_val *args, p_var **vars) {
  p_val rval;

  if(val_llen(args) != 2) {
    fprintf(stderr, "bind: 2 arguments required\n");
    exit(1);
  } else if(strcmp(args[0].type, "symbol")) {
    fprintf(stderr, "bind: argument 1 must be symbol\n");
    exit(1);
  }

  var_lset(vars, (char *)args[0].val, args[1].type, args[1].val);

  return rval;
}

