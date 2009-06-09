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
 * tokenize a string/file for execution by the engine
 */

#include "common.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

p_tok *tokenize_str(char *str) {
  p_tok *tokens = (p_tok *)calloc(1, sizeof(p_tok));
  p_tok *_tokens; /* temporary storage for appending to <tokens> */
  p_tok token;
  int i;
  
  printf("%d\n", tok_llen(tokens));
  for(i = 0; i < strlen(str); i++) {
    token.type = "";
    token.val = NULL;
  }

  return tokens;
}

p_tok *tokenize_fp(FILE *fp) {
  p_tok *tokens;
  char *code, *read;
  int blocksize = 4096; /* hell, why not */
  
  code = "";
  while(1) {
    read = (char *)calloc(blocksize + 1, sizeof(char)); /* +1 for NUL byte */
    fgets(read, blocksize, fp); if(feof(fp)) { break; }
    asprintf(&code, "%s%s", code, read);
    free(read);
  }
  tokens = tokenize_str(code);
  free(code); /* don't want to leak that much memory */

  return tokens;
}

