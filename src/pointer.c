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
 * pointer creation/manipulation
 */

#include "common.h"
#include "pointer.h"
#include <string.h>
#include <stdlib.h>

/* some functions for copying data */

void *ptr_dupstr(char *str) {
  char *dup = strdup(str);
  return (void *)dup;
}

void *ptr_dupint(long num) {
  /* TODO: find out why this is necessary */
  long *dup = (long *)calloc(1, sizeof(long));
  dup[0] = num;
  return (void *)dup;
}

/* FIXME: figure out why long doubles and/or strtold() don't work here (?) */
void *ptr_dupfloat(double num) {
  double *dup = (double *)calloc(1, sizeof(double));
  dup[0] = num;
  return (void *)dup;
}


void *ptr_dupval(p_val val) {
  p_val *dup = (p_val *)calloc(1, sizeof(p_val));
  dup[0] = val;
  return (void *)dup;
}

