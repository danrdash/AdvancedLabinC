#include "IO.h"

int read_line(FILE *InputFile, char *new_line[])
{
  int line_size = 0;
  size_t n = 0;
  if (InputFile != NULL) {
    line_size = getline(new_line, &n, InputFile);
  } else {
    line_size = getline(new_line, &n, stdin);
  }
  return line_size;
}

void print_line(char *line, grepArguments *grepArguments, LinesCounters *LinesCounters, bool is_match_in_line)
{
  if (grepArguments->print_NUM_of_lines_after_match && LinesCounters->num_of_lines_to_print_after_match == 0) {
    printf("--\n");
  }
  if (grepArguments->print_line_num) {
    if (is_match_in_line) {
      printf("%d:", LinesCounters->num_of_lines_in_file);
    } else {
      printf("%d-", LinesCounters->num_of_lines_in_file);
    }
  }
  if (grepArguments->print_line_offset) {
    if (is_match_in_line) {
      printf("%d:", LinesCounters->offset_from_start_of_InputFile);
    } else {
      printf("%d-", LinesCounters->offset_from_start_of_InputFile);
    }
  }
  printf("%s", line);
}
