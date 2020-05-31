#! /usr/bin/env bash

grep -H -n -E "([0-9][0-9]|[3-9])" *.c | grep -v "#define"

if ls *.h 1> /dev/null 2>&1; then
    grep -H -n -E "([0-9][0-9]|[3-9])" *.h | grep -v "#define"
fi
