# Makefile of Generic Linked List static library
# Author: Emir
# Date: 10.01.2025
# Details: This makefile is written for building linked_list library

BUILD_TYPE = $(RELEASE)
#BUILD_TYPE = $(DEBUG)
MODULE_NAME:= linked_list
OBJ_NAME:=$(MODULE_NAME).o
TARGET_NAME:= $(MODULE_NAME).a

CC:= gcc

PROJ_ROOT_DIR:= ../..
OBJ_DIR:= $(PROJ_ROOT_DIR)/obj/$(MODULE_NAME)
OBJ:=$(OBJ_DIR)/$(OBJ_NAME)

INC_DIR:= $(PROJ_ROOT_DIR)/include/$(MODULE_NAME)

TARGET_NAME:= lib$(MODULE_NAME).a
TARGET_DIR:= $(PROJ_ROOT_DIR)/libs
TARGET:=$(TARGET_DIR)/$(TARGET_NAME)

SRC:=./$(MODULE_NAME).c
DEP:=./$(MODULE_NAME).d

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

$(TARGET): $(OBJ)
	 ar rcs $@ $^	

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) -c $^ -o $@ 

# with looking to headers we are keeping our dependency updated in case of any added include to any header
# in this project we will probably only have 1 header file but it is a good practice to keep things in this way
$(DEP):$(SRC) $(HEADERS)
	$(CC) $(CCFLAGS) -M $(SRC) > $@

include $(DEP)
	
build_dependencies: $(DEP)

build_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(DEP)
	rm -rf $(TARGET)

.phony: build_dir build_dependencies install clean