This folder contains the build project only just for arm gcc tool chains supported in USB stack. 
The other complier workspace not in the folder, the workspace will be in corresponding folder under usb_core.
Take an example, the USB device IAR library workspace will be in <USB stack dir>/usb_core/device/build/iar 

This folder contains makefiles in following structure: 

build
+---common
|   +---make        ... shared Makefiles with global settings, variables and paths
+---<board1>        ... board-specific folder
|   +---make        ... folder contains build Makefile for all libraries
|       +---tools   ... tool-specific global settings, variables and paths
+---<board2>  
    +---make
        ...

  Note: 
  - Please use the mingw32-make version 3.8.2 or higher. Download the latest version from http://sourceforge.net/projects/mingw/. 
  - Prior the build you should specify the path (TOOLCHAIN_ROOTDIR variable) to your build tools in the <USB stack dir>/build/common/make/global.mak. To get the default path to the toolchain 
    navigate to the toolchain installation directory and execute "command" on the Windows Command Prompt.
