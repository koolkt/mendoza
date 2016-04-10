#
#   Makefile for zappy
#
#

CC =		g++

CFLAGS =	-std=c++11 -Wall -Werror -Wextra -g

RM =		rm -f

INC =		-I./include/common -I./include/pop_server -I./include/smtp_server


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#									      #
#                 		SERVERS					      #
#									      #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#     Common
#

SRC_COMMON_DIR = src/common

COMMON_SOURCES = $(shell find $(SRC_COMMON_DIR)  -name "*.cpp")

COMMON_OBJ = $(COMMON_SOURCES:src/common/%.cpp=build/common/%.o)

COMMON_DEPS = $(shell find ./include/common  -name "*.hh")

build/common/%.o : src/common/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

#
#    Smtp Server
#

SMTP_SERVER =		bin/smtp_mendoza_server

SRC_SMTP_DIR = src/smtp_server

SMTP_SOURCES = $(shell find $(SRC_SMTP_DIR)  -name "*.cpp")

SMTP_OBJ := $(SMTP_SOURCES:src/smtp_server/%.cpp=build/smtp_server/%.o)

SMTP_OBJ += $(COMMON_OBJ)

SMTP_DEPS = $(shell find ./include/smtp_server  -name "*.hh")

SMTP_DEPS += $(COMMON_DEPS)

build/smtp_server/%.o : $(SRC_SMTP_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

all:		$(SMTP_SERVER)

$(SMTP_SERVER):	$(SMTP_OBJ) $(SMTP_DEPS)
		$(CC) $(CFLAGS) $(INC)  $(SMTP_OBJ) -o $@


#
#       POP SERVER
#


POP_SERVER =		bin/pop_mendoza_server

SRC_POP_DIR = src/pop_server

POP_SOURCES = $(shell find $(SRC_POP_DIR)  -name "*.cpp")

POP_OBJ := $(POP_SOURCES:src/pop_server/%.cpp=build/pop_server/%.o)

POP_OBJ += $(COMMON_OBJ)

POP_DEPS = $(shell find ./include/pop_server  -name "*.hh")

POP_DEPS += $(COMMON_DEPS)

build/pop_server/%.o : $(SRC_POP_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#									      #
#                 		TESTS					      #
#									      #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

TESTS_DIR =		tests

TESTS_SMTP_DIR =	$(TESTS_DIR)/smtp_server

TESTS_POP_DIR =		$(TESTS_DIR)/pop_server

#
#      SMTP TESTS
#

TEST_DIR_SMTP_ECHO =	$(TESTS_SMTP_DIR)/test_echo

TEST_DIR_SMTP_PROTO =	$(TESTS_SMTP_DIR)/test_smtp


TEST_SMTP_SOURCES = $(shell find $(SRC_SMTP_DIR)  -name "*.cpp" ! -name 'main.cpp')

TEST_SMTP_OBJ := $(TEST_SMTP_SOURCES:src/smtp_server/%.cpp=build/smtp_server/%.o)

TEST_SMTP_OBJ += $(COMMON_SOURCES:src/common/%.cpp=build/common/%.o)

MAIN_TEST_SMTP_ECHO_OBJ  = $(TEST_DIR_SMTP_ECHO)/build/test_main.o

MAIN_TEST_SMTP_PROTO_OBJ  = $(TEST_DIR_SMTP_PROTO)/build/test_main.o


TEST_SMTP_ECHO =	$(TEST_DIR_SMTP_ECHO)/bin/test_smtp_echo

TEST_SMTP_PROTO = 	$(TEST_DIR_SMTP_PROTO)/bin/test_smtp_protocol

SMTP_TESTS =		$(TEST_SMTP_ECHO) $(TEST_SMTP_PROTO)

tests/smtp_server/%/build/test_main.o : tests/smtp_server/%/src/test_main.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

#####################################################################################
#
#    POP TESTS
#

TEST_DIR_POP_ECHO =	$(TESTS_POP_DIR)/test_echo

TEST_DIR_POP_PROTO =	$(TESTS_POP_DIR)/test_pop


TEST_POP_SOURCES = $(shell find $(SRC_POP_DIR)  -name "*.cpp" ! -name 'main.cpp')

TEST_POP_OBJ := $(TEST_POP_SOURCES:src/pop_server/%.cpp=build/pop_server/%.o)

TEST_POP_OBJ += $(COMMON_SOURCES:src/common/%.cpp=build/common/%.o)

MAIN_TEST_POP_ECHO_OBJ  = $(TEST_DIR_POP_ECHO)/build/test_main.o

MAIN_TEST_POP_PROTO_OBJ  = $(TEST_DIR_POP_PROTO)/build/test_main.o

TEST_POP_ECHO =	$(TEST_DIR_POP_ECHO)/bin/test_pop_echo

TEST_POP_PROTO =	$(TEST_DIR_POP_PROTO)/bin/test_pop_protocol

POP_TESTS =		$(TEST_POP_ECHO) $(TEST_POP_PROTO)

tests/pop_server/%/build/test_main.o : tests/pop_server/%/src/test_main.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

#####################################################################################

SMTP_TEST_OBJECTS =		$(TEST_SMTP_OBJ) $(MAIN_TEST_SMTP_ECHO_OBJ) $(MAIN_TEST_SMTP_PROTO_OBJ)

POP_TEST_OBJECTS =		$(TEST_POP_OBJ) $(MAIN_TEST_POP_ECHO_OBJ)

TESTS = $(SMTP_TESTS) $(POP_TESTS)

run_tests:	$(TESTS)
		python3 -m unittest

run_smtp_tests:	$(SMTP_TESTS)
		python3 -m unittest discover tests/smtp_server/

run_pop_tests:	$(POP_TESTS)
		python3 -m unittest discover tests/pop_server/

re_tests:		fclean run_tests

clean_tests:
			$(RM) $(SMTP_TEST_OBJECTS) $(POP_TEST_OBJECTS)

#
#      SMTP TESTS
#

test_smtp_echo : $(TEST_SMTP_ECHO)

test_smtp_proto : $(TEST_SMTP_PROTO)

$(TEST_SMTP_ECHO):	$(TEST_SMTP_OBJ) $(SMTP_DEPS) $(MAIN_TEST_SMTP_ECHO_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN_TEST_SMTP_ECHO_OBJ) $(TEST_SMTP_OBJ) -o $@

$(TEST_SMTP_PROTO):	$(TEST_SMTP_OBJ) $(SMTP_DEPS) $(MAIN_TEST_SMTP_PROTO_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN_TEST_SMTP_PROTO_OBJ) $(TEST_SMTP_OBJ) -o $@

#
#      POP TESTS
#

test_pop_echo : $(TEST_POP_ECHO)

test_pop_proto : $(TEST_POP_PROTO)

$(TEST_POP_ECHO):	$(POP_DEPS) $(TEST_POP_OBJ) $(MAIN_TEST_POP_ECHO_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN_TEST_POP_ECHO_OBJ) $(TEST_POP_OBJ) -o $@

$(TEST_POP_PROTO):	$(TEST_POP_OBJ) $(POP_DEPS) $(MAIN_TEST_POP_PROTO_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN_TEST_POP_PROTO_OBJ) $(TEST_POP_OBJ) -o $@

#######################################################################################

clean:
			$(RM) $(SMTP_OBJ) $(POP_OBJ)

fclean:		clean clean_tests
			$(RM) $(SMTP_SERVER) $(POP_SERVER) $(TESTS)

re:			fclean $(SMTP_SERVER) # $(POP_SERVER)

.PHONY:			all clean fclean re clean_tests run_tests re_tests
