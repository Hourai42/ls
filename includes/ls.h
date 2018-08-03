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

# include <libft.h>
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

# define YES 1
# define NO 0
# define ILLEGAL_OPTION -1
# define NONEXISTENT_DIR -2
# define EXIT -10
# define STAY 10
# define VALID_OPTION 2

# define OPT_L(x) (x & 1)
# define OPT_R(x) (x & 2)
# define OPT_A(x) (x & 4)
# define OPT_REV(x) (x & 8)
# define OPT_T(x) (x & 16)
# define IS_NOT_FIRST(x) (x & 32)

# define OPT_L_ON(x) (x |= 1)
# define OPT_R_ON(x) (x |= 2)
# define OPT_A_ON(x) (x |= 4)
# define OPT_REV_ON(x) (x |= 8)
# define OPT_T_ON(x) (x |= 16)
# define NOT_FIRST(x) (x |= 32)

/*
** Queue structures
*/

typedef struct		s_node
{
	void			*content;
	struct s_node	*previous;
}					t_node;

typedef struct		s_queue
{
	t_node			*front;
	t_node			*back;
}					t_queue;

/*
** Queue functions
*/

t_queue				*queue_init(void);
void				enqueue(t_queue *queue, void *content);
void				*dequeue(t_queue *queue);
int					queue_is_empty(t_queue *queue);

/*
** Linked List structures
*/

typedef struct		s_lnode
{
	void			*content;
	struct s_lnode	*next;
}					t_lnode;

typedef struct		s_linked_list
{
	t_lnode			*start;
	t_lnode			*end;
}					t_linked_list;

/*
** Linked list functions
*/

t_linked_list		*create_list(void);
void				add_node(void *content, t_linked_list *list);
void				free_list(t_linked_list **list);
void				read_list(t_lnode *list);

/*
** Mergesort for linked list
*/

t_lnode				*mergesort_list(t_lnode *list,
int (*cmp)(void *one, void *two, char *file), char *filename);

/*
** Comparator functions
*/

int					ft_strcmp2(void *str1, void *str2, char *file);
int					ft_strcmp2_r(void *str1, void *str2, char *file);
int					time_cmp(void *str1, void *str2, char *file);
int					time_cmp_r(void *str1, void *str2, char *file);

/*
** LS core control
*/

int					main(int argc, char **argv);

/*
** Function to read directories
*/

int					read_directories(char *filename, unsigned int options);

/*
** Functions to set options
*/

int					set_options(char **argv, unsigned int *options);

/*
** Option handler and its implementations
*/

void				option_handler(unsigned int options, t_linked_list *names,
char *filename, long int blocks);
void				handle_recur(unsigned int options, t_linked_list *names,
char *file);
long int			sum_blocks(char *filename, char *file);
void				handle_list_format(t_linked_list *names, char *file);
int					filemode(struct stat info);

#endif
