#include <stdio.h>
#include <string.h>
#include "ParameterManager.h"
#include "a1test.h"

int num_tests = 0;
int num_fail = 0;
int num_success = 0;

int test_pm_create_destroy() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_create_destroy_twice() {
        ParameterManager *pm1, *pm2;
        ASSERT(pm1 = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(pm2 = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_destroy(pm1));
        ASSERT(PM_destroy(pm2));
        return 0;
}

int test_pm_manage_int_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_real_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_boolean_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_string_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_list_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_int_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_real_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_boolean_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_string_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_list_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_parse_int_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_real_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 3.3;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT((PM_getValue(pm, "name").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_boolean_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = true;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").bool_val == true);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_string_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"string\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_list_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_all_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = 1;\n"
                "name2 = 3.3;\n"
                "name3 = true;\n"
                "name4 = \"string\";\n"
                "name5 = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 0));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 0));
        ASSERT(PM_manage(pm, "name3", BOOLEAN_TYPE, 0));
        ASSERT(PM_manage(pm, "name4", STRING_TYPE, 0));
        ASSERT(PM_manage(pm, "name5", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_hasValue(pm, "name3"));
        ASSERT(PM_hasValue(pm, "name4"));
        ASSERT(PM_hasValue(pm, "name5"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT((PM_getValue(pm, "name2").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_getValue(pm, "name3").bool_val == true);
        ASSERT(PM_getValue(pm, "name4").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name4").str_val, "string") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name5").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_int_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_real_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_boolean_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_string_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_list_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_all_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 0));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 0));
        ASSERT(PM_manage(pm, "name3", BOOLEAN_TYPE, 0));
        ASSERT(PM_manage(pm, "name4", STRING_TYPE, 0));
        ASSERT(PM_manage(pm, "name5", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name1"));
        ASSERT(!PM_hasValue(pm, "name2"));
        ASSERT(!PM_hasValue(pm, "name3"));
        ASSERT(!PM_hasValue(pm, "name4"));
        ASSERT(!PM_hasValue(pm, "name5"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_int_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_real_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 3.3;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT((PM_getValue(pm, "name").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_boolean_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = true;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").bool_val == true);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_string_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"string\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_list_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_all_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = 1;\n"
                "name2 = 3.3;\n"
                "name3 = true;\n"
                "name4 = \"string\";\n"
                "name5 = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 1));
        ASSERT(PM_manage(pm, "name3", BOOLEAN_TYPE, 1));
        ASSERT(PM_manage(pm, "name4", STRING_TYPE, 1));
        ASSERT(PM_manage(pm, "name5", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_hasValue(pm, "name3"));
        ASSERT(PM_hasValue(pm, "name4"));
        ASSERT(PM_hasValue(pm, "name5"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT((PM_getValue(pm, "name2").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_getValue(pm, "name3").bool_val == true);
        ASSERT(PM_getValue(pm, "name4").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name4").str_val, "string") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name5").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

FILE *file_with_contents(char *contents) {
        FILE *fp = fopen(TEST_FILENAME, "w");
        fprintf(fp, contents);
        fclose(fp);
        return fopen(TEST_FILENAME, "r");
}

void run_test(int (*fn)(), char *fn_name) {
        num_tests++;
        printf("\n[a1test][TEST]: %s\n", fn_name);
        if ((*fn)()) {
                num_fail++;
                printf("\n[a1test][FAILURE]: %s\n", fn_name);
        } else {
                num_success++;
                printf("\n[a1test][SUCCESS]: %s\n", fn_name);
        }
}

int main(int argc, char **argv) {
        /* Main functionality tests */
        run_test(test_pm_create_destroy, "test_pm_create_destroy");
        run_test(test_pm_create_destroy_twice, "test_pm_create_destroy_twice");

        /* PM_manage optional value tests */
        run_test(test_pm_manage_int_optional, "test_pm_manage_int_optional");
        run_test(test_pm_manage_real_optional, "test_pm_manage_real_optional");
        run_test(test_pm_manage_boolean_optional, "test_pm_manage_boolean_optional");
        run_test(test_pm_manage_string_optional, "test_pm_manage_string_optional");
        run_test(test_pm_manage_list_optional, "test_pm_manage_list_optional");

        /* PM_manage required value tests */
        run_test(test_pm_manage_int_required, "test_pm_manage_int_required");
        run_test(test_pm_manage_real_required, "test_pm_manage_real_required");
        run_test(test_pm_manage_boolean_required, "test_pm_manage_boolean_required");
        run_test(test_pm_manage_string_required, "test_pm_manage_string_required");
        run_test(test_pm_manage_list_required, "test_pm_manage_list_required");

        /* PM_parseFrom optional value tests */
        run_test(test_pm_parse_int_optional, "test_pm_parse_int_optional");
        run_test(test_pm_parse_real_optional, "test_pm_parse_real_optional");
        run_test(test_pm_parse_boolean_optional, "test_pm_parse_boolean_optional");
        run_test(test_pm_parse_string_optional, "test_pm_parse_string_optional");
        run_test(test_pm_parse_list_optional, "test_pm_parse_list_optional");
        run_test(test_pm_parse_all_optional, "test_pm_parse_all_optional");

        /* PM_parseFrom missing optional value tests */
        run_test(test_pm_parse_int_optional_missing, "test_pm_parse_int_optional_missing");
        run_test(test_pm_parse_real_optional_missing, "test_pm_parse_real_optional_missing");
        run_test(test_pm_parse_boolean_optional_missing, "test_pm_parse_boolean_optional_missing");
        run_test(test_pm_parse_string_optional_missing, "test_pm_parse_string_optional_missing");
        run_test(test_pm_parse_list_optional_missing, "test_pm_parse_list_optional_missing");
        run_test(test_pm_parse_all_optional_missing, "test_pm_parse_all_optional_missing");

        /* PM_parseFrom required value tests */
        run_test(test_pm_parse_int_required, "test_pm_parse_int_required");
        run_test(test_pm_parse_real_required, "test_pm_parse_real_required");
        run_test(test_pm_parse_boolean_required, "test_pm_parse_boolean_required");
        run_test(test_pm_parse_string_required, "test_pm_parse_string_required");
        run_test(test_pm_parse_list_required, "test_pm_parse_list_required");
        run_test(test_pm_parse_all_required, "test_pm_parse_all_required");

        printf("\n[a1test] Number of tests run: %d\n", num_tests);
        printf("[a1test] Number of successes: %d\n", num_success);
        printf("[a1test] Number of failures: %d\n", num_fail);
        return 0;
}
