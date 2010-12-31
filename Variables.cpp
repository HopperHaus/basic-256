#include <map>
#include "Variables.h"
#include <string>

// manage storage of variables

// variables are limited to the following types:
// T_UNUSED, T_FLOAT, T_STRING, T_ARRAY, and T_STRARRAY

Variables::Variables()
{
	lasterror = ERROR_NONE;
	// initialize variable storage
}

Variables::~Variables()
{
	lasterror = ERROR_NONE;
	// free variables and all storage
	clear();
}

int Variables::error() {
	return(lasterror);
}

void
Variables::clear()
{
	lasterror = ERROR_NONE;
	// erase all variables
	while(!varmap.empty()) {
		std::map<int, variable*>::iterator i=varmap.begin();
		clearvariable((*i).second);
		varmap.erase((*i).first);
	}
}


void Variables::clearvariable(variable* v)
{
	// free a variable's current value to allow it to be reassigned
	if (v->type == T_UNUSED) {
	} else if (v->type == T_STRING && v->value.string != NULL) {
		free(v->value.string);
		v->value.string = NULL;
	}
	else if (v->type == T_ARRAY && v->value.arr != NULL) {
		delete(v->value.arr->data.fdata);
		delete(v->value.arr);
		v->value.arr = NULL;
	}
	else if (v->type == T_STRARRAY && v->value.arr != NULL)	{
		for (int j = 0; j < v->value.arr->size; j++) {
			if (v->value.arr->data.sdata[j]) {
				free(v->value.arr->data.sdata[j]);
				v->value.arr->data.sdata[j] = NULL;
			}
		}
		delete(v->value.arr->data.sdata);
		delete(v->value.arr);
		v->value.arr = NULL;
	}
}

variable* Variables::getvfromnum(int varnum, bool makenew) {
	// get v from map else return NULL
	// if makenew then make a new one if not exist
	variable *v;
	std::map<int, variable*>::iterator i = varmap.find(varnum);
	if(i==varmap.end()) {
		if(makenew) {
			v = new variable;
			v->type = T_UNUSED;
			v->value.floatval = 0;
			v->value.string = NULL;
			v->value.arr = NULL;
			varmap.insert( std::pair<int, variable*> (varnum, v) );
			//printf("lastvar=%i size=%i\n", varnum, varmap.size());
		} else {
			v = NULL;
		}
	} else {
		v = (*i).second;
	}
	return(v);
}


int Variables::type(int varnum)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		return(v->type);
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(T_UNUSED);
}


void Variables::setfloat(int varnum, double value)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,true);
	clearvariable(v);
	v->type = T_FLOAT;
	v->value.floatval = value;
}

double Variables::getfloat(int varnum)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_FLOAT) {
			return(v->value.floatval);
		} else {
			lasterror = ERROR_NOSUCHVARIABLE;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(0);
}

void Variables::setstring(int varnum, char *value)
{
	// pass pointer - copied when put on stack so this is a good pointer
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,true);
	clearvariable(v);
	v->type = T_STRING;
	v->value.string = value;
}

char *Variables::getstring(int varnum)
{
	// just return pointer - copied when put on stack so this is a good pointer
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_STRING) {
			return(v->value.string);
		} else {
			lasterror = ERROR_NOSUCHVARIABLE;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(NULL);
}

void Variables::arraydimfloat(int varnum, int xdim, int ydim, bool redim)
{
	variable *v = getvfromnum(varnum,true);
	lasterror = ERROR_NONE;

	// max number of elements to save on a redim
	int redimsize = 0;
	if(redim && v->type==T_ARRAY) {
		redimsize = v->value.arr->size;	
	}
	
	int size = xdim * ydim;
	if (size <= VARIABLE_MAXARRAYELEMENTS) {
		if (size >= 1) {
			array *a = new array;
			double *d = new double[size];
			for (int j = 0; j < size; j++) {
				if(j < redimsize) {
					d[j] = v->value.arr->data.fdata[j];						
				} else {
					d[j] = 0;
				}
			}

			clearvariable(v);

			v->type = T_ARRAY;
			a->data.fdata = d;
			a->size = size;
			a->xdim = xdim;
			a->ydim = ydim;
			v->value.arr = a;
		} else {
			lasterror = ERROR_ARRAYSIZESMALL;
		}
	} else {
		lasterror = ERROR_ARRAYSIZELARGE;
	}
}

void Variables::arraydimstring(int varnum, int xdim, int ydim, bool redim)
{
	variable *v = getvfromnum(varnum,true);
	lasterror = ERROR_NONE;

	// max number of elements to save on a redim
	int redimsize = 0;
	if(redim && v->type==T_STRARRAY) {
		redimsize = v->value.arr->size;	
	}
	
	int size = xdim * ydim;
	if (size <= VARIABLE_MAXARRAYELEMENTS) {
		if (size >= 1) {
			array *a = new array;
			char **c = new char*[size];
			for (int j = 0; j < size; j++) {
				if(j < redimsize) {
					c[j] = v->value.arr->data.sdata[j];						
					v->value.arr->data.sdata[j]=NULL;	// so not free-d with moved to new array
				} else {
					c[j] = strdup("");
				}
			}

			clearvariable(v);

			v->type = T_STRARRAY;
			a->data.sdata = c;
			a->size = size;
			a->xdim = xdim;
			a->ydim = ydim;
			v->value.arr = a;
		} else {
			lasterror = ERROR_ARRAYSIZESMALL;
		}
	} else {
		lasterror = ERROR_ARRAYSIZELARGE;
	}
}

int Variables::arraysize(int varnum)
{
	// return length of array as if it was a one dimensional array - 0 = not an array		
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY || v->type == T_STRARRAY)
		{
			return(v->value.arr->size);
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(0);
}

int Variables::arraysizex(int varnum)
{
	// return number of columns of array as if it was a two dimensional array - 0 = not an array		
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY || v->type == T_STRARRAY)
		{
			return(v->value.arr->xdim);
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(0);
}

int Variables::arraysizey(int varnum)
{
	// return number of rows of array as if it was a two dimensional array - 0 = not an array		
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY || v->type == T_STRARRAY)
		{
			return(v->value.arr->ydim);
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(0);
}

void Variables::arraysetfloat(int varnum, int index, double value)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY) {
			if(index >= 0 && index < v->value.arr->size) {
				v->value.arr->data.fdata[index] = value;
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
}

void Variables::array2dsetfloat(int varnum, int x, int y, double value)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY) {
			if(x >= 0 && x < v->value.arr->xdim && y >= 0 && y < v->value.arr->ydim ) {
				v->value.arr->data.fdata[x * v->value.arr->ydim + y] = value;
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
}

double Variables::arraygetfloat(int varnum, int index)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY) {
			if(index >= 0 && index < v->value.arr->size) {
				return(v->value.arr->data.fdata[index]);
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(0);
}

double Variables::array2dgetfloat(int varnum, int x, int y)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_ARRAY) {
			if(x >= 0 && x < v->value.arr->xdim && y >= 0 && y < v->value.arr->ydim ) {
				return(v->value.arr->data.fdata[x * v->value.arr->ydim + y]);
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(0);
}

void Variables::arraysetstring(int varnum, int index, char *value)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_STRARRAY) {
			if(index >= 0 && index < v->value.arr->size) {
				if (v->value.arr->data.sdata[index])
				{
					free(v->value.arr->data.sdata[index]);
				}
				v->value.arr->data.sdata[index] = value;
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTSTRINGARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
}

void Variables::array2dsetstring(int varnum, int x, int y, char *value)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_STRARRAY) {
			if(x >= 0 && x < v->value.arr->xdim && y >= 0 && y < v->value.arr->ydim ) {
				int index = x * v->value.arr->ydim + y;
				if (v->value.arr->data.sdata[index])
				{
					free(v->value.arr->data.sdata[index]);
				}
				v->value.arr->data.sdata[index] = value;
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTSTRINGARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
}

char *Variables::arraygetstring(int varnum, int index)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_STRARRAY) {
			if(index >= 0 && index < v->value.arr->size) {
				return(v->value.arr->data.sdata[index]);
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTSTRINGARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(NULL);
}

char *Variables::array2dgetstring(int varnum, int x, int y)
{
	lasterror = ERROR_NONE;
	variable *v = getvfromnum(varnum,false);
	if(v) {
		if (v->type == T_STRARRAY) {
			if(x >= 0 && x < v->value.arr->xdim && y >= 0 && y < v->value.arr->ydim ) {
				int index = x * v->value.arr->ydim + y;
				return(v->value.arr->data.sdata[index]);
			} else {
				lasterror = ERROR_ARRAYINDEX;
			}
		} else {
			lasterror = ERROR_NOTSTRINGARRAY;
		}
	} else {
		lasterror = ERROR_NOSUCHVARIABLE;
	}
	return(NULL);
}


