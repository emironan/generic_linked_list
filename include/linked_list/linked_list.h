/******************************************************************************
 * File: linked_list.h
 * Author: Emir
 * Date: 10.01.2025
 * Description: generic linked list source file
 * Details:
 * Version: 1
 *****************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct st_node_t* linked_list_t;

typedef enum e_linked_list_errors_t
{
    LL_ERROR_NONE = 0,
    LL_ERROR_ALLOCATION,
    LL_ERROR_INDEX_OUT_OF_BOUNDS,
} linked_list_errors_t;

/*****************************************************************************/
/*
    This is creating a new linked list
*/
linked_list_t ll_create_linked_list(void);

/*****************************************************************************/
/*
    Freeing the memory
*/
void ll_delete_linked_list(linked_list_t list);

/*****************************************************************************/
/**
 * @brief Adds the at the end of the list.
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[in] data [void *] data to add
 * @param[in] data_size [size_t] size of the data
 * @return [linked_list_errors_t] returns LL_ERROR_ALLOCATION if can't take
 * memory from OS. Otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_add_to_end(linked_list_t list,
                                   void* data,
                                   size_t data_size);

/*****************************************************************************/
/**
 * @brief Adds the at the beginning of the list.
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[in] data [void *] data to add
 * @param[in] data_size [size_t] size of the data
 * @return [linked_list_errors_t] returns LL_ERROR_ALLOCATION if can't take
 * memory from OS. Otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_add_to_beginning(linked_list_t list,
                                         void* data,
                                         size_t data_size);

/*****************************************************************************/
/**
 * @brief returns size of linked list
 * @param[in] list [linked_list_t] the list to operator upon
 * @return [int] returns the size of list
 */
int ll_return_list_size(linked_list_t list);

/*****************************************************************************/
/**
 * @brief Get the item at the index given, not returning the pointer,
 * this function copies the data to given pointers memory area
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[in] index [int] index of the wanted item in given list
 * @param[out] data [void *] copies data to this memory location
 * @param[in] data_size [size_t] size of the data
 * @return [linked_list_errors_t] returns LL_ERROR_NONE if given index 
 * is not out of bounds
 */
linked_list_errors_t ll_get_item_with_index(linked_list_t list, 
                                            int index, 
                                            void* data,
                                            size_t data_size);

/*****************************************************************************/

/**
 * @brief Prints all list using given print function from head to tail
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[in] print_function [void (print_function)(void *)] print function
 * @return [void]
 */
void ll_print_all_list(linked_list_t list, void (print_function)(void *));

/*****************************************************************************/


#endif // LINKED_LIST_H