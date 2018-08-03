/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:23:44 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:23:49 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

long int		sum_blocks(char *filename, char *file)
{
	struct stat	info;
	char		*joined;
	long int	blocks;

	filename = ft_strjoin(filename, "/");
	joined = ft_strjoin(filename, file);
	lstat(joined, &info);
	blocks = info.st_blocks;
	free(joined);
	free(filename);
	return (blocks);
}
