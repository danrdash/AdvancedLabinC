#include "grep_matching_line.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool is_match_at_place(char *line, Character *PatternToSearch, bool is_tighted_match);

void lowercase_string(char *string)
{
  int i = 0;
  for (; string[i] != '\0'; i++) {
    string[i] = tolower(string[i]);
  }
}

void lowercase_PatternToSearch(Character *PatternToSearch)
{
  int character_index = 0;
  while (PatternToSearch[character_index].type != END_OF_PATTERN) {
    if (PatternToSearch[character_index].type == REGULAR) {
      PatternToSearch[character_index].info.REGULAR_Data = tolower(PatternToSearch[character_index].info.REGULAR_Data);
    }
    character_index++;
  }
}

bool is_match_regular_case(char *line, char *data) { return !strncmp(line, data, 1); }

bool is_match_parentheses_case(char *line, Character *PatternToSearch, bool is_tighted_match)
{
  PARENTHESES_Data *data = &PatternToSearch[0].info.PARENTHESES_Data;
  bool is_match_first_string = false, is_match_second_string = false;
  int PatternToSearch_index = 1;
  if (data->pip) {
    while (PatternToSearch[PatternToSearch_index].type != PARENTHESES) {
      PatternToSearch_index++;
    }
    PatternToSearch_index++;
    return is_match_at_place(line, &PatternToSearch[PatternToSearch_index], is_tighted_match);
  }
  if (data->end_of_PARENTHESES_Data) {
    return is_match_at_place(line, &PatternToSearch[PatternToSearch_index], is_tighted_match);
  }
  is_match_first_string = is_match_at_place(line, &PatternToSearch[PatternToSearch_index], is_tighted_match);
  while (PatternToSearch[PatternToSearch_index].type != PARENTHESES) {
    PatternToSearch_index++;
  }
  PatternToSearch_index++;
  is_match_second_string = is_match_at_place(line, &PatternToSearch[PatternToSearch_index], is_tighted_match);
  return is_match_first_string | is_match_second_string;
}

bool is_match_in_range(const char *line, SQUARE_BRACKETS_Data *data)
{
  return (data->bottom_border <= line[0] && line[0] <= data->upper_border);
}

bool is_match_at_place(char *line, Character *PatternToSearch, bool is_tighted_match)
{
  int line_next_index = 1;
  if (PatternToSearch[0].type == END_OF_PATTERN) {
    if (is_tighted_match && strncmp(line, "\n", 1) != 0) {
      return false;
    }
    return true;
  }
  if (PatternToSearch[0].type == REGULAR) {
    if (is_match_regular_case(line, &PatternToSearch[0].info.REGULAR_Data)) {
      return is_match_at_place(&line[line_next_index], &PatternToSearch[1], is_tighted_match);
    }
  } else if (PatternToSearch[0].type == DOT) {
    return is_match_at_place(&line[line_next_index], &PatternToSearch[1], is_tighted_match);
  } else if (PatternToSearch[0].type == PARENTHESES) {
    return is_match_parentheses_case(line, PatternToSearch, is_tighted_match);
  } else if (PatternToSearch[0].type == SQUARE_BRACKETS) {
    if (is_match_in_range(line, &PatternToSearch[0].info.SQUARE_BRACKETS_Data)) {
      return is_match_at_place(&line[line_next_index], &PatternToSearch[1], is_tighted_match);
    }
  }
  return false;
}

bool is_match_in_line(const char *new_line, grepArguments *grepArguments)
{
  bool is_match = false;
  char *copied_line = (char *)malloc(sizeof(char) * strlen(new_line) + 1);
  int place_at_line = 0;
  strcpy(copied_line, new_line);
  if (grepArguments->ignore_case_sensitive) {
    lowercase_PatternToSearch(grepArguments->PatternToSearch);
    lowercase_string(copied_line);
  }
  while (is_match == false && strcmp(&copied_line[place_at_line], "\n") != 0) {
    is_match =
        is_match_at_place(&copied_line[place_at_line], grepArguments->PatternToSearch, grepArguments->tighted_match);
    place_at_line++;
    if (grepArguments->tighted_match) {
      break;
    }
  }
  if (grepArguments->invers_grep) {
    is_match = is_match ? false : true;
  }
  free(copied_line);
  return is_match;
}

bool is_print_line_without_match(grepArguments *grepArguments, LinesCounters *LinesCounters)
{
  return (grepArguments->print_NUM_of_lines_after_match && LinesCounters->num_of_lines_to_print_after_match > 0);
}
