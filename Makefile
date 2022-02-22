# Executable names:
EXE = final_graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o map.o

# Generated files
#CLEAN_RM = out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk
