OS = $(shell uname)
COMPILER=gcc
ifeq ($(OS), Darwin)
	CFLAGS = -std=c++17 -g -Wall -Werror -Wextra -lstdc++ -lm
else
	CFLAGS=-std=c++17 -g -Wall -Werror -Wextra -lstdc++ -Wl,--no-as-needed -lm -pthread
endif
TFLAGS=-lgtest -lgcov
BUILD=build/
LCOVFLAGS=-coverage
HTML=lcov -t $(BUILD)$(EXE) --capture -o $(BUILD)rep.info -c -d .
EXE=test

all: clean gcov_report

clean:
	rm -rf *.gcno *.gcda $(BUILD)

test: tests/test*
	mkdir build
	$(COMPILER) -g tests/test* $(LCOVFLAGS) $(CFLAGS) $(TFLAGS) -o $(BUILD)$(EXE)
	$(BUILD)$(EXE)

gcov_report: test
	$(HTML)
	genhtml -o $(BUILD)report $(BUILD)rep.info
	open $(BUILD)report/index.html

check: clean test
	clang-format -style="{BasedOnStyle: Google}" -n tests/*.cc libraries/*.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config libraries/*.cc libraries/*.h
ifeq ($(OS), Darwin)
	leaks --atExit -- $(BUILD)$(EXE)
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(BUILD)RESULT_VALGRIND.txt $(BUILD)$(EXE)
endif
