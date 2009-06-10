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
#include "variable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int var_llen(p_var *vars) {
  int i;
  if(!vars) { return 0; }
  for(i = 0; vars[i].id != NULL; i++);
  return i;
}

void var_ldup(p_var *src, p_var *dest) {
  int i;
  for(i = 0; i < var_llen(src); i++) {
    dest[i] = src[i];
  }
}

int var_lexists(p_var *vars, char *id) {
  int i;
  for(i = 0; i < var_llen(vars); i++) {
    if(!strcmp(vars[i].id, id)) { return 1; }
  }
  return 0;
}

p_var var_lget(p_var *vars, char *id) {
  int i;
  p_var default_var;
  for(i = 0; i < var_llen(vars); i++) {
    if(!strcmp(vars[i].id, id)) { return vars[i]; }
  }
  return default_var;
}

void var_lset(p_var **vars, char *id, char *type, void *val) {
  p_var *_vars;
  int llen, i;

  if(var_llen(*vars) == 0) {
    *vars = (p_var *)calloc(2, sizeof(p_var));
    (*vars)[0].id = id;
    (*vars)[0].type = type;
    (*vars)[0].val = val;
    return;
  }

  if(var_lexists(*vars, id)) {
    for(i = 0; i < var_llen(*vars); i++) {
      if(!strcmp((*vars)[i].id, id)) {
        (*vars)[i].type = type;
        (*vars)[i].val = val;
        return;
      }
    }
  } else {
    llen = var_llen(*vars);
    
    _vars = (p_var *)calloc(llen + 1, sizeof(p_var));
    var_ldup(*vars, _vars);

    *vars = (p_var *)calloc(llen + 2, sizeof(p_var));
    var_ldup(_vars, *vars);
    free(_vars);

    (*vars)[llen].id = id;
    (*vars)[llen].type = type;
    (*vars)[llen].val = val;
  }
}

