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
 * the actual punt runtime engine -- execute a token list
 */

#include "common.h"
#include "engine.h"
#include "variable.h"
#include "string.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <libgen.h>

/*
 * run the contents of an s-expression
 *
 * returning <offset> by reference so run_tokens() doesn't iterate over
 * something we've already executed
 */
p_val run_sexp(p_val *tokens, p_var **vars, int *offset) {
  int i, level;
  p_val *args = NULL, *block = NULL, func; /* if not initialized, bad shiz happens */
  p_var var;
  void *modptr = NULL, *(*funcnamesptr)();
  p_val (*funcptr)(p_val *, p_var **);
  char **funcnames, *modpath;

  /* load our argument list with values */
  for(i = 0; i < seq_llen(tokens); i++) {
    if(!strcmp(tokens[i].type, "sexpr")) { break; }

    else if(!strcmp(tokens[i].type, "sexpl")) {
/*      i++;
//      seq_lappend(&args, */
    }

    else if(!strcmp(tokens[i].type, "ident")) {
      if(!strcmp(tokens[i].val, "use")) {
        seq_lappend(&args, "builtin_use", NULL);
      } else {
        if(!var_lexists(*vars, tokens[i].val)) {
          fprintf(stderr, "%s: no such variable\n", tokens[i].val);
          exit(1);
        }
        var = var_lget(*vars, tokens[i].val);
        seq_lappend(&args, var.type, var.val);
      }

    } else if(!strcmp(tokens[i].type, "blockl")) {
      block = NULL;
      level = 1;
      for(i++; i < seq_llen(tokens); i++) {
        if(!strcmp(tokens[i].type, "blockl")) { level++; }
        else if(!strcmp(tokens[i].type, "blockr")) { level--; }
        if(level == 0) { break; }

        seq_lappend(&block, tokens[i].type, tokens[i].val);
      }
      seq_lappend(&args, "block", block);
      /* FIXME: potential for memory leak here unless something frees <block> later */
    }

    else if(!strcmp(tokens[i].type, "str")) {
      seq_lappend(&args, "str", ptr_dupstr(tokens[i].val));
    }

    else if(!strcmp(tokens[i].type, "int")) {
      seq_lappend(&args, "int", ptr_dupint(*(int *)tokens[i].val));
    }

    else if(!strcmp(tokens[i].type, "float")) {
      seq_lappend(&args, "float", ptr_dupfloat(*(double *)tokens[i].val));
    }
  }
  *offset += i;

  /* empty expression, die silently */
  if(!seq_llen(args)) { return; }

  /* now execute stuff */
  func = *args;
  args++;
  
  /* only built-in function -- load a module */
  if(!strcmp(func.type, "builtin_use")) {
    for(i = 0; i < seq_llen(args); i++) {
      if(strcmp(args[i].type, "str")) {
        fprintf(stderr, "use: all arguments must be strings\n");
        exit(1);
      }

      /* load the module */
      /* TODO: stick this in a separate source file */
      modpath = vafmt("%s/%s.so", MODULE_DIR, basename((char *)args[i].val));
      modptr = dlopen(modpath, RTLD_LAZY);
      if(!modptr) {
        fprintf(stderr, "use: %s\n", dlerror());
        exit(1);
      }
      funcnamesptr = dlsym(modptr, "__list_funcs");
      if(!funcnamesptr) {
        fprintf(stderr, "use: module \"%s\" does not define \"__list_funcs\"\n", modpath);
        exit(1);
      }
      funcnames = (*funcnamesptr)();
      while(*funcnames) {
        funcptr = dlsym(modptr, *funcnames);
        if(!funcptr) {
          fprintf(stderr, "use: module \"%s\" reports function \"%s\" but does not define it\n", modpath, *funcnames);
          exit(1);
        }
        var_lset(vars, *funcnames, "mfunc", funcptr);
        funcnames++;
      }
      free(modpath);
//      dlclose(modptr); /* if <modptr> is closed, the function pointers are lost */
    }
  } else {
    fprintf(stderr, "type \"%s\" is not callable\n", func.type);
    exit(1);
  }
}

/* run a list of s-expressions */
void run_tokens(p_val *tokens, p_var **vars) {
  int i;
  for(i = 0; i < seq_llen(tokens); i++) {
    if(!strcmp(tokens[i].type, "sexpl")) {
      run_sexp(tokens + i + 1, vars, &i);
    }
  }
}

