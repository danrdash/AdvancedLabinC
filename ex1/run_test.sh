#! /usr/bin/env bash

~nimrodav/grep_tests/test_permissions.sh

~nimrodav/socket_ex/verify_readme.sh

~nimrodav/grep_tests/check_line_lengths.sh

cat ~nimrodav/ex1/test1_input | ./ex1 | diff -b ~nimrodav/ex1/test1_output -

python2.7 ~nimrodav/grep_tests/check_private_functions.py ex1

~nimrodav/header_guards/check_header_guards.sh

~nimrodav/header_guards/check_unnecessary_includes.sh

~nimrodav/grep_tests/check_defines.py

cat SDP | grep -v -i SDP

cat COPYING_WILL_BE_REPORTED | grep -v -i COPYING_WILL_BE_REPORTED
