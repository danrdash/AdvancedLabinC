#include "grep_parser.h"
#include <stdlib.h>
#include <string.h>

void init_grepArguments_values(grepArguments *grepArguments)
{
  grepArguments->ignore_case_sensitive = false;
  grepArguments->invers_grep = false;
  grepArguments->report_num_of_matched_lines = false;
  grepArguments->print_line_num = false;
  grepArguments->print_line_offset = false;
  grepArguments->tighted_match = false;
  grepArguments->print_NUM_of_lines_after_match = false;
  grepArguments->NUM_of_lines = 0;
  grepArguments->PatternToSearch = NULL;
  grepArguments->InputFile_path = NULL;
}

void update_REGULAR_Data(Character *character, const char *pattern)
{
  character->type = REGULAR;
  character->info.REGULAR_Data = *pattern;
}

void init_PARENTHESES_Data(PARENTHESES_Data *data)
{
  data->start_of_PARENTHESES_Data = false;
  data->pip = false;
  data->end_of_PARENTHESES_Data = false;
}

void update_PARENTHESES_Data(PARENTHESES_Data *data, const char *pattern_charater)
{
  init_PARENTHESES_Data(data);
  if (*pattern_charater == '(') {
    data->start_of_PARENTHESES_Data = true;
  } else if (*pattern_charater == '|') {
    data->pip = true;
  } else if (*pattern_charater == ')') {
    data->end_of_PARENTHESES_Data = true;
  }
}
void update_SQUARE_BRACKETS_Data(SQUARE_BRACKETS_Data *data, const char *pattern_to_parse, int *pattern_to_parse_index)
{
  *pattern_to_parse_index += 1;
  data->bottom_border = (char)pattern_to_parse[*pattern_to_parse_index];
  *pattern_to_parse_index += 2;
  data->upper_border = (char)pattern_to_parse[*pattern_to_parse_index];
  *pattern_to_parse_index += 1;
}

Character *Pattern_Parse(Character *PatternToSearch, char *pattern_to_parse)
{
  PatternToSearch = (Character *)malloc(sizeof(Character) * (strlen(pattern_to_parse) + 1));
  int PatternToSearch_index = 0, pattern_to_parse_index = 0;
  union Character_info *character_info;
  for (; pattern_to_parse_index < (int)strlen(pattern_to_parse); pattern_to_parse_index++) {
    character_info = &PatternToSearch[PatternToSearch_index].info;
    if (pattern_to_parse[pattern_to_parse_index] == '.') {
      PatternToSearch[PatternToSearch_index].type = DOT;
    } else if ((pattern_to_parse[pattern_to_parse_index] == '(') | (pattern_to_parse[pattern_to_parse_index] == '|') |
               (pattern_to_parse[pattern_to_parse_index] == ')')) {
      PatternToSearch[PatternToSearch_index].type = PARENTHESES;
      update_PARENTHESES_Data(&character_info->PARENTHESES_Data, &pattern_to_parse[pattern_to_parse_index]);
    } else if (pattern_to_parse[pattern_to_parse_index] == '[') {
      PatternToSearch[PatternToSearch_index].type = SQUARE_BRACKETS;
      update_SQUARE_BRACKETS_Data(&character_info->SQUARE_BRACKETS_Data, pattern_to_parse, &pattern_to_parse_index);
    } else {
      if (pattern_to_parse[pattern_to_parse_index] == '\\') {
        pattern_to_parse_index++;
      }
      update_REGULAR_Data(&PatternToSearch[PatternToSearch_index], &pattern_to_parse[pattern_to_parse_index]);
    }
    PatternToSearch_index++;
  }
  PatternToSearch[PatternToSearch_index].type = END_OF_PATTERN;
  return PatternToSearch;
}

void update_grepArguments(grepArguments *grepArguments, int argc, char *argv[])
{
  init_grepArguments_values(grepArguments);
  int index = 1;
  for (; index < argc; index++) {
    if (!strcmp(argv[index], "-i")) {
      grepArguments->ignore_case_sensitive = true;
    } else if (!strcmp(argv[index], "-v")) {
      grepArguments->invers_grep = true;
    } else if (!strcmp(argv[index], "-c")) {
      grepArguments->report_num_of_matched_lines = true;
    } else if (!strcmp(argv[index], "-n")) {
      grepArguments->print_line_num = true;
    } else if (!strcmp(argv[index], "-b")) {
      grepArguments->print_line_offset = true;
    } else if (!strcmp(argv[index], "-x")) {
      grepArguments->tighted_match = true;
    } else if (!strcmp(argv[index], "-A")) {
      grepArguments->print_NUM_of_lines_after_match = true;
      index++;
      grepArguments->NUM_of_lines = *argv[index] - '0';
    } else if (!strcmp(argv[index], "-E")) {
      continue;
    } else if (grepArguments->PatternToSearch == NULL) {
      grepArguments->PatternToSearch = Pattern_Parse(grepArguments->PatternToSearch, argv[index]);
    } else {
      grepArguments->InputFile_path = argv[index];
    }
  }
}
