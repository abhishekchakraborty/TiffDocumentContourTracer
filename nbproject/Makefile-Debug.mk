#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/547641067/unionfind.o \
	${OBJECTDIR}/_ext/547641067/components.o \
	${OBJECTDIR}/_ext/547641067/read_imag.o \
	${OBJECTDIR}/_ext/547641067/Tiff.o \
	${OBJECTDIR}/_ext/547641067/contour.o \
	${OBJECTDIR}/_ext/547641067/main.o \
	${OBJECTDIR}/_ext/547641067/Wtiff.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/da_components

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/da_components: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -lm -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/da_components ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/547641067/unionfind.o: /home/abhi/NetBeansProjects/DA_Components/unionfind.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/unionfind.o /home/abhi/NetBeansProjects/DA_Components/unionfind.c

${OBJECTDIR}/_ext/547641067/components.o: /home/abhi/NetBeansProjects/DA_Components/components.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/components.o /home/abhi/NetBeansProjects/DA_Components/components.c

${OBJECTDIR}/_ext/547641067/read_imag.o: /home/abhi/NetBeansProjects/DA_Components/read_imag.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/read_imag.o /home/abhi/NetBeansProjects/DA_Components/read_imag.c

${OBJECTDIR}/_ext/547641067/Tiff.o: /home/abhi/NetBeansProjects/DA_Components/Tiff.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/Tiff.o /home/abhi/NetBeansProjects/DA_Components/Tiff.c

${OBJECTDIR}/_ext/547641067/contour.o: /home/abhi/NetBeansProjects/DA_Components/contour.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/contour.o /home/abhi/NetBeansProjects/DA_Components/contour.c

${OBJECTDIR}/_ext/547641067/main.o: /home/abhi/NetBeansProjects/DA_Components/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/main.o /home/abhi/NetBeansProjects/DA_Components/main.c

${OBJECTDIR}/_ext/547641067/Wtiff.o: /home/abhi/NetBeansProjects/DA_Components/Wtiff.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/547641067
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/547641067/Wtiff.o /home/abhi/NetBeansProjects/DA_Components/Wtiff.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/da_components

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
