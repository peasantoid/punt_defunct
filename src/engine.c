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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * run the contents of an s-expression
 *
 * returning <offset> by reference so run_tokens() doesn't iterate over
 * something we've already executed
 */
void run_sexp(p_val *tokens, p_var **vars, int *offset) {
  int i;
  p_val *args = NULL, *block = NULL; /* if not initialized, bad shiz happens */
  p_var var;

  /* load our argument list with values */
  for(i = 0; i < seq_llen(tokens); i++) {
    if(!strcmp(tokens[i].type, "sexpr")) { break; }

    else if(!strcmp(tokens[i].type, "ident")) {
      if(!var_lexists(*vars, tokens[i].val)) {
        fprintf(stderr, "%s: no such variable\n", tokens[i].val);
        exit(1);
      }
      var = var_lget(*vars, tokens[i].val);
      seq_lappend(&args, var.type, var.val);

    } else if(!strcmp(tokens[i].type, "blockl")) {
      block = NULL;
      for(i++; i < seq_llen(tokens) && strcmp(tokens[i].type, "blockr"); i++) {
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

  if(!seq_llen(args)) { return; }
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

