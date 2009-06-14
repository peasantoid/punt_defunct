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
 * string manipulation
 */

#define _GNU_SOURCE
#include "../../src/common.h"
#include "../../src/value.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(4, sizeof(char *));

  funcs[0] = "sfmt";
  /*funcs[1] = "sfind";
  funcs[2] = "srepl";*/

  return funcs;
}

p_val punt_sfmt(p_val *args, p_var **vars) {
  p_val rval;
    rval.type = "str";
    rval.val = (void *)"";
  
  int i;
  for(i = 0; i < val_llen(args); i++) {
    if(!strcmp(args[i].type, "str")) {
      asprintf((char **)&rval.val, "%s%s", (char *)rval.val, (char *)args[i].val);
    } else if(!strcmp(args[i].type, "int")) {
      asprintf((char **)&rval.val, "%s%ld", (char *)rval.val, *(long *)args[i].val);
    } else if(!strcmp(args[i].type, "float")) {
      asprintf((char **)&rval.val, "%s%lf", (char *)rval.val, *(double *)args[i].val);
    } else {
      asprintf((char **)&rval.val, "%s<%s @ %p>", (char *)rval.val, args[i].type, args[i].val);
    }
  }

  return rval;
}

