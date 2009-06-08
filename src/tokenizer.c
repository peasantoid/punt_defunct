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
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tok **tokenize_str(char *str) {
  tok **tokens = (tok **)calloc(1, sizeof(tok *));
    tokens[0] = NULL;
  tok **_tokens; /* temporary storage for appending to <tokens> */
  tok *token = (tok *)calloc(1, sizeof(tok));
  int i;
  
  for(i = 0; i < strlen(str); i++) {
    printf("%c", str[i]);
    token->type = "";
    token->val = NULL;
  }

  return tokens;
}

tok **tokenize_fp(FILE *fp) {
  tok **tokens;
  char *code;
  int c;
  
  code = "";
  while(1) {
    c = fgetc(fp);
    if(c == EOF) { break; }
    asprintf(&code, "%s%c", code, c);
  }
  tokens = tokenize_str(code);
  free(code); /* don't want to leak that much memory */

  return tokens;
}

