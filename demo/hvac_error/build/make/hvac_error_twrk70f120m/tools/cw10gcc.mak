#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/rtcs/rtcs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/shell/shell.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/usb/usbh.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/__arm_start.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/__arm_end.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/librt.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libstdc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/lib/gcc/arm-none-eabi/4.7.3/armv7e-m/fpu/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/arm-none-eabi/lib/armv7e-m/fpu/libsupc++.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/psp/psp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/mfs/mfs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/rtcs/rtcs.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/shell/shell.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/usb/usbh.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/__arm_start.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/__arm_end.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/librt.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/fpu/libstdc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/lib/gcc/arm-none-eabi/4.7.3/armv7e-m/fpu/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/arm-none-eabi/lib/armv7e-m/fpu/libsupc++.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/rtcs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/shell
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/debug/usb
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/psp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/mfs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/rtcs
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/shell
INCLUDE += $(MQX_ROOTDIR)/lib/twrk70f120m.cw10gcc/release/usb
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif




#-----------------------------------------------------------
# 'debug' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
AS_FLAGS += -Xassembler --no-warn -x assembler-with-cpp 
CX_FLAGS += -c -fmessage-length=0 -Wno-switch -Wno-unused-value -Wno-unused-variable -Wno-unused-but-set-variable -Wno-pointer-to-int-cast -Wno-unused-function -Wno-unused-label -Wno-char-subscripts -Wno-int-to-pointer-cast 
endif
#-----------------------------------------------------------
# 'release' configuration settings
#-----------------------------------------------------------
ifeq ($(CONFIG),release)
AS_FLAGS += -Xassembler --no-warn -x assembler-with-cpp 
CX_FLAGS += -c -fmessage-length=0 -Wno-switch -Wno-unused-value -Wno-unused-variable -Wno-unused-but-set-variable -Wno-pointer-to-int-cast -Wno-unused-function -Wno-unused-label -Wno-char-subscripts -Wno-int-to-pointer-cast 
endif


