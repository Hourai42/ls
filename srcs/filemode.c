/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:30:59 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:31:04 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	print(char letter)
{
	ft_printf("%c", letter);
	return (0);
}

int			filemode(struct stat info)
{
	if (S_ISREG(info.st_mode))
		return (print('-'));
	else if (S_ISDIR(info.st_mode))
		return (print('d'));
	else if (S_ISCHR(info.st_mode))
		return (print('c'));
	else if (S_ISBLK(info.st_mode))
		return (print('b'));
	else if (S_ISFIFO(info.st_mode))
		return (print('p'));
	else if (S_ISSOCK(info.st_mode))
		return (print('s'));
	else
	{
		ft_printf("%c", 'l');
		return (1);
	}
}
