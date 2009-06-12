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

#include "common.h"
#include "module.h"
#include "variable.h"
#include "value.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <libgen.h>

void load_module(char *path, p_var **vars) {
  char **funcnames;
  void *modptr = NULL, *(*funcnamesptr)() = NULL;
  p_val (*funcptr)(p_val *, p_var **);

  modptr = dlopen(path, RTLD_LAZY);
  if(!modptr) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  funcnamesptr = dlsym(modptr, "_punt_list_funcs");
  if(!funcnamesptr) {
    fprintf(stderr, "module \"%s\" does not define \"_punt_list_funcs\"\n", path);
    exit(1);
  }

  funcnames = (*funcnamesptr)();
  while(*funcnames) {
    funcptr = dlsym(modptr, vafmt("punt_%s", *funcnames));
    if(!funcptr) {
      fprintf(stderr, "module \"%s\" reports function \"%s\" but does not define it (should be defined as \"%s\")\n", path, *funcnames, vafmt("punt_%s", *funcnames));
      exit(1);
    }
    var_lset(vars, *funcnames, "mfunc", funcptr);
    funcnames++;
  }
//  dlclose(modptr); /* if <modptr> is closed, the function pointers are lost */
}

void use_module(p_val *args, p_var **vars) {
  int i;
  char *path;

  for(i = 0; i < val_llen(args); i++) {
    if(strcmp(args[i].type, "str")) {
      fprintf(stderr, "use: all arguments must be strings\n");
      exit(1);
    }

    path = vafmt("%s/%s.so", MODULE_DIR, basename((char *)args[i].val));
    load_module(path, vars);
    free(path);
  }
}

