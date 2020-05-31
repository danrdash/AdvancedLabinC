#ifndef GREP_MATCHING_LINE_H
#define GREP_MATCHING_LINE_H

#include "grep_lines_counters.h"
#include "grep_parser.h"
#include <stdbool.h>

bool is_match_in_line(const char *new_line, grepArguments *grepArguments);
bool is_print_line_without_match(grepArguments *grepArguments, LinesCounters *LinesCounters);

#endif