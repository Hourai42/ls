/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:17:16 by ttran             #+#    #+#             */
/*   Updated: 2018/07/23 15:20:50 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

#include <libft.h>
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define YES 1
#define NO 0
#define ILLEGAL_OPTION -1
#define NONEXISTENT_DIR -2
#define EXIT -10
#define STAY 10
#define VALID_OPTION 2

#define OPT_l(x) (x & 1)
#define OPT_R(x) (x & 2)
#define OPT_a(x) (x & 4)
#define OPT_r(x) (x & 8)
#define OPT_t(x) (x & 16)
#define is_first(x) (x & 32)

#define OPT_l_on(x) (x |= 1)
#define OPT_R_on(x) (x |= 2)
#define OPT_a_on(x) (x |= 4)
#define OPT_r_on(x) (x |= 8)
#define OPT_t_on(x) (x |= 16)
#define not_first(x) (x |= 32)

/*
** Add to back, take from front.
** Add this basic queue data structure to your library later!
*/

typedef struct s_node
{
    void *content;
    struct s_node *previous;
}               t_node;

typedef struct s_queue
{
    t_node *front;
    t_node *back;
}               t_queue;

typedef struct s_lnode
{
    void *content;
    struct s_lnode *next;
}               t_lnode;

typedef struct s_linked_list
{
    t_lnode *start;
    t_lnode *end;
}               t_linked_list;

/*
** Linked List functions
*/

t_linked_list *create_list(void);
void    add_node(void *content, t_linked_list *list);
void free_list(t_linked_list **list);
void read_list(t_lnode *list);

/*
** Mergesort functions
*/

t_lnode *mergesort_list(t_lnode *list, long int (*cmp)(void *one, void *two));

long int ft_strcmp2(void *str1, void *str2);
long int ft_strcmp2_r(void *str1, void *str2);
long int time_cmp(void *str1, void *str2);
long int time_cmp_r(void *str1, void *str2);

int	read_directories(char *filename, unsigned int options);

#endif
