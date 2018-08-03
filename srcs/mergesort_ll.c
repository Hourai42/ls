/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 19:36:54 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 19:36:55 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_lnode			*find_middle(t_lnode *list)
{
	t_lnode				*right;
	t_lnode				*last;

	right = list;
	last = list;
	while (list && list->next)
	{
		last = right;
		right = right->next;
		list = list->next->next;
	}
	last->next = NULL;
	return (right);
}

static t_lnode			*merge_helper(t_lnode **left, t_lnode **right,
int (*cmp)(void *one, void *two, char *file), char *filename)
{
	t_lnode *next;

	if (!(*right))
	{
		next = *left;
		*left = (*left)->next;
	}
	else if (!(*left))
	{
		next = *right;
		*right = (*right)->next;
	}
	else if (cmp((*left)->content, (*right)->content, filename) < 0)
	{
		next = *left;
		*left = (*left)->next;
	}
	else
	{
		next = *right;
		*right = (*right)->next;
	}
	return (next);
}

static	t_lnode			*merge_list(t_lnode *left, t_lnode *right,
int (*cmp)(void *one, void *two, char *file), char *filename)
{
	t_lnode				*result;
	t_lnode				*tail;
	t_lnode				*next;

	tail = NULL;
	result = NULL;
	next = NULL;
	while (left || right)
	{
		next = merge_helper(&left, &right, cmp, filename);
		if (!result)
			result = next;
		else
			tail->next = next;
		tail = next;
	}
	return (result);
}

t_lnode					*mergesort_list(t_lnode *list,
int (*cmp)(void *one, void *two, char *file), char *filename)
{
	t_lnode				*right;

	if (!list || !list->next)
		return (list);
	right = find_middle(list);
	list = mergesort_list(list, cmp, filename);
	right = mergesort_list(right, cmp, filename);
	return (merge_list(list, right, cmp, filename));
}
