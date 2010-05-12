######################################################################
# Automatically generated by qmake (2.00a) Fri Sep 15 19:35:58 2006
######################################################################

TEMPLATE		=	app
TARGET			=	BASIC256
DEPENDPATH		+=	.
INCLUDEPATH		+=	.
CONFIG          	+=  debug_and_release
OBJECTS_DIR		=	tmp/obj
MOC_DIR			=	tmp/moc
RESOURCES		+=	resources/resource.qrc
RC_FILE         =   resources/basic256.rc
TRANSLATIONS	=	Translations/basic256_en_US.ts \
		        	Translations/basic256_de.ts \
		        	Translations/basic256_ru_RU.ts \
		        	Translations/basic256_sp.ts \
		        	Translations/basic256_nl.ts

win32 {
	# use SAPI for speech
	DEFINES 		+= WIN32
	LIBS			+= -lole32 \
					-lsapi \
					-lwinmm 
					#Ian: removing this for visual studio build.  Mingw might need this back.
					#-lm
} else {
	## for the SAY command (LINUX) you need to choose one TTS engine - uncomment the one desired
	## espeak library (causes problems with sound statement in 0.9.5i under ubuntu 9.10 - suggest flite)
	## DEFINES		+= 	LINUX_ESPEAK
	## INCLUDEPATH		+=	/usr/include/espeak
	## LIBS			+=	-lespeak
	## flite library
	DEFINES			+= 	LINUX_FLITE
	INCLUDEPATH		+=	/usr/include/flite
	LIBS			+=	-lflite_cmu_us_kal16
	LIBS			+=	-lflite
	LIBS			+=	-lflite_cmulex
	LIBS			+=	-lflite_usenglish
	
	LIBS			+=	-lm

	## rules for make install
	examplesDiceFiles.files = ./Examples/dice/*
	examplesDiceFiles.path = /usr/share/basic256/Examples/dice
	INSTALLS += examplesDiceFiles
	examplesTestingFiles.files = ./Examples/testing/*
	examplesTestingFiles.path = /usr/share/basic256/Examples/testing
	INSTALLS += examplesTestingFiles
	examplesFiles.files = ./Examples/*
	examplesFiles.path = /usr/share/basic256/Examples
	INSTALLS += examplesFiles
	helpImgFiles.files = ../doc/help/images/*
	helpImgFiles.path = /usr/share/basic256/help/images
	INSTALLS += helpImgFiles
	helpFiles.files = ../doc/help/*
	helpFiles.path = /usr/share/basic256/help
	INSTALLS += helpFiles
	transFiles.files = ./Translations/*.qm
	transFiles.path = /usr/share/basic256
	INSTALLS += transFiles
	target.path = /usr/local/bin
	INSTALLS += target

}

exists( ./LEX/Makefile ) {
	message( Running make for ./LEX/Makefile )
	system( make -C ./LEX )
}
else { 
	error( Couldn't make LEX project - aborting... )
}


# Input
HEADERS 		+= 	LEX/basicParse.tab.h 
HEADERS 		+= 	BasicEdit.h 
HEADERS 		+= 	Interpreter.h 
HEADERS 		+= 	RunController.h 
HEADERS 		+= 	BasicOutput.h 
HEADERS 		+= 	BasicGraph.h 
HEADERS 		+= 	GhostButton.h 
HEADERS 		+= 	PauseButton.h 
HEADERS 		+= 	DockWidget.h
HEADERS			+=	BasicWidget.h
HEADERS			+=	ToolBar.h
HEADERS			+=	ViewWidgetIFace.h
HEADERS			+=	MainWindow.h
HEADERS			+=	VariableWin.h
HEADERS			+=	DocumentationWin.h
HEADERS			+=	Version.h
HEADERS			+=	EditSyntaxHighlighter.h
HEADERS         +=  Stack.h

SOURCES 		+= 	LEX/lex.yy.c 
SOURCES 		+= 	LEX/basicParse.tab.c 
SOURCES 		+= 	BasicEdit.cpp 
SOURCES 		+= 	Interpreter.cpp 
SOURCES 		+= 	RunController.cpp 
SOURCES 		+= 	Main.cpp 
SOURCES 		+= 	BasicOutput.cpp 
SOURCES 		+= 	BasicGraph.cpp 
SOURCES 		+= 	GhostButton.cpp 
SOURCES 		+= 	PauseButton.cpp 
SOURCES 		+= 	DockWidget.cpp
SOURCES			+=	BasicWidget.cpp
SOURCES			+=	ToolBar.cpp
SOURCES			+=	ViewWidgetIFace.cpp
SOURCES			+=	MainWindow.cpp
SOURCES			+=	VariableWin.cpp
SOURCES			+=	DocumentationWin.cpp
SOURCES			+=	EditSyntaxHighlighter.cpp
SOURCES			+=  Stack.cpp
