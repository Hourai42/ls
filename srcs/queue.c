/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:26:21 by ttran             #+#    #+#             */
/*   Updated: 2018/07/26 16:26:22 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void enqueue(t_queue *queue, void *content)
{
    t_node *new_node;

    new_node = malloc(sizeof(t_node));
    new_node->content = content;
    new_node->previous = NULL;
    if (queue->front == NULL)
        queue->front = new_node;
    else
        queue->back->previous = new_node;
    queue->back = new_node;
}

void *dequeue(t_queue *queue)
{
    void *content_ptr;
    t_node *ptr;

    content_ptr = NULL;
    if (queue->front != NULL)
    {
        content_ptr = queue->front->content;
        ptr = queue->front;
        queue->front = queue->front->previous;
        free(ptr);
        if (queue->front == NULL)
            queue->back = NULL;
    }
    return (content_ptr);
}

t_queue *queue_init(void)
{
    t_queue *queue;

    queue = malloc(sizeof(t_queue));
    queue->front = NULL;
    queue->back = NULL;
    return (queue);
}

int queueIsEmpty(t_queue *queue)
{
    if (queue->front == NULL)
        return (YES);
    return (NO);
}
