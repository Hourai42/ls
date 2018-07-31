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

void    add_node(void *content, t_linked_list *list)
{
    t_lnode *new;

    new = malloc(sizeof(t_lnode));
    new->content = content;
    new->next = NULL;
    if (list->start == NULL)
        list->start = new;
    else
        list->end->next = new;
    list->end = new;
}

void free_list(t_linked_list **list)
{
    t_lnode *ptr;

    while ((*list)->start)
    {
        ptr = (*list)->start;
        (*list)->start = ptr->next;
        free(ptr);
    }
    free(*list);
}

void read_list(t_lnode *list)
{
    while (list != NULL)
    {
        printf("%s\n", (char *)list->content);
        list = list->next;
    }
}

/*
** Functions to mergesort a linked list!
** Observe how all the pointers are fixed later.
*/

t_lnode *mergesort_list(t_lnode *list, int (*cmp)(void *one, void *two))
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
    list = mergesort_list(list, cmp);
    right = mergesort_list(right, cmp);

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
        } else if (cmp(list->content, right->content) < 0) {
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

int ft_strcmp2(void *str1, void *str2)
{
    int i;
    char *s1;
    char *s2;

    i = 0;
    s1 = (char *)str1;
    s2 = (char *)str2;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}