#include <stdio.h>
#include "ParameterManager.h"

#define TEST_FILENAME "TEMP"

int num_tests = 0;
int num_fail = 0;
int num_success = 0;

int test_create_pm() {
        ParameterManager *pm;
        if (!(pm = PM_create(10))) {
                return 1;
        } else {
                return 0;
        }
}

int test_create_pm_twice() {
        ParameterManager *pm1, *pm2;
        if (!(pm1 = PM_create(10))) {
                return 1;
        }else if  (!(pm2 = PM_create(10))) {
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
        run_test(test_create_pm, "test_create_pm");
        run_test(test_create_pm_twice, "test_create_pm_twice");
        printf("\n[a1test] Number of tests run: %d\n", num_tests);
        printf("[a1test] Number of successes: %d\n", num_success);
        printf("[a1test] Number of failures: %d\n", num_fail);
        return 0;
}
