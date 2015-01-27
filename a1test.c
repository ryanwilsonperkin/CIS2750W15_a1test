#include <stdio.h>
#include "ParameterManager.h"
#include "a1test.h"

int num_tests = 0;
int num_fail = 0;
int num_success = 0;

int test_pm_create() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        return 0;
}

int test_pm_create_twice() {
        ParameterManager *pm1, *pm2;
        ASSERT(pm1 = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(pm2 = PM_create(DEFAULT_CREATE_VAL));
        return 0;
}

int test_pm_destroy() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_int_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        return 0;
}

int test_pm_manage_int_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        return 0;
}

int test_pm_manage_real_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        return 0;
}

int test_pm_manage_real_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        return 0;
}

int test_pm_manage_boolean_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        return 0;
}

int test_pm_manage_boolean_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        return 0;
}

int test_pm_manage_string_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        return 0;
}

int test_pm_manage_string_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        return 0;
}

int test_pm_manage_list_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        return 0;
}

int test_pm_manage_list_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
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
        run_test(test_pm_create, "test_pm_create");
        run_test(test_pm_create_twice, "test_pm_create_twice");
        run_test(test_pm_destroy, "test_pm_destroy");
        run_test(test_pm_manage_int_optional, "test_pm_manage_int_optional");
        run_test(test_pm_manage_int_required, "test_pm_manage_int_required");
        run_test(test_pm_manage_real_optional, "test_pm_manage_real_optional");
        run_test(test_pm_manage_real_required, "test_pm_manage_real_required");
        run_test(test_pm_manage_boolean_optional, "test_pm_manage_boolean_optional");
        run_test(test_pm_manage_boolean_required, "test_pm_manage_boolean_required");
        run_test(test_pm_manage_string_optional, "test_pm_manage_string_optional");
        run_test(test_pm_manage_string_required, "test_pm_manage_string_required");
        run_test(test_pm_manage_list_optional, "test_pm_manage_list_optional");
        run_test(test_pm_manage_list_required, "test_pm_manage_list_required");
        printf("\n[a1test] Number of tests run: %d\n", num_tests);
        printf("[a1test] Number of successes: %d\n", num_success);
        printf("[a1test] Number of failures: %d\n", num_fail);
        return 0;
}
