/******************************************************************************
 * File: linked_list.h
 * Author: Emir
 * Date: 10.01.2025
 * Description: generic linked list header file
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
    LL_ERROR_LIST_ALREADY_EMPTY
} linked_list_errors_t;

/*****************************************************************************/
/**
 * @brief Creates a new linked list and returns the beginning address of it.
 * @return [linked_list_t] Created linked list
 */
linked_list_t ll_create_linked_list(void);

/*****************************************************************************/
/**
 * @brief Deletes all list iterating through all list
 * @param[in] list [linked_list_t] the list to operator upon
 * @return [void] 
 */
void ll_delete_linked_list(linked_list_t list);

/*****************************************************************************/
/**
 * @brief Adds data to the end of the list.
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
 * @brief Adds data to the beginning of the list.
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
 * @brief Pops data from end of the list
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[out] data [void *] the data pointer to return data
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_pop_from_end(linked_list_t list, 
                                     void* data,
                                     size_t data_size);

/*****************************************************************************/
/**
 * @brief Pops data from beginning of the list
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[out] data [void *] the data pointer to return data
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_pop_from_beginning(linked_list_t list, 
                                           void* data,
                                           size_t data_size);

/*****************************************************************************/
/**
 * @brief Gets data from end of the list
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[out] data [void *] the data pointer to return data
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_get_from_end(linked_list_t list, 
                                     void* data,
                                     size_t data_size);

/*****************************************************************************/
/**
 * @brief Gets data from beginning of the list
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[out] data [void *] the data pointer to return data
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_get_from_beginning(linked_list_t list, 
                                           void* data,
                                           size_t data_size);

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
 * @brief returns index of the data in the list, that is equal to given data 
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[in] print_function [void (is_equal)(void* data1, void* data2))] 
 * function that checks equality. if two data are same, it must return 0
 * @return [int] index of found element in list
 */
int ll_get_index_of_eq_data(linked_list_t list,
                            void* data,
                            int (is_equal)(void* data1, void* data2));
                                           
/*****************************************************************************/
/**
 * @brief Removes data from end of the list
 * @param[in] list [linked_list_t] the list to operator upon
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_remove_from_end(linked_list_t list);

/*****************************************************************************/
/**
 * @brief Removes data from beginning of the list
 * @param[in] list [linked_list_t] the list to operator upon
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_remove_from_beginning(linked_list_t list);

/*****************************************************************************/
/**
 * @brief Removes data at the given index in given list
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[in] index [int] the list to operator upon
 * @return [linked_list_errors_t] returns LL_ERROR_INDEX_OUT_OF_BOUNDS if the
 * given index is invalid for list, otherwise returns LL_ERROR_NONE
 */
linked_list_errors_t ll_remove_with_index(linked_list_t list, int index);

/*****************************************************************************/
/**
 * @brief Returns size of linked list
 * @param[in] list [linked_list_t] the list to operator upon
 * @return [int] returns the size of list
 */
int ll_return_list_size(linked_list_t list);

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