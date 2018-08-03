/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:21:07 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:21:13 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int					read_directories(char *filename, unsigned int options)
{
	DIR				*dir_ptr;
	struct dirent	*entry;
	t_linked_list	*names;
	long int		blocks;

	blocks = 0;
	names = create_list();
	dir_ptr = opendir(filename);
	if (dir_ptr == NULL)
		return (NONEXISTENT_DIR);
	while ((entry = readdir(dir_ptr)) != NULL)
		if (!(entry->d_name[0] == '.' && !OPT_a(options)))
		{
			add_node(entry->d_name, names);
			blocks += sum_blocks(filename, (char *)names->end->content);
		}
	option_handler(options, names, filename, blocks);
	closedir(dir_ptr);
	free_list(&names);
	return (0);
}
