#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-ATmega8.mk)" "nbproject/Makefile-local-ATmega8.mk"
include nbproject/Makefile-local-ATmega8.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=ATmega8
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/mega/buffers/buffers.c src/mega/button/button.c src/mega/cmsa/csma.c src/mega/ds1307/example/ds1307.X/src/app.c src/mega/ds1307/ds1307.c src/mega/eeprom/eeprom.c src/mega/exeeprom/exEprom.c src/mega/gpio/gpio.c src/mega/keypad/keypad.c src/mega/lcd/lcd.c src/mega/lcdmnue/lcdmnue.c src/mega/signalGenertor/signalGenertor.c src/mega/system/system.c src/mega/system/time.c src/mega/twi/twi.c src/mega/usart/usart.c src/mega.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/mega/buffers/buffers.o ${OBJECTDIR}/src/mega/button/button.o ${OBJECTDIR}/src/mega/cmsa/csma.o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o ${OBJECTDIR}/src/mega/ds1307/ds1307.o ${OBJECTDIR}/src/mega/eeprom/eeprom.o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o ${OBJECTDIR}/src/mega/gpio/gpio.o ${OBJECTDIR}/src/mega/keypad/keypad.o ${OBJECTDIR}/src/mega/lcd/lcd.o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o ${OBJECTDIR}/src/mega/system/system.o ${OBJECTDIR}/src/mega/system/time.o ${OBJECTDIR}/src/mega/twi/twi.o ${OBJECTDIR}/src/mega/usart/usart.o ${OBJECTDIR}/src/mega.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/mega/buffers/buffers.o.d ${OBJECTDIR}/src/mega/button/button.o.d ${OBJECTDIR}/src/mega/cmsa/csma.o.d ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d ${OBJECTDIR}/src/mega/gpio/gpio.o.d ${OBJECTDIR}/src/mega/keypad/keypad.o.d ${OBJECTDIR}/src/mega/lcd/lcd.o.d ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d ${OBJECTDIR}/src/mega/system/system.o.d ${OBJECTDIR}/src/mega/system/time.o.d ${OBJECTDIR}/src/mega/twi/twi.o.d ${OBJECTDIR}/src/mega/usart/usart.o.d ${OBJECTDIR}/src/mega.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/mega/buffers/buffers.o ${OBJECTDIR}/src/mega/button/button.o ${OBJECTDIR}/src/mega/cmsa/csma.o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o ${OBJECTDIR}/src/mega/ds1307/ds1307.o ${OBJECTDIR}/src/mega/eeprom/eeprom.o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o ${OBJECTDIR}/src/mega/gpio/gpio.o ${OBJECTDIR}/src/mega/keypad/keypad.o ${OBJECTDIR}/src/mega/lcd/lcd.o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o ${OBJECTDIR}/src/mega/system/system.o ${OBJECTDIR}/src/mega/system/time.o ${OBJECTDIR}/src/mega/twi/twi.o ${OBJECTDIR}/src/mega/usart/usart.o ${OBJECTDIR}/src/mega.o

# Source Files
SOURCEFILES=src/mega/buffers/buffers.c src/mega/button/button.c src/mega/cmsa/csma.c src/mega/ds1307/example/ds1307.X/src/app.c src/mega/ds1307/ds1307.c src/mega/eeprom/eeprom.c src/mega/exeeprom/exEprom.c src/mega/gpio/gpio.c src/mega/keypad/keypad.c src/mega/lcd/lcd.c src/mega/lcdmnue/lcdmnue.c src/mega/signalGenertor/signalGenertor.c src/mega/system/system.c src/mega/system/time.c src/mega/twi/twi.c src/mega/usart/usart.c src/mega.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega8a"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-ATmega8.mk ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega8A
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/ATmega8/555ac5afca9d36d86cdfdb6470b337e3f9933960 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/ATmega8/7102483462b81037f80ee6f3975b431a60ca08de .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/ATmega8/79c726aed1d6967dd5027694f9365aab5bd30a18 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/ATmega8/7363af2a75f2d63cbd16dd287e1a4f1b369a6602 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/ATmega8/a02b19d7bed96ccf8b6596f056f656e8dd3907da .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/ATmega8/5cc471dc9a58a89fa046f74e5d3d8689a35b3842 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/ATmega8/b5f5dd5e94d275923327e39261cedb4dd75fe5e3 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/ATmega8/d10bee0cca9e23991b2b8a1414385c986ab3b700 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/ATmega8/a36202ed3c03aaa534f4c776b5d196cac66ea6f7 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/ATmega8/c7f0258deafda3af831b190bde14ebdefd8c43e0 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/ATmega8/36247b0497fcf54dda4b099cd4e8d96d3339bb59 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/ATmega8/eabd4c7a173eaf07a0cc7d998f20e9c182bf3f7c .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/ATmega8/31ec4e252bf3cf828515523cfee0ed5f381cf99c .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/ATmega8/b7020524b7dac8b9ca215d735a60909065746ed .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/ATmega8/e2f8302f532bd285a97307e54a0e1d1a6b07a009 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/ATmega8/60a93f938da80aceff85b4a1b03446fc0d37edb1 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/ATmega8/a67aaab00d2dc45e91fec458b42c678bea624818 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/ATmega8/4ddc9447d6132c9fa85d9d527cdd94f5d0b22aa0 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/ATmega8/27374d79165a02a4d8d8cf931506e08fa3b621db .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/ATmega8/4f324f25e0b42b3bbee65c46b5aa5bb20f8e3387 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/ATmega8/fb9eb90844bd3378f176eda07d1e809d72141067 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/ATmega8/df96d14da55bf0865b6e6834e0112c9d6c509fce .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/ATmega8/c86064f0d58e4134c7243b0f2e9b8ed537286b36 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/ATmega8/30be880e99f1431205f5d0a3577a70df5ece25d9 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/ATmega8/e76ed304f12a06ec97dba6abb7bd41bdf176626e .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/ATmega8/3feb168673e82800948fe1506b1d14fccb3086e5 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/ATmega8/7210427d8fd07e5a7a35943ccdb49889c40e355a .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/ATmega8/a9c123d6ef5915504eedc75f7c3ddfc5c70ce09f .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/ATmega8/eb415e1197c4f4cdd103e0195e45af35ef04abd0 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/ATmega8/c0947cb199fbac51555eda5c60394e6b08232b7a .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/ATmega8/36926cee0eb743923b4a9074d1758f078c815981 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/ATmega8/8c685182cf55bf8d74e24a85de0b735a26c58a77 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/ATmega8/37a7b5a12934e2c0f2772892006ad30617479cf4 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/ATmega8/33bca6e408b18ceb42547fdd3038e4c30bac8d98 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE) -r -o ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}   
else
${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE) -r -o ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
