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

t_linked_list		*create_list(void)
{
	t_linked_list	*list;

	list = malloc(sizeof(t_linked_list));
	list->start = NULL;
	list->end = NULL;
	return (list);
}

void				add_node(void *content, t_linked_list *list)
{
	t_lnode			*new;

	new = malloc(sizeof(t_lnode));
	new->content = ft_strdup(content);
	new->next = NULL;
	if (list->start == NULL)
		list->start = new;
	else
		list->end->next = new;
	list->end = new;
}

void				free_list(t_linked_list **list)
{
	t_lnode			*ptr;

	while ((*list)->start)
	{
		ptr = (*list)->start;
		(*list)->start = ptr->next;
		free(ptr->content);
		free(ptr);
	}
	free(*list);
}

void				read_list(t_lnode *list)
{
	while (list != NULL)
	{
		ft_printf("%s\n", (char *)list->content);
		list = list->next;
	}
}
