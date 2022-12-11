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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/app.c src/events.c src/resepassword.c src/Indicator.c src/defalut.c src/user.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/events.o ${OBJECTDIR}/src/resepassword.o ${OBJECTDIR}/src/Indicator.o ${OBJECTDIR}/src/defalut.o ${OBJECTDIR}/src/user.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app.o.d ${OBJECTDIR}/src/events.o.d ${OBJECTDIR}/src/resepassword.o.d ${OBJECTDIR}/src/Indicator.o.d ${OBJECTDIR}/src/defalut.o.d ${OBJECTDIR}/src/user.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/events.o ${OBJECTDIR}/src/resepassword.o ${OBJECTDIR}/src/Indicator.o ${OBJECTDIR}/src/defalut.o ${OBJECTDIR}/src/user.o

# Source Files
SOURCEFILES=src/app.c src/events.c src/resepassword.c src/Indicator.c src/defalut.c src/user.c

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
	${MAKE}  -f nbproject/Makefile-ATmega8.mk ${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/ATmega8/99a41d788fddab1ed34bf807ba66b218d4bbd55b .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/events.o: src/events.c  .generated_files/flags/ATmega8/125b1b3481714cc23666a6be8c59a9fafa6f7f03 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/events.o.d 
	@${RM} ${OBJECTDIR}/src/events.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/events.o.d" -MT "${OBJECTDIR}/src/events.o.d" -MT ${OBJECTDIR}/src/events.o  -o ${OBJECTDIR}/src/events.o src/events.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/resepassword.o: src/resepassword.c  .generated_files/flags/ATmega8/6ed7aa3f576a5004929f6fa012e9dc9c37e0e05e .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/resepassword.o.d 
	@${RM} ${OBJECTDIR}/src/resepassword.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/resepassword.o.d" -MT "${OBJECTDIR}/src/resepassword.o.d" -MT ${OBJECTDIR}/src/resepassword.o  -o ${OBJECTDIR}/src/resepassword.o src/resepassword.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Indicator.o: src/Indicator.c  .generated_files/flags/ATmega8/c32f12373bdca1038ead1a1cad281e14ae572bf4 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Indicator.o.d 
	@${RM} ${OBJECTDIR}/src/Indicator.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/Indicator.o.d" -MT "${OBJECTDIR}/src/Indicator.o.d" -MT ${OBJECTDIR}/src/Indicator.o  -o ${OBJECTDIR}/src/Indicator.o src/Indicator.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/defalut.o: src/defalut.c  .generated_files/flags/ATmega8/bfc7d9cd3d410f5b203298f894999cb6b8e4a5e1 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/defalut.o.d 
	@${RM} ${OBJECTDIR}/src/defalut.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/defalut.o.d" -MT "${OBJECTDIR}/src/defalut.o.d" -MT ${OBJECTDIR}/src/defalut.o  -o ${OBJECTDIR}/src/defalut.o src/defalut.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/user.o: src/user.c  .generated_files/flags/ATmega8/6a9ca20a10fa290fad668771e8e9eba18b7a85e0 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/user.o.d 
	@${RM} ${OBJECTDIR}/src/user.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/user.o.d" -MT "${OBJECTDIR}/src/user.o.d" -MT ${OBJECTDIR}/src/user.o  -o ${OBJECTDIR}/src/user.o src/user.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/ATmega8/4e55909a0c6557ca87ad94cced13d1435344844b .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/events.o: src/events.c  .generated_files/flags/ATmega8/9aa9fc2cac18e5f5870ba13356d1a9bd3e038acb .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/events.o.d 
	@${RM} ${OBJECTDIR}/src/events.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/events.o.d" -MT "${OBJECTDIR}/src/events.o.d" -MT ${OBJECTDIR}/src/events.o  -o ${OBJECTDIR}/src/events.o src/events.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/resepassword.o: src/resepassword.c  .generated_files/flags/ATmega8/d7ac711e2ec455e7745f2aa63c2efe970e16194a .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/resepassword.o.d 
	@${RM} ${OBJECTDIR}/src/resepassword.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/resepassword.o.d" -MT "${OBJECTDIR}/src/resepassword.o.d" -MT ${OBJECTDIR}/src/resepassword.o  -o ${OBJECTDIR}/src/resepassword.o src/resepassword.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Indicator.o: src/Indicator.c  .generated_files/flags/ATmega8/3b3dfd3369ebe8a8e7057c3c8a964ad9ea859f25 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Indicator.o.d 
	@${RM} ${OBJECTDIR}/src/Indicator.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/Indicator.o.d" -MT "${OBJECTDIR}/src/Indicator.o.d" -MT ${OBJECTDIR}/src/Indicator.o  -o ${OBJECTDIR}/src/Indicator.o src/Indicator.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/defalut.o: src/defalut.c  .generated_files/flags/ATmega8/7fdc1cb6955d48e5dfe68c35d7b7968ad23b8457 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/defalut.o.d 
	@${RM} ${OBJECTDIR}/src/defalut.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/defalut.o.d" -MT "${OBJECTDIR}/src/defalut.o.d" -MT ${OBJECTDIR}/src/defalut.o  -o ${OBJECTDIR}/src/defalut.o src/defalut.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/user.o: src/user.c  .generated_files/flags/ATmega8/e472bcdecdae5863b367b2c121cc03f40e7aec23 .generated_files/flags/ATmega8/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/user.o.d 
	@${RM} ${OBJECTDIR}/src/user.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega8a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/user.o.d" -MT "${OBJECTDIR}/src/user.o.d" -MT ${OBJECTDIR}/src/user.o  -o ${OBJECTDIR}/src/user.o src/user.c  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../mega2.X/dist/ATmega8/production/mega2.X.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega8a ${PACK_COMMON_OPTIONS}  -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\ElectronicSafe.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\mega2.X\dist\ATmega8\production\mega2.X.a  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../mega2.X/dist/ATmega8/production/mega2.X.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega8a ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\ElectronicSafe.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\mega2.X\dist\ATmega8\production\mega2.X.a  -DXPRJ_ATmega8=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/ElectronicSafe.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
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
