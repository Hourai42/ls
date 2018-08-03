/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_recur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:33:19 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:33:23 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int		not_permaloop(char *string)
{
	if (string[0] == '.')
	{
		if (string[1] == '\0')
			return (NO);
		else if (string[1] == '.' && string[2] == '\0')
			return (NO);
	}
	return (YES);
}

void			handle_recur(unsigned int options, t_linked_list *names,
char *file)
{
	t_lnode		*iter;
	struct stat	info;
	char		*joined;

	iter = names->start;
	while (iter != NULL)
	{
		joined = ft_strjoin(file, (char *)iter->content);
		lstat(joined, &info);
		if (S_ISDIR(info.st_mode) && not_permaloop((char *)iter->content))
			read_directories(joined, options);
		free(joined);
		iter = iter->next;
	}
}
