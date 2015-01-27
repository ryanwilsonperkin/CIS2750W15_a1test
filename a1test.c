#include <stdio.h>
#include "ParameterManager.h"

#define TEST_FILENAME "TEMP"
#define DEFAULT_CREATE_VAL 10

int num_tests = 0;
int num_fail = 0;
int num_success = 0;

int test_pm_create() {
        ParameterManager *pm;
        if (!(pm = PM_create(DEFAULT_CREATE_VAL))) {
                return 1;
        } else {
                return 0;
        }
}

int test_pm_create_twice() {
        ParameterManager *pm1, *pm2;
        if (!(pm1 = PM_create(DEFAULT_CREATE_VAL))) {
                return 1;
        }else if  (!(pm2 = PM_create(DEFAULT_CREATE_VAL))) {
                return 1;
        } else {
                return 0;
        }
}

int test_pm_destroy() {
        ParameterManager *pm;
        pm = PM_create(DEFAULT_CREATE_VAL);
        if (!PM_destroy(pm)) {
                return 1;
        } else {
                return 0;
        }
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
        printf("\n[a1test] Number of tests run: %d\n", num_tests);
        printf("[a1test] Number of successes: %d\n", num_success);
        printf("[a1test] Number of failures: %d\n", num_fail);
        return 0;
}
