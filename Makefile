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

SMTP_SERVER =		bin/smtp_mendoza_server

SRC_SMTP_DIR = src/smtp_server

SRC_COMMON_DIR = src/common

COMMON_SOURCES = $(shell find $(SRC_COMMON_DIR)  -name "*.cpp")

SMTP_SOURCES = $(shell find $(SRC_SMTP_DIR)  -name "*.cpp")

SMTP_OBJ := $(SMTP_SOURCES:src/smtp_server/%.cpp=build/smtp_server/%.o)

SMTP_OBJ += $(COMMON_SOURCES:src/common/%.cpp=build/common/%.o)

SMTP_DEPS = $(shell find ./include/smtp_server  -name "*.hh")

COMMON_DEPS = $(shell find ./include/common  -name "*.hh")

SMTP_DEPS += $(COMMON_DEPS)

build/smtp_server/%.o : $(SRC_SMTP_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

build/common/%.o : src/common/%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

all:		$(SMTP_SERVER)

$(SMTP_SERVER):	$(SMTP_OBJ) $(SMTP_DEPS)
		$(CC) $(CFLAGS) $(INC)  $(SMTP_OBJ) -o $@

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#									      #
#                 		TESTS					      #
#									      #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

TESTS_DIR =		tests

TESTS_SMTP_DIR =	$(TESTS_DIR)/smtp_server

TESTS_POP_DIR =		$(TESTS_DIR)/pop_server

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
######

run_tests:	$(SMTP_TESTS)
		python3 -m unittest

test_smtp_echo : $(TEST_SMTP_ECHO)

test_smtp_proto : $(TEST_SMTP_PROTO)

$(TEST_SMTP_ECHO):	$(TEST_SMTP_OBJ) $(SMTP_DEPS) $(MAIN_TEST_SMTP_ECHO_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN_TEST_SMTP_ECHO_OBJ) $(TEST_SMTP_OBJ) -o $@

$(TEST_SMTP_PROTO):	$(TEST_SMTP_OBJ) $(SMTP_DEPS) $(MAIN_TEST_SMTP_PROTO_OBJ)
		$(CC) $(CFLAGS) $(INC) $(MAIN_TEST_SMTP_PROTO_OBJ) $(TEST_SMTP_OBJ) -o $@

clean_tests:
			$(RM) $(TEST_SMTP_OBJ) $(MAIN_TEST_SMTP_ECHO_OBJ)

clean:
			$(RM) $(SMTP_OBJ)

fclean:		clean
			$(RM) $(SMTP_SERVER) $(TESTS)

re:			fclean $(SMTP_SERVER)

re_tests:		fclean run_tests

.PHONY:			all clean fclean re clean_tests run_tests re_tests
