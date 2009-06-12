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

double do_op(double op1, double op2, char op) {
  double result = op1;
  switch(op) {
    case '+':
      result += op2;
      break;
    case '-':
      result -= op2;
      break;
    case '*':
      result *= op2;
      break;
    case '/':
      if(op2 == 0) {
        fprintf(stderr, "div: division by zero\n");
        return 0;
      }
      result /= op2;
      break;
    case '%':
      if(op2 == 0) {
        fprintf(stderr, "mod: modulus by zero\n");
        return 0;
      }
      result = fmod(result, op2);
      break;
    case '^':
      result = pow(result, op2);
      break;
  }
  return result;
}

/* minlen: negative to use == instead of >= */
void checktypes(p_val *args, int minlen, char *func) {
  int i;

  if(val_llen(args) < minlen) {
    fprintf(stderr, "%s: at least 1 argument required\n", func);
    exit(1);
  } else if(minlen < 0 && val_llen(args) != abs(minlen)) {
    fprintf(stderr, "%s: %d %s required\n", func, abs(minlen),
      abs(minlen) == 1 ? "argument" : "arguments");
    exit(1);
  }

  for(i = 0; i < val_llen(args); i++) {
    if(strcmp(args[i].type, "int") &&
    strcmp(args[i].type, "float")) {
      fprintf(stderr, "%s: only numeric types are accepted\n", func);
      exit(1);
    }
  }
}

double getval(p_val arg) {
  double result = 0;
  if(!strcmp(arg.type, "int")) {
    result = (double)*(long *)arg.val;
  } else if(!strcmp(arg.type, "float")) {
    result = *(double *)arg.val;
  }
  return result;
}

void intify(p_val *arg) {
  if((long)*(double *)(*(p_val *)arg).val ==
  *(double *)(*(p_val *)arg).val) {
    arg->type = "int";
    arg->val = ptr_dupint((long)*(double *)(*(p_val *)arg).val);
  }
}

p_val do_arithmetic(p_val *args, char *func, char op) {
  p_val rval = val_make();
  rval.type = "float";
  checktypes(args, 1, func);
  rval.val = ptr_dupfloat(getval(args[0]));
  int i;

  for(i = 1; i < val_llen(args); i++) {
    *(double *)rval.val = do_op(getval(rval), getval(args[i]), op);
  }
  intify(&rval);

  return rval;
}

//p_val

