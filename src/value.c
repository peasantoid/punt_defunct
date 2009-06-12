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
 * miscellaneous utilities for value sequence manipulation
 */

#include "common.h"
#include "value.h"
#include "pointer.h"
#include <stdio.h> /* Why is NULL in here? Sheesh. */
#include <stdlib.h>
#include <string.h>

/* generated initialized value */
p_val val_make() {
  p_val val;
    val.type = "int";
    val.val = ptr_dupint(0);
  return val;
}

/* is it true? */
int val_true(p_val val) {
  if(!strcmp(val.type, "str") && strlen((char *)val.val) > 0) { return 1; }
  else if(!strcmp(val.type, "int") && *(int *)val.val > 0) { return 1; }
  else if(!strcmp(val.type, "float") && *(double *)val.val > 0) { return 1; }
  else if(val.val) { return 1; }
  return 0;
}

/* return length of value list */
int val_llen(p_val *values) {
  int i;
  if(!values) { return 0; }
  for(i = 0; values[i].type != NULL; i++);
  return i;
}

/* duplicate value list */
void val_ldup(p_val *src, p_val *dest) {
  int i;
  for(i = 0; i < val_llen(src); i++) {
    dest[i] = src[i];
  }
}

/* add value to list */
void val_lappend(p_val **values, char *type, void *val) {
  p_val *_values; /* scratch space */
  int llen;
  
  if(*values) {
    llen = val_llen(*values);
    
    _values = (p_val *)calloc(llen + 1, sizeof(p_val));
    val_ldup(*values, _values);

    *values = (p_val *)calloc(llen + 2, sizeof(p_val)); /* new value + null terminator */
    val_ldup(_values, *values);
    free(_values);

    (*values)[llen].type = type;
    (*values)[llen].val = val;
  } else {
    /* if it's empty, un-emptify it */
    *values = (p_val *)calloc(2, sizeof(p_val));
    (*values)[0].type = type;
    (*values)[0].val = val;
  }
}

