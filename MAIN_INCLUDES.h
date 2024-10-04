#ifndef MAIN_INCLUDES_H
#define MAIN_INCLUDES_H

//#include <FileCtrl.hpp>

#define MAX_STR_NUM		3000
#define STRADR			0x20000

#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>

enum TextFileTypes{
    Report_type,
    Capture_type,
    log_file_type
};

/*#include <windows.h>
#include <sys\stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <ctype.h>
#include <mbstring.h>
#include <string.h>
#include <errno.h>
#include <mmsystem.h>
#include <map.h>
#include <vcl.h>
#include <stdarg.h>*/
/*
#include "Setup_Page.h"
#include "Monitor_Page.h"
#include "LinesInMemory.h"
#include "BaseDbgClass.h"
#include "Dbg_class.h"
#include "MainForm.h"
#include "Debug_Page.h"
#include "MyThread.h"
#include "MapFileSv.h"
#include "WorkingStrings.h"
#include "ReportMessages.h"*/
#include "Messages.h"









#define EMPTY_STRING 	" "
#define ONE_SPACE 		" "
#define THREE_SPACES 	"   "
#define PERCENT_CHAR 	"%"
#define DBL_SLASH_CHAR	"  //"\

#define gridView 	1
#define textView	2

#define getShortName	1
#define getFullName		2
#define getIndex		3

#define GET_ADDR		1
#define GET_DATA		2
#define GET_COMMENT		3





#endif // MAIN_INCLUDES_H
