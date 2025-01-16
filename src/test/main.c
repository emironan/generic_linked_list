#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include "linked_list.h"

/* This struct is created to be used in tests. */
typedef struct __attribute__((packed)) st_employee_t
{
    int age;
    const char* name;
} employee_t;

/* Print Function to use as callback function in ll_print_all_list */
void print_employee_info(void * employee);

/* Compare Function to use as callback function in ll_get_index_of_eq_data */
int is_equal(void * data1, void * data2);

/* Created to be used in tests. */
linked_list_t list;
employee_t employee;

void tcase_fill_list_setup(void)
{
    list = ll_create_linked_list();

    employee.name = "Ahmet";
    employee.age = 24;
    ll_add_tail(list, &employee, sizeof(employee_t));

    employee.name = "Emir";
    employee.age = 28;
    ll_add_tail(list, &employee, sizeof(employee_t));

    employee.name = "Serkan";
    employee.age = 54;
    ll_add_tail(list, &employee, sizeof(employee_t));

    employee.name = "Veli";
    employee.age = 21;
    ll_add_head(list, &employee, sizeof(employee_t));
}

void tcase_default_teardown(void)
{
    ll_delete_linked_list(list);
}

/********************************** ADD TEST *********************************/
/* Just for creating an empty list*/
void tcase_add_setup(void)
{
    list = ll_create_linked_list();
}

START_TEST(test_add_tail)
{
    /* Adds an employee to the list and checks if it is added correctly. */
    employee.name = "Ahmet";
    employee.age = 24;
    ll_add_tail(list, &employee, sizeof(employee_t));

    employee.name = "";
    employee.age = 0;

    ll_get_tail(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Ahmet");
    ck_assert_int_eq(employee.age, 24);

    /* Adds an employee to the list and checks if it is added correctly. */
    employee.name = "Emir";
    employee.age = 28;
    ll_add_tail(list, &employee, sizeof(employee_t));

    employee.name = "";
    employee.age = 0;

    ll_get_tail(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Emir");
    ck_assert_int_eq(employee.age, 28);

    /* Adds an employee to the list and checks if it is added correctly. */
    employee.name = "Serkan";
    employee.age = 36;
    ll_add_tail(list, &employee, sizeof(employee_t));

    employee.name = "";
    employee.age = 0;

    ll_get_tail(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Serkan");
    ck_assert_int_eq(employee.age, 36);
}
END_TEST

START_TEST(test_add_head)
{
    /* Adds an employee to the list and checks if it is added correctly. */
    employee.name = "Ahmet";
    employee.age = 24;
    ll_add_head(list, &employee, sizeof(employee_t));

    employee.name = "";
    employee.age = 0;

    ll_get_head(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Ahmet");
    ck_assert_int_eq(employee.age, 24);

    /* Adds an employee to the list and checks if it is added correctly. */
    employee.name = "Emir";
    employee.age = 28;
    ll_add_head(list, &employee, sizeof(employee_t));

    employee.name = "";
    employee.age = 0;

    ll_get_head(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Emir");
    ck_assert_int_eq(employee.age, 28);

    /* Adds an employee to the list and checks if it is added correctly. */
    employee.name = "Serkan";
    employee.age = 36;
    ll_add_head(list, &employee, sizeof(employee_t));

    employee.name = "";
    employee.age = 0;

    ll_get_head(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Serkan");
    ck_assert_int_eq(employee.age, 36);
}
END_TEST

/********************************** GET TEST *********************************/
START_TEST(test_get_tail)
{
    ll_get_tail(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Serkan");
    ck_assert_int_eq(employee.age, 54);
}
END_TEST

START_TEST(test_get_head)
{
    ll_get_head(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Veli");
    ck_assert_int_eq(employee.age, 21);
}
END_TEST

START_TEST(test_get_with_index)
{
    linked_list_errors_t error = ll_get_item_with_index(list, (int)2, &employee, sizeof(employee_t));

    /* No error returned */
    ck_assert_int_eq((int)error, (int)LL_ERROR_NONE);

    ck_assert_str_eq(employee.name, "Emir");
    ck_assert_int_eq(employee.age, 28);

    /* index 8 is out of bounds of list, should return error. */
    error = ll_get_item_with_index(list, (int)8, &employee, sizeof(employee_t));

    ck_assert_int_eq((int)error, (int)LL_ERROR_INDEX_OUT_OF_BOUNDS);

}
END_TEST

START_TEST(test_get_index_with_compare_func)
{
    employee.name = "Veli";
    int result = ll_get_index_of_eq_data(list, &employee, is_equal);
    ck_assert_int_eq(result, (int)0);

    employee.name = "Ali";
    result = ll_get_index_of_eq_data(list, &employee, is_equal);
    ck_assert_int_eq(result, (int)-1);
}
END_TEST

/********************************** Pop TEST *********************************/
START_TEST(test_pop_tail)
{
    ll_pop_tail(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Serkan");
    ck_assert_int_eq(employee.age, 54);

    ll_get_tail(list, &employee, sizeof(employee_t));
    ck_assert_str_eq(employee.name, "Emir");
    ck_assert_int_eq(employee.age, 28);
}
END_TEST

START_TEST(test_pop_head)
{
    ll_pop_head(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Veli");
    ck_assert_int_eq(employee.age, 21);

    ll_get_head(list, &employee, sizeof(employee_t));
    ck_assert_str_eq(employee.name, "Ahmet");
    ck_assert_int_eq(employee.age, 24);
}
END_TEST

/*************************** Return List Size TEST ***************************/
START_TEST(test_return_list_size)
{
    ll_print_all_list(list, print_employee_info);
    int list_size = ll_return_list_size(list);
    ck_assert_int_eq(list_size, 4);
}
END_TEST

/*************************** Remove List Size TEST ***************************/
START_TEST(test_remove_tail)
{
    ll_remove_tail(list);
    ll_get_tail(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Emir");
    ck_assert_int_eq(employee.age, 28);
}
END_TEST

START_TEST(test_remove_head)
{
    ll_remove_head(list);
    ll_get_head(list, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Ahmet");
    ck_assert_int_eq(employee.age, 24);
}
END_TEST

START_TEST(test_remove_with_index)
{
    ll_remove_with_index(list, 1);
    ll_get_item_with_index(list, 1, &employee, sizeof(employee_t));

    ck_assert_str_eq(employee.name, "Emir");
    ck_assert_int_eq(employee.age, 28);
}
END_TEST

Suite * linked_list_suite(void)
{
    Suite *s;

    s = suite_create("Generic Linked List");

    /* Add Functions' tests */
    TCase *tc_add;
    tc_add = tcase_create("Add Tests");
    tcase_add_checked_fixture(tc_add, tcase_add_setup, tcase_default_teardown);
    tcase_add_test(tc_add, test_add_tail);
    tcase_add_test(tc_add, test_add_head);
    suite_add_tcase(s, tc_add);

    /* Get Functions' tests */
    TCase *tc_get;
    tc_get = tcase_create("Get Tests");
    tcase_add_checked_fixture(tc_get, tcase_fill_list_setup, tcase_default_teardown);
    tcase_add_test(tc_get, test_get_tail);
    tcase_add_test(tc_get, test_get_head);
    tcase_add_test(tc_get, test_get_with_index);
    tcase_add_test(tc_get, test_get_index_with_compare_func);
    suite_add_tcase(s, tc_get);

    /* Pop Functions' tests */
    TCase *tc_pop;
    tc_pop = tcase_create("Pop Tests");
    tcase_add_checked_fixture(tc_pop, tcase_fill_list_setup, tcase_default_teardown);
    tcase_add_test(tc_pop, test_pop_tail);
    tcase_add_test(tc_pop, test_pop_head);
    suite_add_tcase(s, tc_pop);

    /* Return List Size test */
    TCase *tc_return_size;
    tc_return_size = tcase_create("Pop Tests");
    tcase_add_checked_fixture(tc_return_size, tcase_fill_list_setup, tcase_default_teardown);
    tcase_add_test(tc_return_size, test_return_list_size);
    suite_add_tcase(s, tc_return_size);

    /* Remove Functions' tests */
    TCase *tc_remove;
    tc_remove = tcase_create("Remove Tests");
    tcase_add_checked_fixture(tc_remove, tcase_fill_list_setup, tcase_default_teardown);
    tcase_add_test(tc_remove, test_remove_tail);
    tcase_add_test(tc_remove, test_remove_head);
    tcase_add_test(tc_remove, test_remove_with_index);
    suite_add_tcase(s, tc_remove);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = linked_list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*****************************************************************************/
void print_employee_info(void* employee)
{
    printf("Employee name is : %s\n", ((employee_t *) employee)->name);
    printf("Employee age is : %d\n", ((employee_t *) employee)->age);
}

/*****************************************************************************/
int is_equal(void* data1, void* data2)
{
    const char * s1 = ((employee_t *) data1)->name;
    const char * s2 = ((employee_t *) data2)->name;

    return strcmp(((employee_t *) data1)->name, ((employee_t *) data2)->name);
}

/*****************************************************************************/