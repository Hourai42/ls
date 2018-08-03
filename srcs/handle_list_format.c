/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 20:24:23 by ttran             #+#    #+#             */
/*   Updated: 2018/08/02 20:24:30 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		date(struct stat info)
{
	long int	curr_time;
	long int	last_modified;
	int			over_six_months;
	char		*ts;

	curr_time = time(NULL);
	last_modified = info.st_mtime;
	ts = ctime(&last_modified);
	over_six_months = (curr_time - last_modified) >= 15778476 ? 1 : 0;
	ft_printf("%c%c%c %c%c ", ts[4], ts[5], ts[6], ts[8], ts[9]);
	if (over_six_months)
	{
		ts[24] = '\0';
		ft_printf("%s ", &ts[20]);
	}
	else
		ft_printf("%c%c:%c%c ", ts[11], ts[12], ts[14], ts[15]);
}

static void		permissions(struct stat info, char *filename)
{
	ssize_t		xattr;

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

static void		links_user_group_size(struct stat info)
{
	ft_printf("%d ", info.st_nlink);
	ft_printf("%s  ", getpwuid(info.st_uid)->pw_name);
	ft_printf("%s ", getgrgid(info.st_gid)->gr_name);
	ft_printf("%8d ", info.st_size);
}

static void		read_link(char *filename)
{
	char		buf[1024];
	ssize_t		len;

	if ((len = readlink(filename, buf, sizeof(buf) - 1)) != -1)
		buf[len] = '\0';
	ft_printf(" -> ");
	ft_printf("%s\n", buf);
}

void			handle_list_format(t_linked_list *names, char *file)
{
	struct stat	info;
	t_lnode		*iter;
	char		*joined;
	int			use_readlink;

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
		ft_printf("%s", (char *)iter->content);
		use_readlink ? read_link(joined) : ft_putchar('\n');
		free(joined);
		iter = iter->next;
	}
}
