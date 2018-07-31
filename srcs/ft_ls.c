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

void	set_flags(unsigned int *options, int *flag, int argc)
{
	*options = 0;
	*flag = 0;
	argc = 0;
}

int		error_messages(int *flag, char *error)
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

int valid_option(char option)
{
	if (option == 'l' || option == 'R' || option == 'a' || option == 'r'
	|| option == 't')
		return (YES);
	return (NO);
}

void	use_option_macros(unsigned int *options, char letter)
{
	if (letter == 'l')
		OPT_l_on(*options);
	else if (letter == 'R')
		OPT_R_on(*options);
	else if (letter == 'a')
		OPT_a_on(*options);
	else if (letter == 'r')
		OPT_r_on(*options);
	else
		OPT_t_on(*options);
}

int	set_options(char **argv, unsigned int *options)
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
		return (VALID_OPTION);
	}
	else
		return (1);
}

void	option_handler(unsigned int options, t_linked_list *names)
{
	options = 0; names = 0;
}

/*
** Sort by alphabetical order in Linked List
** Go through list twice-- once to print names, then another time 
** to recurse into directories. Lole, this is super lazy. 
** -l is long format with all the information
** -t is sort by time modified
** -r is reverse
** -R is recursive
** -a is include hidden
*/

int	read_directories(char *filename, unsigned int options)
{
	DIR *dir_ptr;
	struct dirent *entry;
	t_linked_list *names;

	options = 0;
	names = create_list();
	dir_ptr = opendir(filename);
	if (dir_ptr == NULL)
		return (NONEXISTENT_DIR);
	while ((entry = readdir(dir_ptr)) != NULL)
		add_node(entry->d_name, names);
	option_handler(options, names);
	closedir(dir_ptr);
	free_list(&names);
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
** Parse(options then filenames) -> Read directories
** Use exit to leave since no memory is allocated yet during option parsing.
**/

int main(int argc, char **argv) 
{
	unsigned int options;
	int flag;

	argv++;
	set_flags(&options, &flag, argc);
	while (*argv && flag == 0)
	{
		if ((flag = set_options(argv, &options)) == VALID_OPTION)
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
	return (0);
}
