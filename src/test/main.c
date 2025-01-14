#include <stdio.h>
#include <stdint.h>
#include "linked_list.h"

typedef struct __attribute__((packed)) st_employee_t
{
    int age;
    const char* name;
} employee_t;

void print_employee_info(void * employee);

int main(void)
{
    printf("*********************** Linked List Project ***********************\n\n");

    employee_t employee;

    linked_list_t list = ll_create_linked_list();

    printf("Size of my data type = %ld\n", sizeof(employee_t));

    printf("Size of list is = %d\n", ll_return_list_size(list));

    employee.name = "Ahmed";
    employee.age = 32;
    ll_add_to_end(list, &employee, sizeof(employee_t));

    employee.name = "Ali";
    employee.age = 22;
    ll_add_to_end(list, &employee, sizeof(employee_t));

    employee.name = "Serkan";
    employee.age = 43;
    ll_add_to_end(list, &employee, sizeof(employee_t));

    employee.name = "Veli";
    employee.age = 56;
    ll_add_to_end(list, &employee, sizeof(employee_t));

    employee.name = "Emir";
    employee.age = 28;    
    ll_add_to_beginning(list, &employee, sizeof(employee_t));

    ll_print_all_list(list, print_employee_info);

    printf("Size of list is = %d\n", ll_return_list_size(list));

    printf("Info of the employee at index %d:\n", 2);

    ll_get_item_with_index(list, 2, &employee, sizeof(employee_t));

    print_employee_info((void*) &employee);

    ll_delete_linked_list(list);

    printf("*******************************************************************\n\n");
    return 0;
}

void print_employee_info(void* employee)
{
    printf("Employee name is : %s\n", ((employee_t *) employee)->name);
    printf("Employee age is : %d\n", ((employee_t *) employee)->age);
}