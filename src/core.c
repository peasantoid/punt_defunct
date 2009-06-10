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

int main(int argc, char **argv) {
  int i;
  FILE *fp;
  p_val *tokens = (p_val *)calloc(1, sizeof(p_val));
  p_var *vars = (p_var *)calloc(1, sizeof(p_var));
  
  for(i = 1; i < argc; i++) {
    fp = fopen(argv[i], "r");
    if(!fp) { /* FIXME: doesn't fail if you try to run a directory (!) */
      perror(argv[i]);
      return 1;
    }
    tokens = tokenize_fp(fp);
    fclose(fp);
    run_tokens(tokens, &vars);
  }

  return 0;
}

