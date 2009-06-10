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
  
}

