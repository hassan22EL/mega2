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
ifeq "$(wildcard nbproject/Makefile-local-Atmega128A.mk)" "nbproject/Makefile-local-Atmega128A.mk"
include nbproject/Makefile-local-Atmega128A.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Atmega128A
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
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega128a"



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
	${MAKE}  -f nbproject/Makefile-Atmega128A.mk ${DISTDIR}/mega2.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega128A
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
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/Atmega128A/cfcd58bdd21f3634460ec71abca334b664fc8e3 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/Atmega128A/66cdb6235685a51fcdab2c5f7974a614c1b978b4 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/Atmega128A/6ef82b2bb78424a37569d23a57e7aae1a3f321c0 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/Atmega128A/66ab3d790f584821307718f94834613a8f57de6d .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/Atmega128A/4f52f58abf0201497590ab7d0b149f00efe08bda .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/Atmega128A/6e2c57383e1040b1f2129c3b87e2312dd6df16f .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/Atmega128A/a7de72be3017ba7d02d390a6ee1f41f76603d2d0 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/Atmega128A/e85929247c6b8323b3afff5e873533bb41e20d6e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/Atmega128A/31af159f9740e687e7a6b912ced9a3a786b5b71b .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/Atmega128A/5ad8d2b7c29323838ad333ac2148add0ee819352 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/Atmega128A/8b395d8c9c30f2a255ebb8fef4572d223752055d .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/Atmega128A/ab85e983cf40e3a5c57e337050eea95235359ecf .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/Atmega128A/5871c3cef9fc76b6ae587b72ad2260be12c3698e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/Atmega128A/4b38329fed619480aa81bafc5a80a2e3fb6d20af .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/Atmega128A/b6e483875e6cc054b8edbe3a9120be91c8185cd4 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/Atmega128A/1f99243c679f0aa6fe6cdc7197a7046c58030d86 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/Atmega128A/93698327a581597fe4b9bb202789ce40bb137746 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/Atmega128A/800189584b02d4ef8538cc7e48efdca1142b4e42 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/Atmega128A/ea2771281614a2def0a6c600957cacedc9a830a4 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/Atmega128A/8cb7a568d8abfb97c375deba4a185cfe4002e4d4 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a   -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/mega/buffers/buffers.o: src/mega/buffers/buffers.c  .generated_files/flags/Atmega128A/9804c02a85c684129ad6cccd1ae95cef7afcbc3 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/buffers" 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o.d 
	@${RM} ${OBJECTDIR}/src/mega/buffers/buffers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT "${OBJECTDIR}/src/mega/buffers/buffers.o.d" -MT ${OBJECTDIR}/src/mega/buffers/buffers.o  -o ${OBJECTDIR}/src/mega/buffers/buffers.o src/mega/buffers/buffers.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/button/button.o: src/mega/button/button.c  .generated_files/flags/Atmega128A/23868957014bc4b0bea1de5901ecb3288ca781fb .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/button" 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o.d 
	@${RM} ${OBJECTDIR}/src/mega/button/button.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/button/button.o.d" -MT "${OBJECTDIR}/src/mega/button/button.o.d" -MT ${OBJECTDIR}/src/mega/button/button.o  -o ${OBJECTDIR}/src/mega/button/button.o src/mega/button/button.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/cmsa/csma.o: src/mega/cmsa/csma.c  .generated_files/flags/Atmega128A/452aec4de2c9e8c9b4b9947ac1e186b9e7a3af1 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/cmsa" 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o.d 
	@${RM} ${OBJECTDIR}/src/mega/cmsa/csma.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT "${OBJECTDIR}/src/mega/cmsa/csma.o.d" -MT ${OBJECTDIR}/src/mega/cmsa/csma.o  -o ${OBJECTDIR}/src/mega/cmsa/csma.o src/mega/cmsa/csma.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o: src/mega/ds1307/example/ds1307.X/src/app.c  .generated_files/flags/Atmega128A/28697eda60f68ebad423fdd18e88f0fa881ff4f9 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o  -o ${OBJECTDIR}/src/mega/ds1307/example/ds1307.X/src/app.o src/mega/ds1307/example/ds1307.X/src/app.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ds1307/ds1307.o: src/mega/ds1307/ds1307.c  .generated_files/flags/Atmega128A/aa8b3a93eeeca7076deb89c45d8d5200472a4480 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ds1307" 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ds1307/ds1307.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT "${OBJECTDIR}/src/mega/ds1307/ds1307.o.d" -MT ${OBJECTDIR}/src/mega/ds1307/ds1307.o  -o ${OBJECTDIR}/src/mega/ds1307/ds1307.o src/mega/ds1307/ds1307.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/eeprom/eeprom.o: src/mega/eeprom/eeprom.c  .generated_files/flags/Atmega128A/96b9229dfd1861c0f11b95c7547adfc3d50ac113 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/eeprom" 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/eeprom/eeprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT "${OBJECTDIR}/src/mega/eeprom/eeprom.o.d" -MT ${OBJECTDIR}/src/mega/eeprom/eeprom.o  -o ${OBJECTDIR}/src/mega/eeprom/eeprom.o src/mega/eeprom/eeprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/exeeprom/exEprom.o: src/mega/exeeprom/exEprom.c  .generated_files/flags/Atmega128A/eb3779994cb9f90ee34d64af2640ae91b10d3067 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/exeeprom" 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d 
	@${RM} ${OBJECTDIR}/src/mega/exeeprom/exEprom.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT "${OBJECTDIR}/src/mega/exeeprom/exEprom.o.d" -MT ${OBJECTDIR}/src/mega/exeeprom/exEprom.o  -o ${OBJECTDIR}/src/mega/exeeprom/exEprom.o src/mega/exeeprom/exEprom.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/gpio/gpio.o: src/mega/gpio/gpio.c  .generated_files/flags/Atmega128A/e8952752c894edb87aa86b9154001b070bca6d87 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/gpio" 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/mega/gpio/gpio.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT "${OBJECTDIR}/src/mega/gpio/gpio.o.d" -MT ${OBJECTDIR}/src/mega/gpio/gpio.o  -o ${OBJECTDIR}/src/mega/gpio/gpio.o src/mega/gpio/gpio.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/keypad/keypad.o: src/mega/keypad/keypad.c  .generated_files/flags/Atmega128A/604723e8cb60d75c6de128996c16355bf54b3da5 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/keypad" 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/src/mega/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT "${OBJECTDIR}/src/mega/keypad/keypad.o.d" -MT ${OBJECTDIR}/src/mega/keypad/keypad.o  -o ${OBJECTDIR}/src/mega/keypad/keypad.o src/mega/keypad/keypad.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcd/lcd.o: src/mega/lcd/lcd.c  .generated_files/flags/Atmega128A/e1a9e9a0d684ea606fe0e7ff12270af104a7f7dd .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcd" 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcd/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT "${OBJECTDIR}/src/mega/lcd/lcd.o.d" -MT ${OBJECTDIR}/src/mega/lcd/lcd.o  -o ${OBJECTDIR}/src/mega/lcd/lcd.o src/mega/lcd/lcd.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o: src/mega/lcdmnue/lcdmnue.c  .generated_files/flags/Atmega128A/bda1cdaed42831c84df767a2045775ab70b77bd6 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/lcdmnue" 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d 
	@${RM} ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT "${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o.d" -MT ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o  -o ${OBJECTDIR}/src/mega/lcdmnue/lcdmnue.o src/mega/lcdmnue/lcdmnue.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o: src/mega/signalGenertor/signalGenertor.c  .generated_files/flags/Atmega128A/5b33cb725ebb7948a5ff00eec6a65c1139ec4b7e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/signalGenertor" 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d 
	@${RM} ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT "${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o.d" -MT ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o  -o ${OBJECTDIR}/src/mega/signalGenertor/signalGenertor.o src/mega/signalGenertor/signalGenertor.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/system.o: src/mega/system/system.c  .generated_files/flags/Atmega128A/3dd22892780d79bf232b2d95dc14b3da83df43c9 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/system.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/system.o.d" -MT "${OBJECTDIR}/src/mega/system/system.o.d" -MT ${OBJECTDIR}/src/mega/system/system.o  -o ${OBJECTDIR}/src/mega/system/system.o src/mega/system/system.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/system/time.o: src/mega/system/time.c  .generated_files/flags/Atmega128A/42108a0d7fe5240bbe5386dbc95a0cc79b7082f0 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/system" 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o.d 
	@${RM} ${OBJECTDIR}/src/mega/system/time.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/system/time.o.d" -MT "${OBJECTDIR}/src/mega/system/time.o.d" -MT ${OBJECTDIR}/src/mega/system/time.o  -o ${OBJECTDIR}/src/mega/system/time.o src/mega/system/time.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/Tone/tone.o: src/mega/Tone/tone.c  .generated_files/flags/Atmega128A/6a5c091e77e595235451e3114cc5e1a2a9214cc5 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/Tone" 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o.d 
	@${RM} ${OBJECTDIR}/src/mega/Tone/tone.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT "${OBJECTDIR}/src/mega/Tone/tone.o.d" -MT ${OBJECTDIR}/src/mega/Tone/tone.o  -o ${OBJECTDIR}/src/mega/Tone/tone.o src/mega/Tone/tone.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/twi/twi.o: src/mega/twi/twi.c  .generated_files/flags/Atmega128A/1beea5330144e4d3ad0803d91b4c0d325262dd88 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/twi" 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o.d 
	@${RM} ${OBJECTDIR}/src/mega/twi/twi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT "${OBJECTDIR}/src/mega/twi/twi.o.d" -MT ${OBJECTDIR}/src/mega/twi/twi.o  -o ${OBJECTDIR}/src/mega/twi/twi.o src/mega/twi/twi.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/usart/usart.o: src/mega/usart/usart.c  .generated_files/flags/Atmega128A/dd447971416a34357b2c75344a84275d7ecaa44e .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/usart" 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o.d 
	@${RM} ${OBJECTDIR}/src/mega/usart/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT "${OBJECTDIR}/src/mega/usart/usart.o.d" -MT ${OBJECTDIR}/src/mega/usart/usart.o  -o ${OBJECTDIR}/src/mega/usart/usart.o src/mega/usart/usart.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/utility/utility.o: src/mega/utility/utility.c  .generated_files/flags/Atmega128A/db4e2ff210439309725e0f7619c2e182ad3c0bec .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/utility" 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o.d 
	@${RM} ${OBJECTDIR}/src/mega/utility/utility.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT "${OBJECTDIR}/src/mega/utility/utility.o.d" -MT ${OBJECTDIR}/src/mega/utility/utility.o  -o ${OBJECTDIR}/src/mega/utility/utility.o src/mega/utility/utility.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega/ZLP/ZLP.o: src/mega/ZLP/ZLP.c  .generated_files/flags/Atmega128A/5116e60926c6ec33254497d945512ac097463abd .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/mega/ZLP" 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o.d 
	@${RM} ${OBJECTDIR}/src/mega/ZLP/ZLP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT "${OBJECTDIR}/src/mega/ZLP/ZLP.o.d" -MT ${OBJECTDIR}/src/mega/ZLP/ZLP.o  -o ${OBJECTDIR}/src/mega/ZLP/ZLP.o src/mega/ZLP/ZLP.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/mega.o: src/mega.c  .generated_files/flags/Atmega128A/d2f42d77c0431f63157ae4c79818868c35573a83 .generated_files/flags/Atmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mega.o.d 
	@${RM} ${OBJECTDIR}/src/mega.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a    -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/mega.o.d" -MT "${OBJECTDIR}/src/mega.o.d" -MT ${OBJECTDIR}/src/mega.o  -o ${OBJECTDIR}/src/mega.o src/mega.c  -DXPRJ_Atmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
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
