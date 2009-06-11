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
 * I/O functions
 */

#include "../../src/common.h"
#include "../../src/value.c"
#include <stdio.h>
#include <stdlib.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(2, sizeof(char *));

  funcs[0] = "print";

  return funcs;
}

p_val punt_print(p_val *args, p_var **vars) {
  p_val rval;

  int i;
  for(i = 0; i < val_llen(args); i++) {
    if(!strcmp(args[i].type, "str")) {
      printf("%s", (char *)args[i].val);
    } else if(!strcmp(args[i].type, "int")) {
      printf("%ld", *(int *)args[i].val);
    } else if(!strcmp(args[i].type, "float")) {
      printf("%lf", *(double *)args[i].val);
    } else {
      printf("<%s @ %p>", args[i].type, args[i].val);
    }
  }

  return rval;
}

