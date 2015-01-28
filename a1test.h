#ifndef A1TEST_A1TEST_H
#define A1TEST_A1TEST_H

#define TEST_FILENAME "TEMP"
#define DEFAULT_CREATE_VAL 10
#define DEFAULT_COMMENT '#'
#define REAL_THRESHOLD 1.0

#define ASSERT(cond) if (!(cond)) return 1

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

/* PM_parseFrom required value tests */
int test_pm_parse_int_required();
int test_pm_parse_real_required();
int test_pm_parse_boolean_required();
int test_pm_parse_string_required();
int test_pm_parse_list_required();

#endif  /* A1TEST_A1TEST_H */
