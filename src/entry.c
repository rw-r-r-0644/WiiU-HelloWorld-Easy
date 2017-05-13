#include <string.h>
#include <dynamic_libs/ax_functions.h>
#include <dynamic_libs/sys_functions.h>
#include <dynamic_libs/socket_functions.h>
#include <dynamic_libs/fs_functions.h>
#include <dynamic_libs/aoc_functions.h>
#include <dynamic_libs/syshid_functions.h>
#include <dynamic_libs/padscore_functions.h>
#include <dynamic_libs/fs_defs.h>
#include <dynamic_libs/vpad_functions.h>
#include <dynamic_libs/gx2_types.h>
#include <dynamic_libs/curl_functions.h>
#include <dynamic_libs/os_functions.h>
#include <dynamic_libs/gx2_functions.h>
#include <dynamic_libs/acp_functions.h>
#include <fs/fs_utils.h>
#include <fs/sd_fat_devoptab.h>
#include <system/memory.h>
#include <common/common.h>
#include <utils/utils.h>
#include <screen/tty.h>
#include "main.h"

int __entry_menu(int argc, char **argv)
{	
	// Initialize function pointers
	InitOSFunctionPointers();
	InitSocketFunctionPointers();
	InitACPFunctionPointers();
	InitAocFunctionPointers();
	InitAXFunctionPointers();
	InitCurlFunctionPointers();
	InitFSFunctionPointers();
	InitGX2FunctionPointers();
	InitPadScoreFunctionPointers();
	InitSysFunctionPointers();
	InitSysHIDFunctionPointers();
	InitVPadFunctionPointers();

	// Initialize memory management
	memory_init();
	
	// Mount the SD card
	mount_sd_fat("sd");
	
	// Initialize screen and stdout/stdin devoptabs
	tty_init();
	
	// Run the Main function
    int ret = Menu_Main();
	
	// Deinitialize screen
	tty_end();
	
	// Unmount the SD card
	unmount_sd_fat("sd");
	
	// Deinitialize memory management
	memory_end();

	// Return the result of the main function
    return ret;
}
