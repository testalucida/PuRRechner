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
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2110116603/Application.o \
	${OBJECTDIR}/_ext/2110116603/Calculator.o \
	${OBJECTDIR}/_ext/2110116603/ContainerIO.o \
	${OBJECTDIR}/_ext/2110116603/DepotWertCalculator.o \
	${OBJECTDIR}/_ext/2110116603/DialogModel.o \
	${OBJECTDIR}/_ext/2110116603/MainWindow.o \
	${OBJECTDIR}/_ext/2110116603/MySql.o \
	${OBJECTDIR}/_ext/2110116603/SaveHandler.o \
	${OBJECTDIR}/_ext/2110116603/Vertraege.o \
	${OBJECTDIR}/_ext/2110116603/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/purrechner

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/purrechner: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/purrechner ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2110116603/Application.o: /home/max/cpp/fltk/PuRRechner/src/Application.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/Application.o /home/max/cpp/fltk/PuRRechner/src/Application.cpp

${OBJECTDIR}/_ext/2110116603/Calculator.o: /home/max/cpp/fltk/PuRRechner/src/Calculator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/Calculator.o /home/max/cpp/fltk/PuRRechner/src/Calculator.cpp

${OBJECTDIR}/_ext/2110116603/ContainerIO.o: /home/max/cpp/fltk/PuRRechner/src/ContainerIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/ContainerIO.o /home/max/cpp/fltk/PuRRechner/src/ContainerIO.cpp

${OBJECTDIR}/_ext/2110116603/DepotWertCalculator.o: /home/max/cpp/fltk/PuRRechner/src/DepotWertCalculator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/DepotWertCalculator.o /home/max/cpp/fltk/PuRRechner/src/DepotWertCalculator.cpp

${OBJECTDIR}/_ext/2110116603/DialogModel.o: /home/max/cpp/fltk/PuRRechner/src/DialogModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/DialogModel.o /home/max/cpp/fltk/PuRRechner/src/DialogModel.cpp

${OBJECTDIR}/_ext/2110116603/MainWindow.o: /home/max/cpp/fltk/PuRRechner/src/MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/MainWindow.o /home/max/cpp/fltk/PuRRechner/src/MainWindow.cpp

${OBJECTDIR}/_ext/2110116603/MySql.o: /home/max/cpp/fltk/PuRRechner/src/MySql.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/MySql.o /home/max/cpp/fltk/PuRRechner/src/MySql.cpp

${OBJECTDIR}/_ext/2110116603/SaveHandler.o: /home/max/cpp/fltk/PuRRechner/src/SaveHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/SaveHandler.o /home/max/cpp/fltk/PuRRechner/src/SaveHandler.cpp

${OBJECTDIR}/_ext/2110116603/Vertraege.o: /home/max/cpp/fltk/PuRRechner/src/Vertraege.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/Vertraege.o /home/max/cpp/fltk/PuRRechner/src/Vertraege.cpp

${OBJECTDIR}/_ext/2110116603/main.o: /home/max/cpp/fltk/PuRRechner/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2110116603
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2110116603/main.o /home/max/cpp/fltk/PuRRechner/src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/purrechner

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
