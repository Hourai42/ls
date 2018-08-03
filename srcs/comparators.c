/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:20:12 by ttran             #+#    #+#             */
/*   Updated: 2018/07/31 16:20:18 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int				ft_strcmp2(void *str1, void *str2, char *file)
{
	int			i;
	char		*s1;
	char		*s2;

	file = 0;
	i = 0;
	s1 = (char *)str1;
	s2 = (char *)str2;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int				ft_strcmp2_r(void *str1, void *str2, char *file)
{
	int			i;
	char		*s1;
	char		*s2;

	file = 0;
	i = 0;
	s1 = (char *)str2;
	s2 = (char *)str1;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int				time_cmp(void *str1, void *str2, char *file)
{
	char		*s1;
	char		*s2;
	struct stat	info1;
	struct stat	info2;

	s1 = ft_strjoin(file, (char *)str1);
	s2 = ft_strjoin(file, (char *)str2);
	lstat(s1, &info1);
	lstat(s2, &info2);
	if (info1.st_mtime < info2.st_mtime)
		return (1);
	else if (info1.st_mtime > info2.st_mtime)
		return (-1);
	else
	{
		if (info1.st_mtimespec.tv_nsec < info2.st_mtimespec.tv_nsec)
			return (1);
		else if (info1.st_mtimespec.tv_nsec > info2.st_mtimespec.tv_nsec)
			return (-1);
		else
			return (ft_strcmp((char *)str1, (char *)str2));
	}
	free(s1);
	free(s2);
}

int				time_cmp_r(void *str1, void *str2, char *file)
{
	char		*s1;
	char		*s2;
	struct stat	info1;
	struct stat	info2;

	s1 = ft_strjoin(file, (char *)str1);
	s2 = ft_strjoin(file, (char *)str2);
	lstat(s1, &info1);
	lstat(s2, &info2);
	if (info1.st_mtime < info2.st_mtime)
		return (-1);
	else if (info1.st_mtime > info2.st_mtime)
		return (1);
	else
	{
		if (info1.st_mtimespec.tv_nsec < info2.st_mtimespec.tv_nsec)
			return (-1);
		else if (info1.st_mtimespec.tv_nsec > info2.st_mtimespec.tv_nsec)
			return (1);
		else
			return (ft_strcmp((char *)str2, (char *)str1));
	}
	free(s1);
	free(s2);
}
