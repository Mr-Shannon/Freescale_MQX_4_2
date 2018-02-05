#-----------------------------------------------------------
# libraries
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/debug/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/debug/psp/psp.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/__arm_start.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/__arm_end.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/librt.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libstdc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/lib/gcc/arm-none-eabi/4.7.3/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/arm-none-eabi/lib/armv7e-m/libsupc++.a
endif
ifeq ($(CONFIG),release)
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/release/bsp/bsp.a
LIBRARIES += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/release/psp/psp.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/__arm_start.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/__arm_end.o
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/librt.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libm.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/lib/armv7e-m/libstdc++.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/lib/gcc/arm-none-eabi/4.7.3/armv7e-m/libgcc.a
LIBRARIES += $(TOOLCHAIN_ROOTDIR)/Cross_Tools/arm-none-eabi-gcc-4_7_3/arm-none-eabi/lib/armv7e-m/libsupc++.a
endif


#-----------------------------------------------------------
# search paths
#-----------------------------------------------------------
ifeq ($(CONFIG),debug)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/debug/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/debug
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/debug/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/debug/psp
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_C/include
INCLUDE += $(TOOLCHAIN_ROOTDIR)/MCU/ARM_GCC_Support/ewl/EWL_Runtime/include
endif
ifeq ($(CONFIG),release)
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/release/bsp/Generated_Code
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/release
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/release/bsp
INCLUDE += $(MQX_ROOTDIR)/lib/twrk20d50m.cw10gcc/release/psp
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


