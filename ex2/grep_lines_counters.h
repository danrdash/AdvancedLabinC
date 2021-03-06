#ifndef GREP_LINES_COUNTERS_H
#define GREP_LINES_COUNTERS_H

#include "grep_parser.h"

typedef struct LinesCounters {
  int num_of_lines_in_file;
  int num_of_matched_lines_in_file;
  int offset_from_start_of_InputFile;
  int num_of_lines_to_print_after_match;
} LinesCounters;

void init_LinesCounters(LinesCounters *LinesCounters);
void update_num_of_lines_to_print_after_match(grepArguments *grepArguments, LinesCounters *LinesCounters);

#endif
