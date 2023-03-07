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
ifeq "$(wildcard nbproject/Makefile-local-ATmega16.mk)" "nbproject/Makefile-local-ATmega16.mk"
include nbproject/Makefile-local-ATmega16.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=ATmega16
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
SOURCEFILES_QUOTED_IF_SPACED=src/mega/buffers/buffers.c src/mega/button/button.c src/mega/cmsa/csma.c src/mega/ds1307/example/ds1307.X/src/app.c src/mega/ds1307/ds1307.c src/mega/eeprom/eeprom.c src/mega/exeeprom/exEprom.c src/mega/gpio/gpio.c src/mega/keypad/keypad.c src/mega/lcd/lcd.c src/mega/lcdmnue/lcdmnue.c src/mega/signalGenertor/signalGenertor.c src/mega/system/system.c src/mega/system/time.c src/mega/Tone/tone.c src/mega/twi/twi.c src/mega/usart/usart.c src/mega/utility/utility.c src/mega/ZLP/ZLP.c src/mega.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/mega/buffers/buffers.o ${OBJECTDIR}/src/mega/button/button.o ${OBJECTDIR}/src/mega/cmsa/csma.o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o ${OBJECTDIR}/src/mega/ds1307/ds1307.o ${OBJECTDIR}/src/mega/eeprom/eeprom.o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o ${OBJECTDIR}/src/mega/gpio/gpio.o ${OBJECTDIR}/src/mega/keypad/keypad.o ${OBJECTDIR}/src/mega/lcd/lcd.o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o ${OBJECTDIR}/src/mega/system/system.o ${OBJECTDIR}/src/mega/system/time.o ${OBJECTDIR}/src/mega/Tone/tone.o ${OBJECTDIR}/src/mega/twi/twi.o ${OBJECTDIR}/src/mega/usart/usart.o ${OBJECTDIR}/src/mega/utility/utility.o ${OBJECTDIR}/src/mega/ZLP/ZLP.o ${OBJECTDIR}/src/mega.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/mega/buffers/buffers.o.d ${OBJECTDIR}/src/mega/button/button.o.d ${OBJECTDIR}/src/mega/cmsa/csma.o.d ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d ${OBJECTDIR}/src/mega/gpio/gpio.o.d ${OBJECTDIR}/src/mega/keypad/keypad.o.d ${OBJECTDIR}/src/mega/lcd/lcd.o.d ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d ${OBJECTDIR}/src/mega/system/system.o.d ${OBJECTDIR}/src/mega/system/time.o.d ${OBJECTDIR}/src/mega/Tone/tone.o.d ${OBJECTDIR}/src/mega/twi/twi.o.d ${OBJECTDIR}/src/mega/usart/usart.o.d ${OBJECTDIR}/src/mega/utility/utility.o.d ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d ${OBJECTDIR}/src/mega.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/mega/buffers/buffers.o ${OBJECTDIR}/src/mega/button/button.o ${OBJECTDIR}/src/mega/cmsa/csma.o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o ${OBJECTDIR}/src/mega/ds1307/ds1307.o ${OBJECTDIR}/src/mega/eeprom/eeprom.o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o ${OBJECTDIR}/src/mega/gpio/gpio.o ${OBJECTDIR}/src/mega/keypad/keypad.o ${OBJECTDIR}/src/mega/lcd/lcd.o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o ${OBJECTDIR}/src/mega/system/system.o ${OBJECTDIR}/src/mega/system/time.o ${OBJECTDIR}/src/mega/Tone/tone.o ${OBJECTDIR}/src/mega/twi/twi.o ${OBJECTDIR}/src/mega/usart/usart.o ${OBJECTDIR}/src/mega/utility/utility.o ${OBJECTDIR}/src/mega/ZLP/ZLP.o ${OBJECTDIR}/src/mega.o

# Source Files
SOURCEFILES=src/mega/buffers/buffers.c src/mega/button/button.c src/mega/cmsa/csma.c src/mega/ds1307/example/ds1307.X/src/app.c src/mega/ds1307/ds1307.c src/mega/eeprom/eeprom.c src/mega/exeeprom/exEprom.c src/mega/gpio/gpio.c src/mega/keypad/keypad.c src/mega/lcd/lcd.c src/mega/lcdmnue/lcdmnue.c src/mega/signalGenertor/signalGenertor.c src/mega/system/system.c src/mega/system/time.c src/mega/Tone/tone.c src/mega/twi/twi.c src/mega/usart/usart.c src/mega/utility/utility.c src/mega/ZLP/ZLP.c src/mega.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega16a"



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
	${MAKE}  -f nbproject/Makefile-ATmega16.mk ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega16A
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
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/ATmega16/1410cbe15471f732c09ecff8271756f90feea328 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/ATmega16/8f2dc64c0568f46520d92138c4c5ad1231171df1 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/ATmega16/96423d15a8a1eae0dbf19073682376774256df61 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/ATmega16/d04ae4dc70926af94984015c057741c53a66f7d4 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/ATmega16/2f17e048c6938970d0a2ce01920c45e5d34aebb .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/ATmega16/579db5c2d35b9ef5bd88de4df1b735045262164 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/ATmega16/c55590b784b56b6497286450a4964f9bfdbf3aab .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/ATmega16/4d945f9c762cd015b00227c02ea663a8a1eedf5e .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/ATmega16/10caabb07a0bdf6e4316c91be42f2ea296e7bafb .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/ATmega16/ee2be579564dc24b94fe95f1a29a0b3251a04792 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/ATmega16/958f57102df5b781a2f8352d9c1d312f7b452e6e .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/ATmega16/4fff1e797eebad4f4f7d19e2a7521a3fb0f4eb83 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/ATmega16/32e50888eacbb05f2908032219a9f2f8fc437c2a .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/ATmega16/f43da5efdcb19d7145158feefbc1e90c816f6d29 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/ATmega16/3f70c599bb19c87d6c99de1ddd54dc56ac05ecfd .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/ATmega16/674fe2067f25a30d259aaaa5496112f7f59976e .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/ATmega16/cf028a95e8407c22321aa06f9ab164bbd9f2cb81 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/ATmega16/ac6fd1a2fadec1383be6cc98a40393872b5ad10 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/ATmega16/e361bb0da1aef945c5ee0b440a0e4f4d6b910a2f .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/ATmega16/2f1aef65f6dbbe5243d6af028f844d86b07e8bea .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/ATmega16/7afd898875ffe3ade1059d53ea337d0075f98890 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/ATmega16/5282adb539ad38a88fdb1a539f2b5af4f2ecef6 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/ATmega16/785f25e3072ed6dd97bde52008c8a91d2ba9661 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/ATmega16/5378fb033d5162669d6b42a046e69c41853fc397 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/ATmega16/834fea2f4ebbd68510a4ff9eb380d064f20e3121 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/ATmega16/58c5fb91176091c7e72b98f42d84661c9ff2bf84 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/ATmega16/670fde6f09f32708fd0f2152bc7b4d6b702fa716 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/ATmega16/f2995fa545df1e7fd823f8b69b5a88e4c568e43b .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/ATmega16/5ffe2a43cdce31973dbebe379630940541bbef2e .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/ATmega16/d892fa5a840690e6069e957d053b01659884bdf6 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/ATmega16/250b1f6e1317be14a6307c9e91a9f5020296a298 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/ATmega16/9432cc3243a2690c9d68fa5a1746d236d07051bb .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/ATmega16/52fb7da4cef8183865486fc0870178a89081a334 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/ATmega16/b895992ac91bfc46600cf28cc15b1773c5c3e3b7 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/ATmega16/7a189f841d1ec71b5e277854b013a0d1f584ee09 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/ATmega16/dad9757bde26570623ab7dc1b1729babf5fb8a43 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/ATmega16/9e9e0be952900d4dc36a3dcb6676f180d3d3e7fc .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/ATmega16/232533c4659ef557af02bc8c263b2fb2de5dc6cd .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/ATmega16/b681f96a5fad90240d8e0b6daec3b16d5fbcd19f .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/ATmega16/1956d708226a12fab695b31609b3feafad631f9 .generated_files/flags/ATmega16/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_ATmega16=$(CND_CONF)  $(COMPARISON_BUILD) 
	
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
