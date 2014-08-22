#pragma once

#include <list>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <limits>

#include <QString>
#include "ErrorCodes.h"

#define BASIC256EPSILON 0.00000001

enum b_type {T_FLOAT, T_STRING, T_BOOL, T_ARRAY, T_STRARRAY, T_UNUSED, T_VARREF, T_VARREFSTR};
// stack types T_VARREF, T_VARREFSTR are to pass a variable reference to a subroutine or function (BYREF passing)

struct stackdata
{
  b_type type;
  QString string;
  double floatval; 
};

class Stack
{
 public:
  Stack();
  ~Stack();
  
  void pushstring(QString);
  void pushint(int);
  void pushfloat(double);
  void pushvarref(int);
  void pushvarrefstr(int);
  void swap();
  void swap2();
  void topto2();
  void dup();
  void dup2();
  int peekType();
  int popint();
  double popfloat();
  QString popstring();
  void clear();
  QString debug();
  int height();
  int compareTopTwo();
  int compareFloats(double, double);
  int error();
  void clearerror();
  void settypeconverror(int);
  void setdecimaldigits(int);

 private:
  std::list<stackdata*> stacklist;
  int errornumber;		// internal storage of last stack error
  int typeconverror;	// 0-return no errors on type conversion, 1-warn, 2-error
  int decimaldigits;	// display n decinal digits 12 default - 8 to 15 valid
  stackdata *popelement();
};
