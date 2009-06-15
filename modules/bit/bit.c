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
 * bitwise operations
 */

#include "../../src/common.h"
#include "../../src/value.h"
#include "../../src/pointer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkargs(p_val *args, char *func, int minargs) {
  if(val_llen(args) != minargs) {
    fprintf(stderr, "%s: %d %s required\n", func, minargs, (minargs == 1) ? "arg" : "args");
    exit(1);
  }

  int i;
  for(i = 0; i < val_llen(args); i++) {
    if(strcmp(args[i].type, "int")) {
      fprintf(stderr, "%s: all args must be ints\n", func);
      exit(1);
    }
  }
}

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(7, sizeof(char *));

  funcs[0] = "bitnot";
  funcs[1] = "bitor";
  funcs[2] = "bitand";
  funcs[3] = "bitxor";
  funcs[4] = "bitl";
  funcs[5] = "bitr";

  return funcs;
}

p_val punt_bitnot(p_val *args, p_var **vars) {
  p_val rval = val_make();

  checkargs(args, "bitnot", 1);
  rval.val = ptr_dupint(~*(long *)args[0].val);

  return rval;
}

p_val punt_bitor(p_val *args, p_var **vars) {
  p_val rval = val_make();

  checkargs(args, "bitor", 2);
  rval.val = ptr_dupint(*(long *)args[0].val | *(long *)args[1].val);

  return rval;
}

p_val punt_bitand(p_val *args, p_var **vars) {
  p_val rval = val_make();

  checkargs(args, "bitand", 2);
  rval.val = ptr_dupint(*(long *)args[0].val & *(long *)args[1].val);

  return rval;
}

p_val punt_bitxor(p_val *args, p_var **vars) {
  p_val rval = val_make();

  checkargs(args, "bitxor", 2);
  rval.val = ptr_dupint(*(long *)args[0].val ^ *(long *)args[1].val);

  return rval;
}

p_val punt_bitl(p_val *args, p_var **vars) {
  p_val rval = val_make();

  checkargs(args, "bitl", 2);
  rval.val = ptr_dupint(*(long *)args[0].val << *(long *)args[1].val);

  return rval;
}

p_val punt_bitr(p_val *args, p_var **vars) {
  p_val rval = val_make();

  checkargs(args, "bitr", 2);
  rval.val = ptr_dupint(*(long *)args[0].val >> *(long *)args[1].val);

  return rval;
}

