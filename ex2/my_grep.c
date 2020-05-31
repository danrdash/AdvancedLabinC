#include "IO.h"
#include "grep_lines_counters.h"
#include "grep_matching_line.h"
#include "grep_parser.h"
#include <stdio.h>
#include <stdlib.h>

void free_line(char *line)
{
  if (line != NULL) {
    free(line);
  }
}

void report_line_match(char *new_line, grepArguments *grepArguments, LinesCounters *LinesCounters, int line_size)
{
  if (grepArguments->print_line_num) {
    LinesCounters->num_of_lines_in_file++;
  }
  if (is_match_in_line(new_line, grepArguments)) {
    if (grepArguments->report_num_of_matched_lines) {
      LinesCounters->num_of_matched_lines_in_file++;
    } else {
      print_line(new_line, grepArguments, LinesCounters, true);
      update_num_of_lines_to_print_after_match(grepArguments, LinesCounters);
    }
  } else if (is_print_line_without_match(grepArguments, LinesCounters)) {
    print_line(new_line, grepArguments, LinesCounters, false);
    LinesCounters->num_of_lines_to_print_after_match--;
  }
  if (grepArguments->print_line_offset) {
    LinesCounters->offset_from_start_of_InputFile += line_size;
  }
}

int main(int argc, char *argv[])
{
  FILE *InputFile = NULL;
  char *new_line = NULL;
  int line_size = 0;
  grepArguments grepArguments;
  LinesCounters LinesCounters;
  update_grepArguments(&grepArguments, argc, argv);
  init_LinesCounters(&LinesCounters);
  if (grepArguments.InputFile_path != NULL) {
    InputFile = fopen(grepArguments.InputFile_path, "r");
  }
  while (line_size > -1) {
    line_size = read_line(InputFile, &new_line);
    if (line_size > -1) {
      report_line_match(new_line, &grepArguments, &LinesCounters, line_size);
    }
    free_line(new_line);
  }
  if (grepArguments.report_num_of_matched_lines) {
    printf("%d\n", LinesCounters.num_of_matched_lines_in_file);
  }
  free(grepArguments.PatternToSearch);
  if (InputFile != NULL) {
    fclose(InputFile);
  }
  return 0;
}
