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
#include "../../src/value.h"
#include "../../src/engine.h"
#include "../../src/variable.h"
#include "../../src/pointer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(5, sizeof(char *));

  funcs[0] = "give";
  funcs[1] = "exit";
  funcs[2] = "if";
  funcs[3] = "either";

  return funcs;
}

p_val punt_give(p_val *args, p_var **vars) {
  if(val_llen(args) != 1) {
    fprintf(stderr, "give: 1 arg required\n");
    exit(1);
  }
  return args[0];
}

p_val punt_exit(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(val_llen(args) != 1) {
    fprintf(stderr, "exit: 1 argument required\n");
    exit(1);
  } else if(strcmp(args[0].type, "int")) {
    fprintf(stderr, "exit: argument 1 must be of type \"int\"\n");
    exit(1);
  }
  exit(*(long *)args[0].val);

  return rval;
}

p_val punt_if(p_val *args, p_var **vars) {
  p_val rval = val_make();
  
  if(val_llen(args) != 2) {
    fprintf(stderr, "if: 2 arguments required\n");
    exit(1);
  } else if(strcmp(args[1].type, "block")) {
    fprintf(stderr, "if: argument 2 must be of type \"block\"\n");
    exit(1);
  }

  if(val_true(args[0])) {
    rval = run_tokens((p_val *)args[1].val, vars);
  }

  return rval;
}

p_val punt_either(p_val *args, p_var **vars) {
  p_val rval = val_make();
  
  if(val_llen(args) != 3) {
    fprintf(stderr, "either: 3 arguments required\n");
    exit(1);
  } else if(strcmp(args[1].type, "block") || strcmp(args[2].type, "block")) {
    fprintf(stderr, "either: arguments 1 and 2 must be of type \"block\"\n");
    exit(1);
  }

  rval = val_true(args[0]) ?
    run_tokens((p_val *)args[1].val, vars) :
    run_tokens((p_val *)args[2].val, vars);

  return rval;
}

