#ifndef GREP_PARSER_H
#define GREP_PARSER_H

#include <stdbool.h>

enum Character_Type {
  END_OF_PATTERN = 0,
  REGULAR,
  DOT,
  PARENTHESES,
  SQUARE_BRACKETS,
};

typedef struct PARENTHESES_Data {
  bool start_of_PARENTHESES_Data;
  bool pip;
  bool end_of_PARENTHESES_Data;
} PARENTHESES_Data;

typedef struct SQUARE_BRACKETS_Data {
  char bottom_border;
  char upper_border;
} SQUARE_BRACKETS_Data;

union Character_info {
  char REGULAR_Data;
  PARENTHESES_Data PARENTHESES_Data;
  SQUARE_BRACKETS_Data SQUARE_BRACKETS_Data;
};

typedef struct Character {
  enum Character_Type type;
  union Character_info info;
} Character;

typedef struct grepArguments {
  bool ignore_case_sensitive;
  bool invers_grep;
  bool report_num_of_matched_lines;
  bool print_line_num;
  bool print_line_offset;
  bool tighted_match;
  bool print_NUM_of_lines_after_match;
  int NUM_of_lines;
  Character *PatternToSearch;
  char *InputFile_path;
} grepArguments;

void update_grepArguments(grepArguments *grepArguments, int argc, char *argv[]);

#endif
