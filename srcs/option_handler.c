/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:22:48 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:22:53 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	handle_sort(unsigned int options, t_linked_list *names, char *file)
{
	if (OPT_t(options) && OPT_r(options))
		names->start = mergesort_list(names->start, &time_cmp_r, file);
	else if (OPT_t(options))
		names->start = mergesort_list(names->start, &time_cmp, file);
	else if (OPT_r(options))
		names->start = mergesort_list(names->start, &ft_strcmp2_r, file);
	else
		names->start = mergesort_list(names->start, &ft_strcmp2, file);
}

static void	handle_printing(unsigned int *options, char *filename)
{
	if (is_not_first(*options))
	{
		ft_printf("\n");
		if (OPT_R(*options))
			ft_printf("%s:\n", filename);
	}
	else
		not_first(*options);
}

void		option_handler(unsigned int options, t_linked_list *names,
char *filename, long int blocks)
{
	char	*file;

	file = ft_strjoin(filename, "/");
	handle_sort(options, names, file);
	handle_printing(&options, filename);
	if (OPT_l(options))
	{
		ft_printf("total %ld\n", blocks);
		handle_list_format(names, file);
	}
	else
		read_list(names->start);
	if (OPT_R(options))
		handle_recur(options, names, file);
	free(file);
}
