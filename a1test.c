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

void run_test(int (*fn)(), char *fn_name) {
        num_tests++;
        printf("===TEST: %s\n", fn_name);
        if ((*fn)()) {
                num_fail++;
                printf("===FAILURE: %s\n", fn_name);
        } else {
                num_success++;
                printf("===SUCCESS: %s\n", fn_name);
        }
}

int main(int argc, char **argv) {
        run_test(test_create_pm, "test_basic");
        return 0;
}
