#! /usr/bin/env bash

gcc -Wall -Wextra  my_grep.c IO.c grep_matching_line.c grep_parser.c grep_lines_counters.c -o my_grep -O0
~nimrodav/grep_tests/check_line_lengths.sh
python2.7 ~nimrodav/grep_tests/check_private_functions.py ./my_grep
~nimrodav/header_guards/check_header_guards.sh
~nimrodav/header_guards/check_unnecessary_includes.sh
~nimrodav/grep_tests/check_defines.py
~nimrodav/grep_tests/check_magic_constants.sh

~nimrodav/grep_tests/beta2.sh
~nimrodav/grep_tests/run10.sh
~nimrodav/grep_tests/run11.sh
~nimrodav/grep_tests/run12.sh
~nimrodav/grep_tests/run13.sh
~nimrodav/grep_tests/run14.sh
~nimrodav/grep_tests/run15.sh
~nimrodav/grep_tests/run16.sh
~nimrodav/grep_tests/run17.sh
./my_grep one ~yehudar/c_lab/ex2/beta2/tests/one_line_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/one_line_output.txt -
./my_grep sfgsfe ~yehudar/c_lab/ex2/beta2/tests/one_line_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/empty_file.txt -
./my_grep Let ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_output.txt -
./my_grep sfgsfe ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/empty_file.txt -
./my_grep sfgsfe ~yehudar/c_lab/ex2/beta2/tests/empty_file.txt | diff ~yehudar/c_lab/ex2/beta2/tests/empty_file.txt -
./my_grep -i let ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/ignore_case_sensitivity__output.txt -
./my_grep -i lET ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/ignore_case_sensitivity__output.txt -
./my_grep -i SDFgfd ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/empty_file.txt -
./my_grep -v sdfsf ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt -
./my_grep -v et  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/invers_grep_output.txt -
./my_grep -v -i ET  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/invers_grep_output.txt -
./my_grep -i -v eT  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/invers_grep_output.txt -
./my_grep -v -i VWsfSF  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt -
./my_grep -c one  ~yehudar/c_lab/ex2/beta2/tests/one_line_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/report_num_of_matched_lines_output_1.txt -
./my_grep -c Let ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/report_num_of_matched_lines_output_2.txt -
./my_grep -c -i Let ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/report_num_of_matched_lines_output_3.txt -
./my_grep -c -i -v Let ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/report_num_of_matched_lines_output_4.txt -
./my_grep -n -i lET ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/print_line_num_output_1.txt -
./my_grep -n -v -i lET ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/print_line_num_output_2.txt -
./my_grep -b let  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/print_line_offset_output_1.txt -
./my_grep -b -v Let  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/print_line_offset_output_2.txt -
./my_grep -i -b -v LET  ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/print_line_offset_output_3.txt -
./my_grep -x bam ~yehudar/c_lab/ex2/beta2/tests/tighted_match_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/tighted_match_output_1.txt -
./my_grep -x -i bam ~yehudar/c_lab/ex2/beta2/tests/tighted_match_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/tighted_match_output_2.txt -
./my_grep -x -i -v bam ~yehudar/c_lab/ex2/beta2/tests/tighted_match_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/tighted_match_output_3.txt -
./my_grep -A 2 let ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/A_NUM_output_1.txt -
./my_grep -A 2 -i we ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/A_NUM_output_2.txt -
./my_grep -A 3 -v e ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/A_NUM_output_3.txt -
./my_grep -A 2 -n -b we ~yehudar/c_lab/ex2/beta2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/beta2/tests/A_NUM_output_4.txt -
./my_grep -E "\[now" ~yehudar/c_lab/ex2/beta2/tests/switch_E_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/switch_E_output_1.txt -
./my_grep -E "s\[til\)l" ~yehudar/c_lab/ex2/beta2/tests/switch_E_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/switch_E_output_2.txt -
./my_grep -E "ya\aa" ~yehudar/c_lab/ex2/beta2/tests/switch_E_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/switch_E_output_3.txt -
./my_grep -E "le\\ts" ~yehudar/c_lab/ex2/beta2/tests/switch_E_input.txt | diff ~yehudar/c_lab/ex2/beta2/tests/empty_file.txt -
./my_grep -E "le."  ~yehudar/c_lab/ex2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/tests/dot_output_1.txt -
./my_grep -E "W." ~yehudar/c_lab/ex2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/tests/dot_output_2.txt -
./my_grep -i -E "W."  ~yehudar/c_lab/ex2/tests/multiple_lines_input.txt | diff  ~yehudar/c_lab/ex2/tests/dot_output_3.txt -
./my_grep -E "[y-z]\." ~nimrodav/grep_tests/2013.html | diff  ~yehudar/c_lab/ex2/tests/square_brackets_output_1.txt -
./my_grep -E "[f-z]\." ~nimrodav/grep_tests/2013.html | diff  ~yehudar/c_lab/ex2/tests/square_brackets_output_2.txt -
./my_grep -E "\[[0-9]\]" ~nimrodav/grep_tests/in16 | diff ~yehudar/c_lab/ex2/tests/square_brackets_output_3.txt -
