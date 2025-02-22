############################################################
# Author		: Mahmoud Karam
# Version		: 2
# Description	: makefile for Desktop C apps automates:
#					* Build Process: <make all>
#						Folder structure:
#							* src 		folder has source files.
#							* include 	folder has header files.
#							* lib 		folder has libraaries files.
#							IF YOU WANT ANOTHER NAME FOR THESE FOLDERS, CHANGE MACROS BELOW (SDIR, HDIR, LDIR)
#					* Write/Read from MCU Flash: <make flash>/<make read>
#					* Read MCU fuse: <make rfuse> 
#					* Clean Binaries & Output Files <make clean>
#						used if makefile has any changes or when 
#						making version control.
#					* Project creation: <make project>
#						pass project name to make: <NAME=test>
#					* Create driver folder: <make driver>
#						pass driver name to make: <NAME=test>
############################################################

############################################################
#					Configurations
############################################################

# Host Configurations
# SHELL 	= cmd
# RM		= del /s /q
# RMDIR	= rmdir /s /q

SHELL 	= bash
RM		= rm -fv
RMDIR	= rm -rf

# Note: / is used with GCC as it's linux SW.
# Note: \ is used with Windows, So, if working on Linux,
#		assume changing \ to / in Windows commands or paths

# Files directories
SDIR	= src
ODIR 	= obj
HDIR	= include
DDIR	= dep
debugDIR= debug
LDIR	= lib

SRCS	= ${wildcard ${SDIR}/*.c}
OBJS 	= ${SRCS:${SDIR}/%.c=${ODIR}/%.o}
DEPS 	= ${SRCS:${SDIR}/%.c=${DDIR}/%.d}
-include ${DEPS}

# Target configurations, compiler flags and dependencies flags
TARGET 	= app.hex
FCPU	= 8000000UL
# compiler configurations
CC 		= avr-gcc
CFLAGS	= -c -O1 -Wall -Wextra -std=c99 -pedantic -Wundef -Wunused-macros -Wcast-align -Wlogical-op -fno-common 
EXTRACFLAGS = -wtraditional -Wdangling-pointer -Wfloat-conversion -Wsizeof-array-div -Wsizeof-pointer-div -fno-short-enum -Wtraditional-conversion -Wconversion
DBGFLAGS = -g3

MCU		= atmega32
LIBS	= -lm

# Tools options
OBJCOPY	= ${CC:%gcc=%objcopy}
OBJCOPY_FLAGS= -j .text -j .data -j .bss -j .rdata -O ihex
SIZE_SW	= ${CC:%gcc=%size}

#Burner SW Configurations
BURN_SW	= avrdude
DUDE_MCU= m32
PRGRMR	= usbasp
PORT	= usb
BAUDRATE= 115200

############################################################
#					Building Rules
############################################################
.PHONY	: all
all 	: ${TARGET}

${TARGET} : makeDirs ${OBJS}
	@echo
	@echo [*-------- Linking object files to binary file -------*]
	@${CC} -mmcu=${MCU} ${OBJS} -o ${@:%.hex=${debugDIR}/%.bin} \
	-Xlinker -Map=${@:%.hex=${debugDIR}/%.map}
	@echo "   File ${@:%.hex=${debugDIR}/%.bin} generated"

	
	@${OBJCOPY} ${OBJCOPY_FLAGS} ${@:%.hex=${debugDIR}/%.bin} ${@}
	@echo	
	@echo [*--------------- Excecutable file Info --------------*]
	@${SIZE_SW} -B ${@:%.hex=${debugDIR}/%.bin}
	@echo
	@echo "   Finished building: $@"
	@echo "   Microcontroller:   ${MCU}"
	@echo "   Frequncy:          ${FCPU} Hz"
	@echo "   Compiler:          ${CC}"
	@echo [*----------------------------------------------------*]
	@echo
	@echo "    |    ||||||||||  ||||||||     ||||  "
	@echo "  || ||      ||           ||    ||    ||"
	@echo " ||   ||     ||         ||           ||"
	@echo "|||||||||    ||           ||        ||  "
	@echo "||     ||    ||      ||    ||     ||    "
	@echo "||     ||    ||        ||||     ||||||||"
	
	








.PHONY	: makeDirs
makeDirs:
	@echo [*--------------- Creating Directories ---------------*]
	@-mkdir ${ODIR} ${DDIR} ${debugDIR}
	
${ODIR}/%.o : ${SDIR}/%.c 
	@echo Generating object file: $@
	@${CC} -mmcu=${MCU} -D__DELAY_BACKWARD_COMPATIBLE__ ${CFLAGS} -I "${HDIR}" -D F_CPU=${FCPU} \
	$< -o $@ ${LIBS} -MMD -MF ${@:${ODIR}/%.o=${DDIR}/%.d}
	
flash:
	${BURN_SW} -c ${PRGRMR} -p ${DUDE_MCU} -P ${PORT} -F -V -U flash:w:${TARGET}:i 
	
read:
	${BURN_SW} -c ${PRGRMR} -p ${DUDE_MCU} -P ${PORT} -F \
	-U flash:r:${TARGET:%.hex=%_read.hex}:i -b ${BAUDRATE}

rfuse:	
	${BURN_SW} -c ${PRGRMR} -p ${DUDE_MCU} -P ${PORT} -F -v -b ${BAUDRATE}

clean	:
	${RMDIR} ${ODIR} ${DDIR} ${debugDIR}
	${RM} ${TARGET}  ${SDIR}\*~ ${HDIR}\*~ *.su

.PHONY	: read flash rfuse clean