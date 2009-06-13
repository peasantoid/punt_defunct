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
 * math functions
 */

#include "common.h"

char **_punt_list_funcs() {
  char **funcs = (char **)calloc(19, sizeof(char *));

  funcs[0] = "add";
  funcs[1] = "sub";
  funcs[2] = "mul";
  funcs[3] = "div";
  funcs[4] = "mod";
  funcs[5] = "pow";

  funcs[6] = "cos";
  funcs[7] = "sin";
  funcs[8] = "tan";
  funcs[9] = "acos";
  funcs[10] = "asin";
  funcs[11] = "atan";

  funcs[12] = "cosh";
  funcs[13] = "sinh";
  funcs[14] = "tanh";

  funcs[15] = "ceil";
  funcs[17] = "floor";
  funcs[16] = "abs";

  return funcs;
}

p_val punt_add(p_val *args, p_var **vars) { 
  return do_arithmetic(args, "add", '+');
}

p_val punt_sub(p_val *args, p_var **vars) {
  return do_arithmetic(args, "sub", '-');
}

p_val punt_mul(p_val *args, p_var **vars) {
  return do_arithmetic(args, "mul", '*');
}

p_val punt_div(p_val *args, p_var **vars) {
  return do_arithmetic(args, "div", '/');
}

p_val punt_mod(p_val *args, p_var **vars) {
  return do_arithmetic(args, "mod", '%');
}

p_val punt_pow(p_val *args, p_var **vars) {
  return do_arithmetic(args, "pow", '^');
}

p_val punt_cos(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "cos");
  rval.val = ptr_dupfloat(cos(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_sin(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "sin");
  rval.val = ptr_dupfloat(sin(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_tan(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "tan");
  rval.val = ptr_dupfloat(tan(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_acos(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "acos");
  rval.val = ptr_dupfloat(acos(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_asin(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "asin");
  rval.val = ptr_dupfloat(asin(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_atan(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "atan");
  rval.val = ptr_dupfloat(atan(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_cosh(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "cosh");
  rval.val = ptr_dupfloat(cosh(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_sinh(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "sinh");
  rval.val = ptr_dupfloat(sinh(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_tanh(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "tanh");
  rval.val = ptr_dupfloat(tanh(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_ceil(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "ceil");
  rval.val = ptr_dupfloat(ceil(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_floor(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "floor");
  rval.val = ptr_dupfloat(floor(getval(args[0])));
  intify(&rval);

  return rval;
}

p_val punt_abs(p_val *args, p_var **vars) {
  p_val rval = val_make();
    rval.type = "float";

  checktypes(args, -1, "abs");
  rval.val = ptr_dupfloat(fabs(getval(args[0])));
  intify(&rval);

  return rval;
}

