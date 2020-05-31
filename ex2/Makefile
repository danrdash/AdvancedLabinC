.PHONY: all test clean 

all: my_grep 

my_grep: IO.o grep_matching_line.o grep_lines_counters.o \
	grep_parser.o my_grep.o	
	gcc  *.o -o my_grep

my_grep.o: my_grep.c grep_parser.h grep_lines_counters.h \
	grep_matching_line.h IO.h
	gcc -c my_grep.c -o my_grep.o

grep_matching_line.o: grep_matching_line.c grep_matching_line.h \
	grep_parser.h grep_lines_counters.h  
	gcc -c -Wall -Wextra grep_matching_line.c -o grep_matching_line.o

grep_lines_counters.o: grep_lines_counters.c grep_lines_counters.h grep_parser.h 
	gcc -c -Wall -Wextra grep_lines_counters.c -o grep_lines_counters.o


grep_parser.o: grep_parser.c grep_parser.h 
	gcc -c -Wall -Wextra grep_parser.c -o \
                grep_parser.o

IO.o: IO.c IO.h grep_lines_counters.h grep_parser.h 
	gcc -c -Wall -Wextra IO.c -o IO.o

test: 
	/specific/a/home/cc/students/csguests/nimrodav/grep_tests/run_all.sh	

clean: 
	rm *.o  my_grep
                                     
