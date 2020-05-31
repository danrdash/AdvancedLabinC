#ifndef IO_H
#define IO_H

#include "grep_lines_counters.h"
#include "grep_parser.h"
#include <stdio.h>

int read_line(FILE *InputFile, char *new_line[]);
void print_line(char *line, grepArguments *grepArguments, LinesCounters *LinesCounters, bool is_match_in_line);

#endif
