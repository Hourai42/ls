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

#define OPT_l_on(x) (x |= 1)
#define OPT_R_on(x) (x |= 2)
#define OPT_a_on(x) (x |= 4)
#define OPT_r_on(x) (x |= 8)
#define OPT_t_on(x) (x |= 16)

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

#endif
