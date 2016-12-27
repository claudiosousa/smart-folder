#include "../src/parser.h"
#include "vendor/cutest.h"
//#define TEST_CHECK_ //

void test_parse_empty()
{
  TEST_CHECK_(parser_parse(NULL, 0) == NULL, "should return null");
}

void test_parse_incomplete()
{
  char *test_argv[] = {"-name"};
  TEST_CHECK_(parser_parse(test_argv, 1) == NULL, "should return null");
}

void test_parse_incorrect()
{
  char *test_argv[] = {"-wrong_arg"};
  TEST_CHECK_(parser_parse(test_argv, 1) == NULL, "should return null");
}

void test_parse_name()
{
  char *test_argv[] = {
      "-name",
      "some_name"};
  parser_t *exact_name_parser = parser_parse(test_argv, 2);
  TEST_CHECK_(exact_name_parser != NULL, "should not return null");
  TEST_CHECK_(exact_name_parser->crit == NAME, "crit should be equal to NAME");
  TEST_CHECK_(strcmp(exact_name_parser->value, test_argv[1]) == 0, "value should be equal to %s", test_argv[1]);
  TEST_CHECK_(exact_name_parser->comp == EXACT, "comp should be equal to EXACT");
}

void test_parse_name_contains()
{
  char *test_argv[] = {
      "-name",
      "-some_name"};
  parser_t *exact_name_parser = parser_parse(test_argv, 2);
  TEST_CHECK_(strcmp(exact_name_parser->value, test_argv[1] + 1) == 0, "value should be equal to %s", test_argv[1] + 1);
  TEST_CHECK_(exact_name_parser->comp == MIN, "comp should be equal to MIN");
}

void test_parse_group()
{
  char *test_argv[] = {
      "-group",
      "some_group"};
  parser_t *exact_name_parser = parser_parse(test_argv, 2);
  TEST_CHECK_(exact_name_parser != NULL, "should not return null");
  TEST_CHECK_(exact_name_parser->crit == GROUP, "crit should be equal to GROUP");
  TEST_CHECK_(strcmp(exact_name_parser->value, test_argv[1]) == 0, "value should be equal to %s", test_argv[1]);
  TEST_CHECK_(exact_name_parser->comp == EXACT, "comp should be equal to EXACT");
}

void test_parse_user()
{
  char *test_argv[] = {
      "-user",
      "some_user"};
  parser_t *exact_name_parser = parser_parse(test_argv, 2);
  TEST_CHECK_(exact_name_parser != NULL, "should not return null");
  TEST_CHECK_(exact_name_parser->crit == USER, "crit should be equal to USER");
  TEST_CHECK_(strcmp(exact_name_parser->value, test_argv[1]) == 0, "value should be equal to %s", test_argv[1]);
  TEST_CHECK_(exact_name_parser->comp == EXACT, "comp should be equal to EXACT");
}

void test_parse_perm()
{
  char *test_argv[] = {
      "-perm",
      "776"};
  parser_t *exact_name_parser = parser_parse(test_argv, 2);
  TEST_CHECK_(exact_name_parser != NULL, "should not return null");
  TEST_CHECK_(exact_name_parser->crit == PERM, "crit should be equal to PERM");
  TEST_CHECK_(exact_name_parser->value == 0776, "value is %d and should be %s", exact_name_parser->value, 0776);
  TEST_CHECK_(exact_name_parser->comp == EXACT, "comp should be equal to EXACT");
}

TEST_LIST = {
    {"parse empty", test_parse_empty},
    {"parse incomplete exp", test_parse_incomplete},
    {"parse incorrect exp", test_parse_incorrect},
    {"parse name", test_parse_name},
    {"parse name contains", test_parse_name_contains},
    {"parse group", test_parse_group},
    {"parse user", test_parse_user},
    {"parse permission", test_parse_perm},
    {0}};

// void main(){
//   test_parse_name();
// }