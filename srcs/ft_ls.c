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

/*
** Need to fix multiple option input if the path is still -r -t etc instead of -rt
*/

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
		return (0);
	}
	else
		return (1);
}

void	handle_sort(unsigned int options, t_linked_list *names, char *file)
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

/*
** Need to handle special case of "." and ".." in recursion later.
*/

int	not_permaloop(char *string)
{
	if (string[0] == '.')
	{
		if (string[1] == '\0')
			return (NO);
		else if (string [1] == '.' && string[2] == '\0')
			return (NO);
	}
	return (YES);
}

void	handle_R(unsigned int options, t_linked_list *names, char *file)
{
	t_lnode *iter;
	struct stat info;
	char *joined;

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

void	handle_printing(unsigned int *options, char *filename)
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

/*
** Need to sum up the total number of size in bytes divided by 512 or use st_blocks
** File mode(Type using ISREG, ISDIR, etc)
** Access by using macros on st_mode
** Number of hard links in stat structure
** st_uid and st_gid for user id and group id-- might have to use other functions but still unsure
** Number of bytes in the file -- st_size
** abbrev. month, day of month, hour, minute last modified then filename
** if mode is l for link, filename is itself -> where it points to (Possibly by using readlink)
** Experiment to see if you can get everything in the format you wish
*/

void	handle_list_format(unsigned int options, t_linked_list *names, char *file)
{
	options = 0; names = 0; file = 0;
}

/*
** Need to get the full path for each one if you wanna do the recursion correctly
*/

void	option_handler(unsigned int options, t_linked_list *names, char *filename)
{
	char *file;

	if (!(is_not_first(options)))
		file = ft_strdup("./");
	else
		file = ft_strjoin(filename, "/");
	handle_sort(options, names, file);
	handle_printing(&options, filename);
	if (OPT_l(options))
		handle_list_format(options, names, file);
	else
		read_list(names->start);
	if (OPT_R(options))
		handle_R(options, names, file);
	free(file);
}

/*
** Haven't used stat, lstat, getpwuid, getgrgid, listxattr, getxattr, time, ctime, readlink
** Looking inside of the headers to see what the structs consist of is nice.
*/

void	experiments(unsigned int options, t_linked_list *names)
{
	struct stat info;

	options = 0, names = 0;
	stat(".", &info);
	ft_printf("hi");
	ft_printf("%s", info);
	ft_printf("%d\n", info.st_mtime);
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

	names = create_list();
	dir_ptr = opendir(filename);
	if (dir_ptr == NULL)
		return (NONEXISTENT_DIR);
	while ((entry = readdir(dir_ptr)) != NULL)
		if (!(entry->d_name[0] == '.' && !OPT_a(options)))
			add_node(entry->d_name, names);
	//read_list(names->start);
	option_handler(options, names, filename);
	//experiments(options, names);
	//read_list(names->start);
	closedir(dir_ptr);
	// Names->front will have to be the sorted list so you can free correctly
	free_list(&names);
	// If strjoin method is used, may need to dup filename when sending in and free everytime
	// for every single stack! Isn't too bad.
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
**
** Bonuses can be management of ACL and extended attributes
** Column management w/o -l
** More options
** Colors! Depending on file type I guess
** Optimization n' speed? lol no
**/

int main(int argc, char **argv) 
{
	unsigned int options;
	int flag;

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
	return (0);
}
