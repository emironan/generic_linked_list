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

TARGET_DIR:=$(PROJ_ROOT_DIR)/obj/$(MODULE_NAME)
TARGET:=$(TARGET_DIR)/$(MODULE_NAME).o

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

#DEP_LIBS = -L$(LIBRARY_DIR) -lemp

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
	$(LD) $(LDFLAGS) $(TARGET) $(TEST_OBJ) -o $(TEST_TARGET)

run: $(TEST_TARGET)
	$(TEST_TARGET)

build_dir:
	mkdir -p $(PROJ_ROOT_DIR)/bin
	mkdir -p $(PROJ_ROOT_DIR)/src
	mkdir -p $(PROJ_ROOT_DIR)/include
	mkdir -p $(PROJ_ROOT_DIR)/obj
	$(call makeallmodules, build_dir)

build_dependencies:
	$(call makeallmodules, build_dependencies)

clean:
	$(call makeallmodules, clean)
	rm -rf bin/test/test

.phony: all test run build_dir build_dependencies clean


