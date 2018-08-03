/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:17:05 by ttran             #+#    #+#             */
/*   Updated: 2018/07/23 15:20:37 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void			set_flags(unsigned int *options, int *flag, int argc)
{
	*options = 0;
	*flag = 0;
	argc = 0;
}

static int			error_messages(int *flag, char *error)
{
	if (*flag == ILLEGAL_OPTION)
	{
		ft_printf("ls: illegal option -- ");
		ft_printf("%c\n", *error);
		exit(0);
	}
	else if (*flag == NONEXISTENT_DIR)
	{
		ft_printf("ls: %s: No such file or directory\n", error);
		*flag = 0;
	}
	return (STAY);
}

/*
** Bonuses can be management of ACL and extended attributes
** Column management w/o -l
** More options
** Colors! Depending on file type I guess
*/

int					main(int argc, char **argv)
{
	unsigned int	options;
	int				flag;

	argv++;
	set_flags(&options, &flag, argc);
	while (*argv && flag == 0)
	{
		if ((flag = set_options(argv, &options)) == 0)
			argv++;
		else
			error_messages(&flag, *argv);
	}
	if (*argv == 0)
		read_directories(".", options);
	else
	{
		while (*argv)
		{
			flag = read_directories(*argv, options);
			error_messages(&flag, *argv);
			argv++;
		}
	}
	while (1)
		;
	return (0);
}
