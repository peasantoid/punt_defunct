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
 * miscellaneous utilities for token manipulation
 */

#include "common.h"
#include <stdio.h>

/* duplicate token list */
void tok_ldup(p_tok *src, p_tok *dest) {
  int i;
  for(i = 0; src[i].type != NULL; i++) {
    dest[i] = src[i];
  }
}

/* return length of token list */
int tok_llen(p_tok *tokens) {
  int i;
  for(i = 0; tokens[i].type != NULL; i++);
  return i;
}

