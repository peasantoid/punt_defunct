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
 * comparison functions
 */

#include "../../src/common.h"
#include "../../src/value.h"
#include "../../src/pointer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(9, sizeof(char *));

  funcs[0] = "yes";
  funcs[1] = "no";
  funcs[2] = "eq";
  funcs[3] = "ne";
  funcs[4] = "lt";
  funcs[5] = "gt";
  funcs[6] = "le";
  funcs[7] = "ge";

  return funcs;
}

p_val punt_yes(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 1) {
    fprintf(stderr, "yes: 1 arg required\n");
    exit(1);
  }
  *(long *)rval.val = val_true(args[0]);

  return rval;
}

p_val punt_no(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 1) {
    fprintf(stderr, "no: 1 arg required\n");
    exit(1);
  }
  *(long *)rval.val = !val_true(args[0]);

  return rval;
}

p_val punt_eq(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 2) {
    fprintf(stderr, "eq: 2 arguments required\n");
    exit(1);
  }
  rval.val = ptr_dupint(val_cmp(args[0], args[1], "eq"));

  return rval;
}

p_val punt_ne(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 2) {
    fprintf(stderr, "ne: 2 arguments required\n");
    exit(1);
  }
  rval.val = ptr_dupint(val_cmp(args[0], args[1], "ne"));

  return rval;
}

p_val punt_lt(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 2) {
    fprintf(stderr, "lt: 2 arguments required\n");
    exit(1);
  }
  rval.val = ptr_dupint(val_cmp(args[0], args[1], "lt"));

  return rval;
}

p_val punt_gt(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 2) {
    fprintf(stderr, "gt: 2 arguments required\n");
    exit(1);
  }
  rval.val = ptr_dupint(val_cmp(args[0], args[1], "gt"));

  return rval;
}

p_val punt_le(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 2) {
    fprintf(stderr, "le: 2 arguments required\n");
    exit(1);
  }
  rval.val = ptr_dupint(val_cmp(args[0], args[1], "le"));

  return rval;
}

p_val punt_ge(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 2) {
    fprintf(stderr, "ge: 2 arguments required\n");
    exit(1);
  }
  rval.val = ptr_dupint(val_cmp(args[0], args[1], "ge"));

  return rval;
}

