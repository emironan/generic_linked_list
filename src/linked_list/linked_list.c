/******************************************************************************
 * File: linked_list.c
 * Author: Emir
 * Date: 10.01.2025
 * Description: generic linked list source file
 * Details:
 * Version: 1
 *****************************************************************************/

#include <stdio.h>
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
/* Bütün listeyi dolaşıp silmesi gerekiyor. */
void ll_delete_linked_list(linked_list_t list)
{
    node_t node_holder = list;

    while(list->next != NULL)
    {
        node_holder = list->next;
        free(list->data);
        free(list);
        list = node_holder;
    } 
    free(list);
}

/*****************************************************************************/
linked_list_errors_t ll_add_to_end(linked_list_t list,
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
linked_list_errors_t ll_add_to_beginning(linked_list_t list,
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
