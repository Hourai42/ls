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

int	test_opendir(void)
{
	DIR *dir_ptr;
	struct dirent *entry;

	dir_ptr = opendir(".");
	if (dir_ptr == NULL)
		return (-1);
	while ((entry = readdir(dir_ptr)) != NULL)
		ft_printf("%s\n", entry->d_name);
	closedir(dir_ptr);
	return (0);
}

int test_options_bitwise(unsigned int *options)
{
	ft_printf("%d\n", OPT_l(*options));
	ft_printf("%d\n", OPT_l_on(*options));
	ft_printf("%d\n", OPT_l(*options));

	ft_printf("%d\n", OPT_R(*options));
	ft_printf("%d\n", OPT_R_on(*options));
	ft_printf("%d\n", OPT_R(*options));

	ft_printf("%d\n", OPT_R(*options));
	ft_printf("%d\n", OPT_R_on(*options));
	ft_printf("%d\n", OPT_R(*options));
	return (0);
}

/**
** write, opendir, readdir, closedir, stat, lstat, getpwuid, getgrgid, listxattr,
** getxattr, time, ctime, readlink, malloc, free, perror, strerror, exit
** Begin by making a parser for options + specific filenames
** Options must always come before filenames! Options after filenames are ignored. (No error)
** Think about how recursion will play into the -R. Hmm. You'll need a recurse-order name queue! 
** Store file names into a file? Or can you simply just keep moving past them?
** NONEXISTENT_DIR isn't an error! But illegal option is.
** Begin adding basic data structures to your library!
**/

int main(int argc, char **argv) 
{
	unsigned int options;


	return (0);
}

