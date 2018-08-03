/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:17:20 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:17:21 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	valid_option(char option)
{
	if (option == 'l' || option == 'R' || option == 'a' || option == 'r'
	|| option == 't')
		return (YES);
	return (NO);
}

static void	use_option_macros(unsigned int *options, char letter)
{
	if (letter == 'l')
		OPT_L_ON(*options);
	else if (letter == 'R')
		OPT_R_ON(*options);
	else if (letter == 'a')
		OPT_A_ON(*options);
	else if (letter == 'r')
		OPT_REV_ON(*options);
	else
		OPT_T_ON(*options);
}

int			set_options(char **argv, unsigned int *options)
{
	if (**argv == '-')
	{
		(*argv)++;
		while (**argv)
		{
			if (valid_option(**argv) == YES)
				use_option_macros(options, **argv);
			else
				return (ILLEGAL_OPTION);
			(*argv)++;
		}
		return (0);
	}
	else
		return (1);
}
