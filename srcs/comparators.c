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

long int ft_strcmp2(void *str1, void *str2)
{
    int i;
    char *s1;
    char *s2;

    i = 0;
    s1 = (char *)str1;
    s2 = (char *)str2;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long int ft_strcmp2_r(void *str1, void *str2)
{
    int i;
    char *s1;
    char *s2;

    i = 0;
    s1 = (char *)str2;
    s2 = (char *)str1;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long int time_cmp(void *str1, void *str2)
{
    char *s1;
    char *s2;
    struct stat info1;
    struct stat info2;

    s1 = (char *)str1;
    s2 = (char *)str2;
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
            return (ft_strcmp(s1, s2));
    }
}

long int time_cmp_r(void *str1, void *str2)
{
    char *s1;
    char *s2;
    struct stat info1;
    struct stat info2;

    s1 = (char *)str1;
    s2 = (char *)str2;
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
            return (ft_strcmp(s2, s1));
    }
}
