/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 21:34:52 by ttran             #+#    #+#             */
/*   Updated: 2018/07/29 21:34:54 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_linked_list *create_list(void)
{
    t_linked_list *list;

    list = malloc(sizeof(t_linked_list));
    list->start = NULL;
    list->end = NULL;
    return (list);
}

/*
** Static memory overflowed since you were just setting pointer to static memory instead of strduping.
*/

void    add_node(void *content, t_linked_list *list)
{
    t_lnode *new;

    new = malloc(sizeof(t_lnode));
    new->content = ft_strdup(content);
    new->next = NULL;
    if (list->start == NULL)
        list->start = new;
    else
        list->end->next = new;
    list->end = new;
    //ft_printf("%s\n", (char *)content);
}

void free_list(t_linked_list **list)
{
    t_lnode *ptr;

    while ((*list)->start)
    {
        ptr = (*list)->start;
        (*list)->start = ptr->next;
        free(ptr->content);
        free(ptr);
    }
    free(*list);
}

void read_list(t_lnode *list)
{
    //struct stat info;

    while (list != NULL)
    {
        //lstat((char *)list->content, &info);
        //printf("Nano seconds: %s : %ld\n", (char *)list->content, info.st_mtimespec.tv_nsec);
        //printf("Seconds : %s : %ld\n", (char *)list->content, info.st_mtime);
        ft_printf("%s\n", (char *)list->content);
        list = list->next;
    }
}

/*
** Functions to mergesort a linked list!
** Observe how all the pointers are fixed later.
*/

t_lnode *mergesort_list(t_lnode *list, long int (*cmp)(void *one, void *two, char *file), char *filename)
{
 // Trivial case.
    if (!list || !list->next)
        return list;

    t_lnode *right = list,
            *temp  = list,
            *last  = list,
            *result = 0,
            *next   = 0,
            *tail   = 0;

    // Find halfway through the list (by running two pointers, one at twice the speed of the other).
    while (temp && temp->next)
    {
        last = right;
        right = right->next;
        temp = temp->next->next;
    }

    // Break the list in two. (prev pointers are broken here, but we fix later)
    last->next = 0;

    // Recurse on the two smaller lists:
    list = mergesort_list(list, cmp, filename);
    right = mergesort_list(right, cmp, filename);

    // Merge:
    while (list || right)
    {
        // Take from empty lists, or compare:
        if (!right) {
            next = list;
            list = list->next;
        } else if (!list) {
            next = right;
            right = right->next;
        } else if (cmp(list->content, right->content, filename) < 0) {
            next = list;
            list = list->next;
        } else {
            next = right;
            right = right->next;
        }
        if (!result) {
            result=next;
        } else {
            tail->next=next;
        }
        tail = next;
    }
    return result;
}
