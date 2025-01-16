/******************************************************************************
 * File: linked_list.c
 * Author: Emir
 * Date: 10.01.2025
 * Description: generic linked list source file
 * Details:
 * Version: 1
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef linked_list_t node_t;

struct st_node_t
{
    node_t next;
    void* data;
};

/*****************************************************************************/
/**
 * @brief Removes the given node by freeing the memory and makes the next
 * pointer of it NULL. It must be used with end nodes.
 * @param[in] node [node_t] the node to be removed
 * @return [void]
 */
static void remove_tail(node_t node);

/*****************************************************************************/
/**
 * @brief iterates through list and returns the address of last node
 * @param[in] list [linked_list_t] the list to operator upon
 * @param[out] node [node_t] output to return address of last node
 * @return [linked_list_errors_t] returns LL_ERROR_LIST_ALREADY_EMPTY if the
 * list is already empty, otherwise returns LL_ERROR_NONE
 */
static linked_list_errors_t get_tail(linked_list_t list, node_t* node);

/*****************************************************************************/
linked_list_t ll_create_linked_list(void)
{
    linked_list_t linked_list = malloc(sizeof(struct st_node_t));

    if(linked_list != NULL)
    {
        linked_list->next = NULL;
    }

    return linked_list;
}

/*****************************************************************************/
void ll_delete_linked_list(linked_list_t list)
{
    node_t node_holder = list;

    while(list->next != NULL)
    {
        node_holder = list->next;
        list->next = NULL;
        free(list->data);
        free(list);
        list = node_holder;
    } 
    free(list);
}

/*****************************************************************************/
linked_list_errors_t ll_add_tail(linked_list_t list,
                                 void* data,
                                 size_t data_size)
{
    while(list->next != NULL)
    {
        list = list->next;
    }
    
    list->data = malloc(data_size);
    // it returns nothing for now but an error return system might be added later.
    if(list->data == NULL)
    {
        return LL_ERROR_ALLOCATION;
    }

    memcpy(list->data, data, data_size);
    list->next = malloc(sizeof(struct st_node_t));

    if(list->next == NULL)
    {
        return LL_ERROR_ALLOCATION;
    }
    else
    {
        list->next->next = NULL;
    }

    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_add_head(linked_list_t list,
                                 void* data,
                                 size_t data_size)
{
    node_t node = malloc(sizeof(struct st_node_t));

    if(node == NULL)
    {
        return LL_ERROR_ALLOCATION;
    }

    memcpy(node, list, sizeof(struct st_node_t));

    list->next = node;
    list->data = malloc(data_size);
    
    if(list->data == NULL)
    {
        return LL_ERROR_ALLOCATION;
    }

    memcpy(list->data, data, data_size);
    
    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_pop_tail(linked_list_t list, 
                                 void* data,
                                 size_t data_size)
{
    if(ll_get_tail(list, data, data_size) == LL_ERROR_LIST_ALREADY_EMPTY)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }
    ll_remove_tail(list);

    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_pop_head(linked_list_t list, 
                                 void* data,
                                 size_t data_size)
{
    if(ll_get_head(list, data, data_size) == LL_ERROR_LIST_ALREADY_EMPTY)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }

    ll_remove_head(list);

    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_get_tail(linked_list_t list, 
                                 void* data,
                                 size_t data_size)
{
    if(get_tail(list, &list) == LL_ERROR_LIST_ALREADY_EMPTY)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }

    memcpy(data, list->data, data_size);
    
    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_get_head(linked_list_t list, 
                                 void* data,
                                 size_t data_size)
{
    if(list->next == NULL)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }

    memcpy(data, list->data, data_size);

    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_get_item_with_index(linked_list_t list, 
                                            int index, 
                                            void* data,
                                            size_t data_size)
{
    if(index < 0)
    {
        return LL_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    for(int i = 0; i < index; i++)
    {
        list = list->next;
        if(list == NULL)
        {
            return LL_ERROR_INDEX_OUT_OF_BOUNDS;
        }
    }
    /* Always allocating the next node while filling the current. 
    This is why we are controlling this here. */
    if(list->next == NULL)
    {
        return LL_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    /* Not returning the pointer of linked_list node, instead
    copying the data to the given area*/
    memcpy(data, list->data, data_size);

    return LL_ERROR_NONE;
}

/*****************************************************************************/
int ll_get_index_of_eq_data(linked_list_t list,
                            void* data,
                            int (is_equal)(void* data1, void* data2))
{
    int index = 0;

    // This means list is empty
    if(list->next == NULL)
    {
        return -1;
    }

    while(list->next->next != NULL)
    {
        if(is_equal(list->data, data) == 0)
        {
            return index;
        }

        index++;
        list = list->next;
    }

    /* -1 means couldn't found */
    return -1;
}

/*****************************************************************************/
linked_list_errors_t ll_remove_tail(linked_list_t list)
{
    if(get_tail(list, &list) == LL_ERROR_LIST_ALREADY_EMPTY)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }

    remove_tail(list);
    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_remove_head(linked_list_t list)
{
    // will hold the next value of a free'd node
    node_t node;

    if(list->next == NULL)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }

    free(list->data);
    list->data = list->next->data;

    node = list->next->next; 
    free(list->next);
    list->next = node;

    return LL_ERROR_NONE;
}

/*****************************************************************************/
linked_list_errors_t ll_remove_with_index(linked_list_t list, int index)
{
    // this is creted to hold value of the next node of the free'd one
    node_t node;
    
    if(index < 0)
    {
        return LL_ERROR_INDEX_OUT_OF_BOUNDS;
    }
    // -1 is for stopping at the node just before our indexed node 
    for(int i = 0; i < index - 1; i++)
    {
        list = list->next;
        if(list == NULL)
        {
            return LL_ERROR_INDEX_OUT_OF_BOUNDS;
        }
    }
    /* Always allocating the next node while filling the current. 
    This is why we are controlling this here. */
    if(list->next->next == NULL)
    {
        return LL_ERROR_INDEX_OUT_OF_BOUNDS;
    }
    
    /* if it is the first index we can use the remove_from_beginning */
    if(index != 0)
    {
        node = list->next;
        list->next = list->next->next;
        free(node->data);
        free(node);
    }
    else
    {
        ll_remove_head(list);
    }

    return LL_ERROR_NONE;
}

/*****************************************************************************/
int ll_return_list_size(linked_list_t list)
{
    int list_size = 0;
    while(list->next != NULL)
    {
        list_size++;
        list = list->next;
    }

    return list_size;
}

/*****************************************************************************/
void ll_print_all_list(linked_list_t list, void (print_function)(void *))
{
    print_function(list->data);
    while(list->next != NULL)
    {
        list = list->next;
        if(list->next != NULL)
        {
            print_function(list->data);
        }
    }
}

/*****************************************************************************/
static void remove_tail(node_t node)
{
    free(node->next);
    free(node->data);
    node->next = NULL;
}

/*****************************************************************************/
static linked_list_errors_t get_tail(linked_list_t list, node_t* node)
{
    *node = list;

    if(list->next == NULL)
    {
        return LL_ERROR_LIST_ALREADY_EMPTY;
    }

    while((*node)->next->next != NULL)
    {
        *node = (*node)->next;
    }

    return LL_ERROR_NONE;
}

/*****************************************************************************/