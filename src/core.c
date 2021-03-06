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
 * where everything gets glued together
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "common.h"
#include "tokenizer.h"
#include "engine.h"
#include "module.h"
#include "variable.h"

int main(int argc, char **argv) {
  int i;
  FILE *fp;
  p_val rval, *tokens = (p_val *)calloc(1, sizeof(p_val));
  p_var *vars = (p_var *)calloc(1, sizeof(p_var));
    var_lset(&vars, "use", "mfunc", &use_module);
  struct stat finfo;
  
  for(i = 1; i < argc; i++) {
    /* 
     * Code for detecting directories by vkumar:
     * http://punt.archuser.com/support/forum/open-bugs/fixed-todo-in-corecmain/#p1
     */
    if(lstat(argv[i], &finfo) == -1 || S_ISDIR(finfo.st_mode)) {
      if(S_ISDIR(finfo.st_mode)) {
        fprintf(stderr, "%s: Is a directory\n", argv[i]);
      } else {
        perror(argv[i]);
      }
      return 1;
    }
    fp = fopen(argv[i], "r"); /* should this be 'rb'? */
    tokens = tokenize_fp(fp);
    fclose(fp);
    rval = run_tokens(tokens, &vars);
    free(tokens);
  }

  return 0;
}

