#include "grep_lines_counters.h"

void init_LinesCounters(LinesCounters *LinesCounters)
{
  LinesCounters->num_of_lines_in_file = 0;
  LinesCounters->num_of_matched_lines_in_file = 0;
  LinesCounters->offset_from_start_of_InputFile = 0;
  LinesCounters->num_of_lines_to_print_after_match = -1;
}

void update_num_of_lines_to_print_after_match(grepArguments *grepArguments, LinesCounters *LinesCounters)
{
  if (grepArguments->print_NUM_of_lines_after_match) {
    LinesCounters->num_of_lines_to_print_after_match = grepArguments->NUM_of_lines;
  }
}
