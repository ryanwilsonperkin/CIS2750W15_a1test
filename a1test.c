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

int test_comment() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "#Comment\n"
                "name = 1;";
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

int test_comment_only() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "#Comment";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_inline() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1; #Comment";
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

int test_comment_multiple() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1; #Comment #Comment";
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

int test_comment_non_default() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "$Comment\n"
                "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, '$'));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_before_semicolon() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1 #Comment\n"
                ";";
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

int test_comment_before_value() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = #Comment\n"
                "1;";
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

int test_comment_before_equals() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name #Comment\n"
                "= 1;";
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

int test_parse_error_no_semicolon() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_no_required_value() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_no_equals() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_double_equals() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name == 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_wrong_type() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_multiple_values() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1 2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_more() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "   name   =   1   ;";
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

int test_whitespace_less() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1=1;\n"
                "name2=2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT(PM_getValue(pm, "name2").int_val == 2);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_none() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1=1;name2=2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT(PM_getValue(pm, "name2").int_val == 2);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_multiline() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name =\n"
                "\n     "
                "1;";
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

int test_int_zero() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 0;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_int_negative() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = -1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == -1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_real_no_decimal() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 3;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT((PM_getValue(pm, "name").real_val - 3) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_boolean_false() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = false;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").bool_val == false);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_spaces() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"   string   \";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "   string   ") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_line_break() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"string\nmore\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "string\nmore") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_single_quotes() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"'string'\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "'string'") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_number() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"123\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "123") == 0);
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

        /* Comment tests */
        run_test(test_comment, "test_comment");
        run_test(test_comment_only, "test_comment_only");
        run_test(test_comment_inline, "test_comment_inline");
        run_test(test_comment_multiple, "test_comment_multiple");
        run_test(test_comment_before_semicolon, "test_comment_before_semicolon");
        run_test(test_comment_before_value, "test_comment_before_value");
        run_test(test_comment_before_value, "test_comment_before_value");

        /* Parse error tests */
        run_test(test_parse_error_no_semicolon, "test_parse_error_no_semicolon");
        run_test(test_parse_error_no_required_value, "test_parse_error_no_required_value");
        run_test(test_parse_error_no_equals, "test_parse_error_no_equals");
        run_test(test_parse_error_double_equals, "test_parse_error_double_equals");
        run_test(test_parse_error_wrong_type, "test_parse_error_wrong_type");
        run_test(test_parse_error_multiple_values, "test_parse_error_multiple_values");

        /* Whitespace tests */
        run_test(test_whitespace_more, "test_whitespace_more");
        run_test(test_whitespace_less, "test_whitespace_less");
        run_test(test_whitespace_none, "test_whitespace_none");
        run_test(test_whitespace_multiline, "test_whitespace_multiline");
        
        /* INT_TYPE tests */
        run_test(test_int_zero, "test_int_zero");
        run_test(test_int_negative, "test_int_negative");

        /* REAL_TYPE tests */
        run_test(test_real_no_decimal, "test_real_no_decimal");

        /* BOOLEAN_TYPE tests */
        run_test(test_boolean_false, "test_boolean_false");

        /* STRING_TYPE tests */
        run_test(test_string_spaces, "test_string_spaces");
        run_test(test_string_line_break, "test_string_line_break");
        run_test(test_string_single_quotes, "test_string_single_quotes");
        run_test(test_string_number, "test_string_number");

        printf("\n[a1test] Number of tests run: %d\n", num_tests);
        printf("[a1test] Number of successes: %d\n", num_success);
        printf("[a1test] Number of failures: %d\n", num_fail);
        return 0;
}
