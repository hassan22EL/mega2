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
ifeq "$(wildcard nbproject/Makefile-local-ATmega16A.mk)" "nbproject/Makefile-local-ATmega16A.mk"
include nbproject/Makefile-local-ATmega16A.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=ATmega16A
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/app.c src/SystemTime.c src/EventsHandles.c src/CreateProduct.c src/Memory.c src/message.c inc/ProductSelect.c src/PrintLable.c src/PrintAction.c src/WorkingTime.c src/AddressableDevice.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/SystemTime.o ${OBJECTDIR}/src/EventsHandles.o ${OBJECTDIR}/src/CreateProduct.o ${OBJECTDIR}/src/Memory.o ${OBJECTDIR}/src/message.o ${OBJECTDIR}/inc/ProductSelect.o ${OBJECTDIR}/src/PrintLable.o ${OBJECTDIR}/src/PrintAction.o ${OBJECTDIR}/src/WorkingTime.o ${OBJECTDIR}/src/AddressableDevice.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app.o.d ${OBJECTDIR}/src/SystemTime.o.d ${OBJECTDIR}/src/EventsHandles.o.d ${OBJECTDIR}/src/CreateProduct.o.d ${OBJECTDIR}/src/Memory.o.d ${OBJECTDIR}/src/message.o.d ${OBJECTDIR}/inc/ProductSelect.o.d ${OBJECTDIR}/src/PrintLable.o.d ${OBJECTDIR}/src/PrintAction.o.d ${OBJECTDIR}/src/WorkingTime.o.d ${OBJECTDIR}/src/AddressableDevice.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/SystemTime.o ${OBJECTDIR}/src/EventsHandles.o ${OBJECTDIR}/src/CreateProduct.o ${OBJECTDIR}/src/Memory.o ${OBJECTDIR}/src/message.o ${OBJECTDIR}/inc/ProductSelect.o ${OBJECTDIR}/src/PrintLable.o ${OBJECTDIR}/src/PrintAction.o ${OBJECTDIR}/src/WorkingTime.o ${OBJECTDIR}/src/AddressableDevice.o

# Source Files
SOURCEFILES=src/app.c src/SystemTime.c src/EventsHandles.c src/CreateProduct.c src/Memory.c src/message.c inc/ProductSelect.c src/PrintLable.c src/PrintAction.c src/WorkingTime.c src/AddressableDevice.c

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
	${MAKE}  -f nbproject/Makefile-ATmega16A.mk ${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/ATmega16A/c043f412675290697e7be09fc149975c9c58a248 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/SystemTime.o: src/SystemTime.c  .generated_files/flags/ATmega16A/32b5ca4429cb1803450fd69044665aec93b0c980 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemTime.o.d 
	@${RM} ${OBJECTDIR}/src/SystemTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/SystemTime.o.d" -MT "${OBJECTDIR}/src/SystemTime.o.d" -MT ${OBJECTDIR}/src/SystemTime.o  -o ${OBJECTDIR}/src/SystemTime.o src/SystemTime.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/EventsHandles.o: src/EventsHandles.c  .generated_files/flags/ATmega16A/ead4428a2d4164e76788887a4638435b5e7e3c70 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o.d 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/EventsHandles.o.d" -MT "${OBJECTDIR}/src/EventsHandles.o.d" -MT ${OBJECTDIR}/src/EventsHandles.o  -o ${OBJECTDIR}/src/EventsHandles.o src/EventsHandles.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/CreateProduct.o: src/CreateProduct.c  .generated_files/flags/ATmega16A/e3b566115ab7d61e5e0d32495555a4016f25859d .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/CreateProduct.o.d 
	@${RM} ${OBJECTDIR}/src/CreateProduct.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/CreateProduct.o.d" -MT "${OBJECTDIR}/src/CreateProduct.o.d" -MT ${OBJECTDIR}/src/CreateProduct.o  -o ${OBJECTDIR}/src/CreateProduct.o src/CreateProduct.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Memory.o: src/Memory.c  .generated_files/flags/ATmega16A/5d22d554422a80c90d8773aa57856e5849aeccc5 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Memory.o.d 
	@${RM} ${OBJECTDIR}/src/Memory.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/Memory.o.d" -MT "${OBJECTDIR}/src/Memory.o.d" -MT ${OBJECTDIR}/src/Memory.o  -o ${OBJECTDIR}/src/Memory.o src/Memory.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/message.o: src/message.c  .generated_files/flags/ATmega16A/c477e4a973155fd127e4cb719d032320286d0f3d .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/message.o.d 
	@${RM} ${OBJECTDIR}/src/message.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/message.o.d" -MT "${OBJECTDIR}/src/message.o.d" -MT ${OBJECTDIR}/src/message.o  -o ${OBJECTDIR}/src/message.o src/message.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/inc/ProductSelect.o: inc/ProductSelect.c  .generated_files/flags/ATmega16A/aa74889f691826bb277ecd731a97a8c6299f5147 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/inc" 
	@${RM} ${OBJECTDIR}/inc/ProductSelect.o.d 
	@${RM} ${OBJECTDIR}/inc/ProductSelect.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/inc/ProductSelect.o.d" -MT "${OBJECTDIR}/inc/ProductSelect.o.d" -MT ${OBJECTDIR}/inc/ProductSelect.o  -o ${OBJECTDIR}/inc/ProductSelect.o inc/ProductSelect.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/PrintLable.o: src/PrintLable.c  .generated_files/flags/ATmega16A/87b9686ac26daa3eee8667954defeff7296a3ec9 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PrintLable.o.d 
	@${RM} ${OBJECTDIR}/src/PrintLable.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/PrintLable.o.d" -MT "${OBJECTDIR}/src/PrintLable.o.d" -MT ${OBJECTDIR}/src/PrintLable.o  -o ${OBJECTDIR}/src/PrintLable.o src/PrintLable.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/PrintAction.o: src/PrintAction.c  .generated_files/flags/ATmega16A/f704d19818b26149bd0210d79e1af44c5191985 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PrintAction.o.d 
	@${RM} ${OBJECTDIR}/src/PrintAction.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/PrintAction.o.d" -MT "${OBJECTDIR}/src/PrintAction.o.d" -MT ${OBJECTDIR}/src/PrintAction.o  -o ${OBJECTDIR}/src/PrintAction.o src/PrintAction.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/WorkingTime.o: src/WorkingTime.c  .generated_files/flags/ATmega16A/74a064dcbd8c62a0f982e8d9d21e38d99a7d2408 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o.d 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/WorkingTime.o.d" -MT "${OBJECTDIR}/src/WorkingTime.o.d" -MT ${OBJECTDIR}/src/WorkingTime.o  -o ${OBJECTDIR}/src/WorkingTime.o src/WorkingTime.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/AddressableDevice.o: src/AddressableDevice.c  .generated_files/flags/ATmega16A/53481665ff69f16d4c52d27b82f0b150a683bad9 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/AddressableDevice.o.d 
	@${RM} ${OBJECTDIR}/src/AddressableDevice.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/AddressableDevice.o.d" -MT "${OBJECTDIR}/src/AddressableDevice.o.d" -MT ${OBJECTDIR}/src/AddressableDevice.o  -o ${OBJECTDIR}/src/AddressableDevice.o src/AddressableDevice.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/ATmega16A/5f0a5d327a632de5e2f17c3e3de161d52737c9ce .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/SystemTime.o: src/SystemTime.c  .generated_files/flags/ATmega16A/3def64c4d8c9789266058df6d49cb4c263714a52 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemTime.o.d 
	@${RM} ${OBJECTDIR}/src/SystemTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/SystemTime.o.d" -MT "${OBJECTDIR}/src/SystemTime.o.d" -MT ${OBJECTDIR}/src/SystemTime.o  -o ${OBJECTDIR}/src/SystemTime.o src/SystemTime.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/EventsHandles.o: src/EventsHandles.c  .generated_files/flags/ATmega16A/929de13050de32f714058bf8a60c71206733cc14 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o.d 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/EventsHandles.o.d" -MT "${OBJECTDIR}/src/EventsHandles.o.d" -MT ${OBJECTDIR}/src/EventsHandles.o  -o ${OBJECTDIR}/src/EventsHandles.o src/EventsHandles.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/CreateProduct.o: src/CreateProduct.c  .generated_files/flags/ATmega16A/aaeed5a78ae52270889b9d0adb8c7c6a021779d3 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/CreateProduct.o.d 
	@${RM} ${OBJECTDIR}/src/CreateProduct.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/CreateProduct.o.d" -MT "${OBJECTDIR}/src/CreateProduct.o.d" -MT ${OBJECTDIR}/src/CreateProduct.o  -o ${OBJECTDIR}/src/CreateProduct.o src/CreateProduct.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Memory.o: src/Memory.c  .generated_files/flags/ATmega16A/cec2d4dda1e1387740629443ada832cb364305ed .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Memory.o.d 
	@${RM} ${OBJECTDIR}/src/Memory.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/Memory.o.d" -MT "${OBJECTDIR}/src/Memory.o.d" -MT ${OBJECTDIR}/src/Memory.o  -o ${OBJECTDIR}/src/Memory.o src/Memory.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/message.o: src/message.c  .generated_files/flags/ATmega16A/b9a71573b6283e57973702afbd4020eca3d4ce72 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/message.o.d 
	@${RM} ${OBJECTDIR}/src/message.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/message.o.d" -MT "${OBJECTDIR}/src/message.o.d" -MT ${OBJECTDIR}/src/message.o  -o ${OBJECTDIR}/src/message.o src/message.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/inc/ProductSelect.o: inc/ProductSelect.c  .generated_files/flags/ATmega16A/47548d94b050b810f279084ea604ee2d6a37d4a6 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/inc" 
	@${RM} ${OBJECTDIR}/inc/ProductSelect.o.d 
	@${RM} ${OBJECTDIR}/inc/ProductSelect.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/inc/ProductSelect.o.d" -MT "${OBJECTDIR}/inc/ProductSelect.o.d" -MT ${OBJECTDIR}/inc/ProductSelect.o  -o ${OBJECTDIR}/inc/ProductSelect.o inc/ProductSelect.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/PrintLable.o: src/PrintLable.c  .generated_files/flags/ATmega16A/d602d7f02f7c320b1bed58e5565fdcd6ec366a72 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PrintLable.o.d 
	@${RM} ${OBJECTDIR}/src/PrintLable.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/PrintLable.o.d" -MT "${OBJECTDIR}/src/PrintLable.o.d" -MT ${OBJECTDIR}/src/PrintLable.o  -o ${OBJECTDIR}/src/PrintLable.o src/PrintLable.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/PrintAction.o: src/PrintAction.c  .generated_files/flags/ATmega16A/7ed5b27a74cf793d19fe74f30db633746d276317 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PrintAction.o.d 
	@${RM} ${OBJECTDIR}/src/PrintAction.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/PrintAction.o.d" -MT "${OBJECTDIR}/src/PrintAction.o.d" -MT ${OBJECTDIR}/src/PrintAction.o  -o ${OBJECTDIR}/src/PrintAction.o src/PrintAction.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/WorkingTime.o: src/WorkingTime.c  .generated_files/flags/ATmega16A/33fb562a9bf097cebf03cc4e276091698d6e9437 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o.d 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/WorkingTime.o.d" -MT "${OBJECTDIR}/src/WorkingTime.o.d" -MT ${OBJECTDIR}/src/WorkingTime.o  -o ${OBJECTDIR}/src/WorkingTime.o src/WorkingTime.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/AddressableDevice.o: src/AddressableDevice.c  .generated_files/flags/ATmega16A/6cace095d806aef945e93124a6deaad4fa6ef836 .generated_files/flags/ATmega16A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/AddressableDevice.o.d 
	@${RM} ${OBJECTDIR}/src/AddressableDevice.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega16a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mshort-calls -Wall -MD -MP -MF "${OBJECTDIR}/src/AddressableDevice.o.d" -MT "${OBJECTDIR}/src/AddressableDevice.o.d" -MT ${OBJECTDIR}/src/AddressableDevice.o  -o ${OBJECTDIR}/src/AddressableDevice.o src/AddressableDevice.c  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../mega2.X/dist/ATmega16/production/mega2.X.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega16a ${PACK_COMMON_OPTIONS}  -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\SerialTools2.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\mega2.X\dist\ATmega16\production\mega2.X.a  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../mega2.X/dist/ATmega16/production/mega2.X.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega16a ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\SerialTools2.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\mega2.X\dist\ATmega16\production\mega2.X.a  -DXPRJ_ATmega16A=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/SerialTools2.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
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
