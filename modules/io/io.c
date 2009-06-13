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
#include "../../src/value.h"
#include "../../src/variable.h"
#include "../../src/pointer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(6, sizeof(char *));

  funcs[0] = "stdin";
  funcs[1] = "stdout";
  funcs[2] = "stderr";
  funcs[3] = "fput";
  funcs[4] = "fopen";

  return funcs;
}

p_val punt_stdin(p_val *args, p_var **vars) {
  p_val rval;
  rval.type = "file";
  rval.val = (void *)stdin;
  return rval;
}

p_val punt_stdout(p_val *args, p_var **vars) {
  p_val rval;
  rval.type = "file";
  rval.val = (void *)stdout;
  return rval;
}

p_val punt_stderr(p_val *args, p_var **vars) {
  p_val rval;
  rval.type = "file";
  rval.val = (void *)stderr;
  return rval;
}

p_val punt_fput(p_val *args, p_var **vars) {
  p_val rval = val_make();

  if(!val_llen(args)) {
    fprintf(stderr, "fput: 1 arg required\n");
    exit(1);
  } else if(strcmp(args[0].type, "file")) {
    fprintf(stderr, "fput: arg 1 must be file\n");
    exit(1);
  }

  FILE *fp = (FILE *)args[0].val;
  int i;
  for(i = 1; i < val_llen(args); i++) {
    if(!strcmp(args[i].type, "str")) {
      fprintf(fp, "%s", (char *)args[i].val);
    } else if(!strcmp(args[i].type, "int")) {
      fprintf(fp, "%ld", *(long *)args[i].val);
    } else if(!strcmp(args[i].type, "float")) {
      fprintf(fp, "%lf", *(double *)args[i].val);
    } else {
      fprintf(fp, "<%s @ %p>", args[i].type, args[i].val);
    }
  }

  return rval;
}

p_val punt_fopen(p_val *args, p_var **vars) {
  p_val rval;

  if(val_llen(args) != 2) {
    fprintf(stderr, "fopen: 2 args required\n");
    exit(1);
  }
  int i;
  for(i = 0; i < val_llen(args); i++) {
    if(strcmp(args[i].type, "str")) {
      fprintf(stderr, "fopen: all args must be strings\n");
      exit(1);
    }
  }
  
  rval.type = "file";
  rval.val = fopen((char *)args[0].val, (char *)args[1].val);
  if(!rval.val) {
    var_lset(vars, "__io_errno", "int", ptr_dupint(errno));
    var_lset(vars, "__io_errstr", "str", (void *)strerror(errno));
  }

  return rval;
}

