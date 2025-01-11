# Makefile of Generic Linked List static Library's tests
# Author: Emir
# Date: 11.01.2025
# Details: This makefile is written for building test of linked_list library

BUILD_TYPE = $(RELEASE)
#BUILD_TYPE = $(DEBUG)
MODULE_NAME:= test
SRC_NAME:= main
TARGET_NAME:= $(SRC_NAME).o

CC:= gcc

PROJ_ROOT_DIR:= ../..
OBJ_DIR:= $(PROJ_ROOT_DIR)/obj
INC_DIR:= $(PROJ_ROOT_DIR)/include/linked_list/

TARGET_DIR:= $(OBJ_DIR)/$(MODULE_NAME)
TARGET:=$(OBJ_DIR)/$(MODULE_NAME)/$(TARGET_NAME)

SRC:=./$(SRC_NAME).c
DEP:=./$(SRC_NAME).d

# We want to check if any include is added to amn included dependency file
# with keeping track of any header that is changed we can see if any dependency changed
HEADERS=$(wildcard $(PROJ_ROOT_DIR)/include/*/*.h) # Taking all of the headers

########## CC FLAGS ##########

STDFLAG = -std=c11

INC:=-I$(INC_DIR)

#choose release/debug
DEBUG = -pipe -g -Wall -W -fPIC
RELEASE = -pipe -O2 -Wall -W -fPIC

# -D stands for DEFINE. If want to define any macro which is used in code for \
    #  timestamp or git revision etc, can be used in this way.
DEFINES = -DBUILD_TIMESTAMP_STR=\"$(BUILD_TIMESTAMP)\" \
	  -DINSTALLATION_PATH_STR=\"$(INSTALLATION_PATH)\"

#UNCOMMENT IF LIKE TO SEE FOLLOWING WARNINGS. ATLEAST ONCE THIS NEEDS TO BE RUN\
FOR EACH MODULE
WARN=-Wall -Wextra -Werror -Wwrite-strings -Wno-parentheses \
     -pedantic -Warray-bounds -Wno-unused-variable -Wno-unused-function \
     -Wno-unused-parameter -Wno-unused-result

CCFLAGS = $(STDFLAG) $(BUILD_TYPE) $(DEFINES) $(WARN) $(INC)

########## CC FLAGS END ##########

$(TARGET): $(SRC)
	$(CC) $(CCFLAGS) -c $^ -o $@ 

# with looking to headers we are keeping our dependency updated in case of any added include to any header
# in this project we will probably only have 1 header file but it is a good practice to keep things in this way
$(DEP):$(SRC) $(HEADERS)
	$(CC) $(CCFLAGS) -M $(SRC) > $@

include $(DEP)
	
build_dependencies: $(DEP)

build_dir:
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(DEP)
	rm -rf $(TARGET)


.phony: build_dir build_dependencies install clean