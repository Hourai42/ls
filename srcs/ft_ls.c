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

int print(char letter)
{
	ft_printf("%c", letter);
	return (0);
}

int	filemode(struct stat info)
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

void	permissions_test(struct stat info)
{
	ft_printf("User permission R: %d \n", (info.st_mode & S_IRUSR));
	ft_printf("User permission W: %d \n", (info.st_mode & S_IWUSR));
	ft_printf("User permission X: %d \n", (info.st_mode & S_IXUSR));
	ft_printf("Group permission R: %d \n", (info.st_mode & S_IRGRP));
	ft_printf("Group permission W: %d \n", (info.st_mode & S_IWGRP));
	ft_printf("Group permission X: %d \n", (info.st_mode & S_IXGRP));
	ft_printf("Other permission R: %d \n", (info.st_mode & S_IROTH));
	ft_printf("Other permission R: %d \n", (info.st_mode & S_IWOTH));
	ft_printf("Other permission R: %d \n", (info.st_mode & S_IXOTH));
}

void	permissions(struct stat info, char *filename)
{
	ssize_t xattr;

	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	info.st_mode & S_IRUSR ? ft_putchar('r') : ft_putchar('-');
	info.st_mode & S_IWUSR ? ft_putchar('w') : ft_putchar('-');
	info.st_mode & S_IXUSR ? ft_putchar('x') : ft_putchar('-');
	info.st_mode & S_IRGRP ? ft_putchar('r') : ft_putchar('-');
	info.st_mode & S_IWGRP ? ft_putchar('w') : ft_putchar('-');
	info.st_mode & S_IXGRP ? ft_putchar('x') : ft_putchar('-');
	info.st_mode & S_IROTH ? ft_putchar('r') : ft_putchar('-');
	info.st_mode & S_IWOTH ? ft_putchar('w') : ft_putchar('-');
	info.st_mode & S_IXOTH ? ft_putchar('x') : ft_putchar('-');
	xattr > 0 ? ft_putchar('@') : ft_putchar(' ');
	ft_putchar(' ');
}

void	links_user_group_size(struct stat info)
{
	ft_printf("%d ", info.st_nlink);
	ft_printf("%s  ", getpwuid(info.st_uid)->pw_name);
	ft_printf("%s ", getgrgid(info.st_gid)->gr_name);
	ft_printf("%8d ", info.st_size);
}

/*
** Over six months since last modified means you should
** be replacing the hours/minutes with years.
*/

void	date(struct stat info)
{
	long int curr_time;
	long int last_modified;
	int over_six_months;
	char *ts;


	curr_time = time(NULL);
	last_modified = info.st_mtime;
	ts = ctime(&last_modified);
	over_six_months = (curr_time - last_modified) >= 15778476 ? 1 : 0;
	ft_printf("%c%c%c %c%c ", ts[4], ts[5], ts[6], ts[8], ts[9]);
	if (over_six_months)
		ft_printf("%s ", &ts[20]);
	else
		ft_printf("%c%c:%c%c ", ts[11], ts[12], ts[14], ts[15]);
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

void	handle_list_format(t_linked_list *names, char *file)
{
	struct stat info;
	t_lnode *iter;
	char *joined;
	int use_readlink;

	use_readlink = 0;
	iter = names->start;
	while (iter != NULL)
	{
		joined = ft_strjoin(file, (char *)iter->content);
		lstat(joined, &info);
		use_readlink = filemode(info);
		permissions(info, joined);
		links_user_group_size(info);
		date(info);
		ft_printf("%s\n", (char *)iter->content);
		free(joined);
		iter = iter->next;
	}
}

/*
** Need to get the full path for each one if you wanna do the recursion correctly
*/

void	option_handler(unsigned int options, t_linked_list *names, char *filename, long int blocks)
{
	char *file;

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

long int sum_blocks(char *filename, char *file)
{
	struct stat info;
	char *joined;
	long int blocks;

	filename = ft_strjoin(filename, "/");
	joined = ft_strjoin(filename, file);
	lstat(joined, &info);
	blocks = info.st_blocks;
	free(joined);
	free(filename);
	return (blocks);
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
	long int blocks;

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
