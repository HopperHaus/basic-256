// Constants.h - Constants used throughout the code

#ifndef M_PI
    #define M_PI 3.14159265
#endif


#ifndef CONSTANTS
	#define CONSTANTS "CONSTANTS"

	// EPSILON represents how far off float comparison may be to be the same
    #define EPSILON 0.00000001

    // returned in bytecode is this a function or a subroutine
    #define CALLSIG_SUBROUTINE 0xffff
    #define CALLSIG_FUNCTION 0xfffe

	// editor settings
	#define EDITOR_TAB_WIDTH 4
	
	// mainwindow geometry settings/defaults
	#define MAINWINDOW_DEFAULT_X 100
	#define MAINWINDOW_DEFAULT_Y 100
	#define MAINWINDOW_DEFAULT_W 800
	#define MAINWINDOW_DEFAULT_H 600
	#define GRAPH_DOCK_DEFAULT_X 100
	#define GRAPH_DOCK_DEFAULT_Y 100
	#define GRAPH_DOCK_DEFAULT_W 400
	#define GRAPH_DOCK_DEFAULT_H 400
	#define OUT_DOCK_DEFAULT_X 100
	#define OUT_DOCK_DEFAULT_Y 100
	#define OUT_DOCK_DEFAULT_W 400
	#define OUT_DOCK_DEFAULT_H 400
	#define VAR_DOCK_DEFAULT_X 100
	#define VAR_DOCK_DEFAULT_Y 100
	#define VAR_DOCK_DEFAULT_W 400
	#define VAR_DOCK_DEFAULT_H 400

	// time between sleep interrupt checks
	#define SLEEP_GRANULE 500L

	// command line states that define how the GUI is laid-out and reacts
	#define GUISTATENORMAL 0
	#define GUISTATERUN 1
	#define GUISTATEAPP 2

	// states of a program
	#define RUNSTATESTOP 0
	#define RUNSTATERUN 1
	#define RUNSTATEDEBUG 2
	#define RUNSTATESTOPING 3
	#define RUNSTATERUNDEBUG 4

	// imagesave valid image types
	#define IMAGETYPE_BMP "BMP"
	#define IMAGETYPE_JPG "JPG"
	#define IMAGETYPE_JPEG "JPEG"
	#define IMAGETYPE_PNG "PNG"
	
	// mouse button value (clickb, mouseb)
	#define MOUSEBUTTON_CENTER 4
	#define MOUSEBUTTON_LEFT 1
	#define MOUSEBUTTON_NONE 0
	#define MOUSEBUTTON_RIGHT 2
    #define MOUSEBUTTON_DOUBLECLICK 32
    	
	// ostypes returned by ostype function
	#define OSTYPE_ANDROID 3
	#define OSTYPE_LINUX 1
	#define OSTYPE_MACINTOSH 2
	#define OSTYPE_WINDOWS 0
	
	// GetSlice Layers
	#define SLICE_ALL 0
	#define SLICE_PAINT 1
	#define SLICE_SPRITE 2
	
	// Transparency Color used in Interperter
	#define COLOR_CLEAR 0
	
	// Constants used in seralize and unserialize
	#define SERALIZE_DELIMITER ':'
	#define SERALIZE_INT '1'
	#define SERALIZE_FLOAT '2'
	#define SERALIZE_STRING '3'
	#define SERALIZE_UNASSIGNED '0'

#endif
