/** Copyright (C) 2006, Ian Paul Larsen.
 **
 **  This program is free software; you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation; either version 2 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License along
 **  with this program; if not, write to the Free Software Foundation, Inc.,
 **  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **/

// BE SURE TO ADD NEW OP TO ENUM

// ALSO ADD to the optype, opname, and opxname functions in interperter.c

#define OPTYPE_NONE		0		// simple opcode with no inline data
#define OPTYPE_INT		1		// a trailing integer
#define OPTYPE_INTINT	2		// two trailing integers
#define OPTYPE_FLOAT	3		// decimal number following
#define OPTYPE_STRING	4		// null terminated string following
#define OPTYPE_EXTENDED	5		// extended opcode follows
#define OPTYPE_LABEL	6		// label number (int) - converted to address at runtime
#define OPTYPE_VARIABLE	7		// variable number (int)



enum {
	OP_END,
	OP_NOP,
	OP_RETURN,
	OP_CONCAT,
	OP_EQUAL,
	OP_NEQUAL,
	OP_GT,
	OP_LT,
	OP_GTE,
	OP_LTE,
	OP_AND,
	OP_NOT,
	OP_OR,
	OP_XOR,
	OP_INT,
	OP_STRING,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_EX,
	OP_NEGATE,
	OP_PRINT,
	OP_PRINTN,
	OP_INPUT,
	OP_KEY,
	OP_PLOT,
	OP_RECT,
	OP_CIRCLE,
	OP_LINE,
	OP_REFRESH,
	OP_FASTGRAPHICS,
	OP_CLS,
	OP_CLG,
	OP_GRAPHSIZE,
	OP_GRAPHWIDTH,
	OP_GRAPHHEIGHT,
	OP_SIN,
	OP_COS,
	OP_TAN,
	OP_RAND,
	OP_CEIL,
	OP_FLOOR,
	OP_ABS,
	OP_PAUSE,
	OP_POLY,
	OP_LENGTH,
	OP_MID,
	OP_INSTR,
	OP_INSTR_S,
	OP_INSTR_SC,
	OP_INSTRX,
	OP_INSTRX_S,
	OP_OPEN,
	OP_READ,
	OP_WRITE,
	OP_CLOSE,
	OP_RESET,
	OP_SOUND,
	OP_INCREASERECURSE,
	OP_DECREASERECURSE,
	OP_ASC,
	OP_CHR,
	OP_FLOAT,
	OP_READLINE,
	OP_EOF,
	OP_MOD,
	OP_YEAR,
	OP_MONTH,
	OP_DAY,
	OP_HOUR,
	OP_MINUTE,
	OP_SECOND,
	OP_MOUSEX,
	OP_MOUSEY,
	OP_MOUSEB,
	OP_CLICKCLEAR,
	OP_CLICKX,
	OP_CLICKY,
	OP_CLICKB,
	OP_TEXT,
	OP_FONT,
	OP_SAY,
	OP_WAVPLAY,
	OP_WAVSTOP,
	OP_SEEK,
	OP_SIZE,
	OP_EXISTS,
	OP_LEFT,
	OP_RIGHT,
	OP_UPPER,
	OP_LOWER,
	OP_SYSTEM,
	OP_VOLUME,
	OP_SETCOLOR,
	OP_RGB,
	OP_PIXEL,
	OP_GETCOLOR,
	OP_ASIN,
	OP_ACOS,
	OP_ATAN,
	OP_DEGREES,
	OP_RADIANS,
	OP_INTDIV,
	OP_LOG,
	OP_LOGTEN,
	OP_GETSLICE,
	OP_PUTSLICE,
	OP_PUTSLICEMASK,
	OP_IMGLOAD,
	OP_SQR,
	OP_EXP,
	OP_ARGUMENTCOUNTTEST,
	OP_THROWERROR,
	OP_READBYTE,
	OP_WRITEBYTE,
	OP_STACKSWAP,
	OP_STACKTOPTO2,
	OP_STACKDUP,
	OP_STACKDUP2,
	OP_STACKSWAP2,
	OP_GOTO,
	OP_GOSUB,
	OP_BRANCH,
	OP_NUMASSIGN,
	OP_STRINGASSIGN,
	OP_ARRAYASSIGN,
	OP_STRARRAYASSIGN,
	OP_PUSHVAR,
	OP_PUSHINT,
	OP_DEREF,
	OP_FOR,
	OP_NEXT,
	OP_CURRLINE,
	OP_DIM,
	OP_DIMSTR,
	OP_ONERROR,
	OP_EXPLODESTR,
	OP_EXPLODESTR_C,
	OP_EXPLODE,
	OP_EXPLODE_C,
	OP_EXPLODEXSTR,
	OP_EXPLODEX,
	OP_IMPLODE,
	OP_GLOBAL,
	OP_STAMP,
	OP_STAMP_LIST,
	OP_STAMP_S_LIST,
	OP_STAMP_SR_LIST,
	OP_POLY_LIST,
	OP_WRITELINE,
	OP_ARRAYASSIGN2D,
	OP_STRARRAYASSIGN2D,
	OP_SOUND_ARRAY,
	OP_SOUND_LIST,
	OP_DEREF2D,
	OP_REDIM,
	OP_REDIMSTR,
	OP_REDIM2D,
	OP_REDIMSTR2D,
	OP_ALEN,
	OP_ALENX,
	OP_ALENY,
	OP_PUSHVARREF,
	OP_PUSHVARREFSTR,
	OP_VARREFASSIGN,
	OP_VARREFSTRASSIGN,
	OP_FUNCRETURN,
	OP_ARRAYLISTASSIGN,
	OP_STRARRAYLISTASSIGN,
	OP_PUSHFLOAT,
	OP_PUSHSTRING,
	OP_INCLUDEFILE,
	OP_SPRITEPOLY,
	OP_SPRITEPOLY_LIST,
	OP_EXTENDEDNONE,

};

// extended opcodes (second byte) - NO ARGMENTS
// - do not need to define a type for them
enum {
	OPX_SPRITEDIM,
	OPX_SPRITELOAD,
	OPX_SPRITESLICE,
	OPX_SPRITEMOVE,
	OPX_SPRITEHIDE,
	OPX_SPRITESHOW,
	OPX_SPRITECOLLIDE,
	OPX_SPRITEPLACE,
	OPX_SPRITEX,
	OPX_SPRITEY,
	OPX_SPRITEH,
	OPX_SPRITEW,
	OPX_SPRITEV,
	OPX_CHANGEDIR,
	OPX_CURRENTDIR,
	OPX_WAVWAIT,
	OPX_DBOPEN,
	OPX_DBCLOSE,
	OPX_DBEXECUTE,
	OPX_DBOPENSET,
	OPX_DBCLOSESET,
	OPX_DBROW,
	OPX_DBINT,
	OPX_DBFLOAT,
	OPX_DBSTRING,
	OPX_LASTERROR,
	OPX_LASTERRORLINE,
	OPX_LASTERRORMESSAGE,
	OPX_LASTERROREXTRA,
	OPX_OFFERROR,
	OPX_NETLISTEN,
	OPX_NETCONNECT,
	OPX_NETREAD,
	OPX_NETWRITE,
	OPX_NETCLOSE,
	OPX_NETDATA,
	OPX_NETADDRESS,
	OPX_KILL,
	OPX_MD5,
	OPX_SETSETTING,
	OPX_GETSETTING,
	OPX_PORTIN,
	OPX_PORTOUT,
	OPX_BINARYOR,
	OPX_BINARYAND,
	OPX_BINARYNOT,
	OPX_IMGSAVE,
	OPX_DIR,
	OPX_REPLACE,
	OPX_REPLACE_C,
	OPX_REPLACEX,
	OPX_COUNT,
	OPX_COUNT_C,
	OPX_COUNTX,
	OPX_OSTYPE,
	OPX_MSEC,
	OPX_EDITVISIBLE,
	OPX_GRAPHVISIBLE,
	OPX_OUTPUTVISIBLE,
	OPX_TEXTWIDTH,
	OPX_SPRITER,
	OPX_SPRITES,
	OPX_FREEFILE,
	OPX_FREENET,
	OPX_FREEDB,
	OPX_FREEDBSET,
	OPX_DBINTS,
	OPX_DBFLOATS,
	OPX_DBSTRINGS,
	OPX_DBNULL,
	OPX_DBNULLS,
	OPX_ARC,
	OPX_CHORD,
	OPX_PIE,
	OPX_PENWIDTH,
	OPX_GETPENWIDTH,
	OPX_GETBRUSHCOLOR,
	OPX_RUNTIMEWARNING,
	OPX_ALERT,
	OPX_CONFIRM,
	OPX_PROMPT,
	OPX_FROMRADIX,
	OPX_TORADIX,
	OPX_DEBUGINFO
};






