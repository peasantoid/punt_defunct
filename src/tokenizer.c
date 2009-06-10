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
#include "sequence.h"
#include "pointer.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sfind(char *str, char c) {
  int i;
  for(i = 0; i < strlen(str); i++) {
    if(str[i] == c) { return i; }
  }
  return -1;
}

p_val *tokenize_str(char *str) {
  p_val *tokens = NULL;
  int i, n, bsc, start;
  char *strv, *strv2;
  
  for(i = 0; i < strlen(str); i++) {
    switch(str[i]) {
      case '#':
        for(; str[i] != '\n'; i++);
        break;
      case '(':
        seq_lappend(&tokens, "sexpl", NULL);
        break;
      case ')':
        seq_lappend(&tokens, "sexpr", NULL);
        break;
      case '[':
        seq_lappend(&tokens, "blockl", NULL);
        break;
      case ']':
        seq_lappend(&tokens, "blockr", NULL);
        break;
      case '\'':
          strv = (char *)calloc(1, sizeof(char));
          bsc = 0;
          /*
           * bsc: backslash count
           * if even, quote has not been escaped
           * if odd, quote has been escaped
           */

          for(i++; i < strlen(str); i++) {
            if(str[i] == '\'' && bsc % 2 == 0) { break; }
            else if(str[i] == '\\') {
              asprintf(&strv, "%s\\", strv);
              bsc ++;
            } else {
              asprintf(&strv, "%s%c", strv, str[i]);
              bsc = 0;
            }
          }
          
          /* remove leftover backslashes */
          strv = str_replace(strv, "\\\\", "\\", 0);
          strv = str_replace(strv, "\\'", "'", 0);

          seq_lappend(&tokens, "str", ptr_dupstr(strv));
          free(strv);
          break;
      default:
        /* it seems to be a number */
        if(isdigit(str[i]) || strchr("-.", str[i])) {
          strv = (char *)calloc(2, sizeof(char));
          strv[0] = str[i];

          for(i++; isdigit(str[i]) || str[i] == '.'; i++) {
            asprintf(&strv, "%s%c", strv, str[i]);
          }
          i--; /* might've overrun something important */

          /* it's a float */
          if(strchr(strv, '.')) {
            seq_lappend(&tokens, "float", ptr_dupfloat(strtod(strv, NULL)));
          /* it's an int */
          } else {
            seq_lappend(&tokens, "int", ptr_dupint(strtol(strv, NULL, 10)));
          }
          free(strv);
        } else if(isalnum(str[i]) || str[i] == '_') {
          strv = (char *)calloc(2, sizeof(char));
          strv[0] = str[i];

          for(i++; isalnum(str[i]) || str[i] == '_'; i++) {
            asprintf(&strv, "%s%c", strv, str[i]);
          }
          i--;

          seq_lappend(&tokens, "ident", ptr_dupstr(strv));
          free(strv);
        }
        break;
    }
  }

  return tokens;
}

p_val *tokenize_fp(FILE *fp) {
  p_val *tokens;
  char *code, *read;
  int blocksize = 4096; /* hell, why not */
  
  code = (char *)calloc(1, sizeof(char));
  while(1) {
    read = (char *)calloc(blocksize + 1, sizeof(char)); /* +1 for nul */
    fgets(read, blocksize, fp); if(feof(fp)) { break; }
    asprintf(&code, "%s%s", code, read);
    free(read);
  }
  tokens = tokenize_str(code);
  free(code); /* don't want to leak that much memory */

  return tokens;
}

