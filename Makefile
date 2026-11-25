# sätter vilken kompilator jag vill använda (basically gcc eller clang då)
CC = gcc
# sätter flaggor för kompileringsregler, tvingar fram c99 standard, wall för vanliga varningar, Wextra mer nyans till wall, och "-g" inkluderar debuginfo i binary för GDB ska funka ordentligt
CFLAGS = -std=c99 -Wall -Wextra -g
# "TARGET = " - basically namnet på .exe filen vi bygger
TARGET = prototypeC99.exe

#hitta de färdigkompilerade Raylib mapparna med alla libraries:
RAYLIB_INC = C:/raylib/w64devkit/include
RAYLIB_LIB = C:/raylib/w64devkit/lib

#lägg till (addendera) Raylib include i compilation flags + leta efter include .h(eader) filer i mappen "include"
CFLAGS += -idirafter $(RAYLIB_INC) -Iinclude
#CFLAGS += -I$(RAYLIB_INC) -Iinclude
LDFLAGS = -L$(RAYLIB_LIB) -lraylib -lopengl32 -lgdi32 -lwinmm


# Automatiska fil-hittar kommandon
#wildcard är makefile feature, plockar alla .c typ filer i projektets root-folder (men nu har jag lagt till att den letar bara i 'src' foldern och MAX EN sub-folder till inuti i 'src')
SRCS = $(wildcard src/*.c src/**/*.c)
# "substitution reference" tar alla .c filers namn och lägger i minnet vad för .o filer den ska skapa som har samma namn...
OBJS = $(SRCS:.c=.o)

#Standardmålet, så när man skriver "make" är det vad man satt som target som ...blir dess target
all: $(TARGET)

#länkar mina object files med raylib (och annat mög om jag specifierat det)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Generera .o från .c | "mönsterregel/pattern rule" | "%" är ett wildcard som matchar vad som helst
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#typ pathing macros för vad som ska involveras vid respektive kommando
.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)