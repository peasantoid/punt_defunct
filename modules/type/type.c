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
 * type functions
 */

#include "../../src/common.h"
#include "../../src/value.h"
#include <stdio.h>
#include <stdlib.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(2, sizeof(char *));

  funcs[0] = "typeof";

  return funcs;
}

p_val punt_typeof(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 1) {
    fprintf(stderr, "typeof: 1 argument required\n");
    exit(1);
  }

  rval.type = "str";
  rval.val = (void *)args[0].type;

  return rval;
}

