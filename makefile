###############################################################################
# Makefile of Generic Linked List Project
# Author: Emir
# Date: 10.01.2025
# Details: This makefile will call makefiles of linked_list and test
###############################################################################

PROJ_ROOT_DIR:=.

SRC_DIR:= $(PROJ_ROOT_DIR)/src

MODULE_NAME:=linked_list
TEST_NAME:=test
TEST_OBJ_NAME:=main.o

TARGET_DIR:=$(PROJ_ROOT_DIR)/libs
TARGET:=$(TARGET_DIR)/lib$(MODULE_NAME).a

TEST_OBJ_DIR:=$(PROJ_ROOT_DIR)/obj/$(TEST_NAME)
TEST_OBJ:=$(TEST_OBJ_DIR)/$(TEST_OBJ_NAME)
TEST_TARGET_DIR:=$(PROJ_ROOT_DIR)/bin/$(TEST_NAME)
TEST_TARGET:= $(TEST_TARGET_DIR)/$(TEST_NAME)


# User-defined function
define makeallmodules
	for dir in $(SRC_DIR)/*; \
		do \
		make -C $$dir $(1); \
		done
endef

LD:= gcc

########## LINKER FLAGS ##########
LIBRARY_DIR= $(PROJ_ROOT_DIR)/libs
LIBRARY:=linked_list
DEP_LIBS = -L$(LIBRARY_DIR) -l$(LIBRARY) -lcheck -lsubunit -pthread -lrt -lm
									
#DEP_LIBS = -lcheck

# RPATH IS USED FOR LINKING USER DEFINED LIBS IN SPECIFIC PATH DURING
# BUILDING THE MODULE.It is needed for the User of the .so. \
    # Unit test binary may use it.
#RPATH="-Wl,-rpath,$(TARGET_DIR):$(TARGET_DIR)/3rd_party_lib"

#RPATH="-Wl,-rpath,$(TARGET_DIR)"

LDFLAGS = $(DEP_LIBS) $(RPATH)
LDFLAGS_PROFILING = $(DEP_LIBS) $(RPATH) -pg

########## LINKER FLAGS END ##########
all: 
	$(MAKE) -C $(SRC_DIR)/$(MODULE_NAME)

test: 
	$(MAKE) -C $(SRC_DIR)/$(MODULE_NAME)
	$(MAKE) -C $(SRC_DIR)/$(TEST_NAME)
	$(LD) $(TEST_OBJ) $(LDFLAGS) -o $(TEST_TARGET)

build_and_run:
	$(MAKE) test
	$(MAKE) run
	

run:
	@echo "\nRunning the test\n"
	$(TEST_TARGET)

build_dir:
	mkdir -p $(PROJ_ROOT_DIR)/bin
	mkdir -p $(PROJ_ROOT_DIR)/src
	mkdir -p $(PROJ_ROOT_DIR)/include
	mkdir -p $(PROJ_ROOT_DIR)/obj
	$(call makeallmodules, build_dir)

build_dependencies:
	$(call makeallmodules, build_dependencies)

mem_check:
	valgrind --leak-check=full --show-leak-kinds=all ./bin/test/test

clean:
	$(call makeallmodules, clean)
	rm -rf bin/test/test

.phony: all test run build_dir build_dependencies mem_check clean


