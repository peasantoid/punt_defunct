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
#include "pointer.h"
#include "value.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * run the contents of an s-expression
 *
 * returning <offset> by reference so run_tokens() doesn't iterate over
 * something we've already executed
 */
p_val run_sexp(p_val *tokens, p_var **vars, int *offset) {
  int i, level, literal;
  p_val *args = NULL, *block = NULL, func, rval; /* if not initialized, bad shiz happens */
  p_var var, *funcvars;
  p_val (*funcptr)(p_val *, p_var **);

  /* load our argument list with values */
  for(i = literal = 0; i < val_llen(tokens); i++) {
    if(!strcmp(tokens[i].type, "sexpr")) { break; }

    else if(!strcmp(tokens[i].type, "sexpl")) {
      rval = run_sexp(tokens + i + 1, vars, &i);
      val_lappend(&args, rval.type, rval.val);

    } else if(!strcmp(tokens[i].type, "literal")) {
      literal = i + 1;

    } else if(!strcmp(tokens[i].type, "symbol")) {
      if(literal) {
        val_lappend(&args, "symbol", tokens[i].val);
      } else {
        if(!var_lexists(*vars, tokens[i].val)) {
          fprintf(stderr, "%s: undefined symbol\n", (char *)tokens[i].val);
          exit(1);
        }
        var = var_lget(*vars, tokens[i].val);
        val_lappend(&args, var.type, var.val);
      }

    } else if(!strcmp(tokens[i].type, "blockl")) {
      block = NULL;
      level = 1;
      for(i++; i < val_llen(tokens); i++) {
        if(!strcmp(tokens[i].type, "blockl")) { level++; }
        else if(!strcmp(tokens[i].type, "blockr")) { level--; }
        if(!level) { break; }

        val_lappend(&block, tokens[i].type, tokens[i].val);
      }
      val_lappend(&args, "block", block);
      /* FIXME: potential memory leak here unless something frees <block> later */
    }

    else if(!strcmp(tokens[i].type, "str")) {
      val_lappend(&args, "str", tokens[i].val);
    }

    else if(!strcmp(tokens[i].type, "int")) {
      val_lappend(&args, "int", tokens[i].val);
    }

    else if(!strcmp(tokens[i].type, "float")) {
      val_lappend(&args, "float", tokens[i].val);
    }

    if(literal == i) { literal = 0; }
  }
  if(offset) { *offset += i + 1; }

  rval.type = "int";
  rval.val = ptr_dupint(0);

  /* empty expression, exit silently */
  if(!val_llen(args)) { return rval; }

  /* now execute stuff */
  func = *args;
  args++;
  
  if(!strcmp(func.type, "mfunc")) {
    funcptr = func.val;
    rval = (*funcptr)(args, vars);

  } else if(!strcmp(func.type, "block")) {
    funcvars = NULL;

    /* add some special variables */
    for(i = 0; i < val_llen(args); i++) {
      var_lset(&funcvars, vafmt("_%d", i + 1), args[i].type, args[i].val);
    }
    var_lset(&funcvars, "__argc", "int", ptr_dupint(val_llen(args)));
    var_lset(&funcvars, "__func", "block", func.val);

    /* pass down any functions defined in current scope */
    for(i = 0; i < var_llen(*vars); i++) {
      if(!strcmp((*vars)[i].type, "mfunc") ||
      !strcmp((*vars)[i].type, "block")) {
        var_lset(&funcvars, (*vars)[i].id, (*vars)[i].type, (*vars)[i].val);
      }
    }

    rval = run_tokens((p_val *)func.val, &funcvars);
    if(funcvars) { free(funcvars); }
  
  } else {
    fprintf(stderr, "type \"%s\" is not callable\n", func.type);
    exit(1);
  }

  return rval;
}

/* run a list of s-expressions */
p_val run_tokens(p_val *tokens, p_var **vars) {
  p_val rval = val_make();
  int i;

  for(i = 0; i < val_llen(tokens); i++) {
    if(!strcmp(tokens[i].type, "sexpl")) {
      rval = run_sexp(tokens + i + 1, vars, &i);
    }
  }

  return rval;
}

