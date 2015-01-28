#ifndef A1TEST_A1TEST_H
#define A1TEST_A1TEST_H

/* File name to use for writing temporary files */
#define TEST_FILENAME "TEMP"

/* Default value to use for PM_create */
#define DEFAULT_CREATE_VAL 10

/* Default character to use as a comment */
#define DEFAULT_COMMENT '#'

/* Maximum difference threshold when comparing REAL_TYPE values */
#define REAL_THRESHOLD 1.0

/*
 * ASSERT
 * A simple macro. Return 1 if cond evaluates to false.
 * Used by test cases to exit if condition is false.
 */
#define ASSERT(cond) if (!(cond)) return 1

/* Test framework methods */
FILE *file_with_contents(char *contents);
void run_test(int (*fn)(), char *fn_name);

/* Main functionality tests */
int test_pm_create_destroy();
int test_pm_create_destroy_twice();

/* PM_manage optional value tests */
int test_pm_manage_int_optional();
int test_pm_manage_real_optional();
int test_pm_manage_boolean_optional();
int test_pm_manage_string_optional();
int test_pm_manage_list_optional();

/* PM_manage required value tests */
int test_pm_manage_int_required();
int test_pm_manage_real_required();
int test_pm_manage_boolean_required();
int test_pm_manage_string_required();
int test_pm_manage_list_required();

/* PM_parseFrom optional value tests */
int test_pm_parse_int_optional();
int test_pm_parse_real_optional();
int test_pm_parse_boolean_optional();
int test_pm_parse_string_optional();
int test_pm_parse_list_optional();
int test_pm_parse_all_optional();

/* PM_parseFrom missing optional value tests */
int test_pm_parse_int_optional_missing();
int test_pm_parse_real_optional_missing();
int test_pm_parse_boolean_optional_missing();
int test_pm_parse_string_optional_missing();
int test_pm_parse_list_optional_missing();
int test_pm_parse_all_optional_missing();

/* PM_parseFrom required value tests */
int test_pm_parse_int_required();
int test_pm_parse_real_required();
int test_pm_parse_boolean_required();
int test_pm_parse_string_required();
int test_pm_parse_list_required();
int test_pm_parse_all_required();

/* Comment tests */
int test_comment();
int test_comment_only();
int test_comment_inline();
int test_comment_multiple();
int test_comment_non_default();
int test_comment_before_semicolon();
int test_comment_before_value();
int test_comment_before_equals();

/* Parse error tests */
int test_parse_error_no_semicolon();
int test_parse_error_no_required_value();
int test_parse_error_no_equals();
int test_parse_error_double_equals();
int test_parse_error_wrong_type();
int test_parse_error_multiple_values();

/* Whitespace tests */
int test_whitespace_more();
int test_whitespace_less();
int test_whitespace_none();
int test_whitespace_multiline();

/* INT_VAL tests */
int test_int_zero();
int test_int_negative();

/* REAL_VAL tests */
int test_real_no_decimal();

#endif  /* A1TEST_A1TEST_H */
