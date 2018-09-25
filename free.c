/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:04:12 by ekelen            #+#    #+#             */
/*   Updated: 2018/09/25 10:50:20 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*get_next(t_block *curr)
{
	if (curr && curr->is_free)
		return (get_next(curr->next));
	return (curr);
}

/*
** get list of contiguous freed blocks
** just to help determine when to call munmap
*/

static t_block		*fuse_free_blocks(void *ptr, t_block *curr, t_block *s)
{
	if (!curr)
		return (NULL);
	if (ptr == curr->ret_ptr)
	{
		s = s ? s : curr;
		s->next = get_next(curr->next);
		return (s);
	}
	if (curr->is_free && !s)
		s = curr;
	if (!curr->is_free)
		s = NULL;
	return (fuse_free_blocks(ptr, curr->next, s));
}

static t_zone		*actually_free(t_block *found_b, t_zone *curr)
{
	t_zone *next;

	next = NULL;
	if (found_b)
	{
		if (found_b == curr->head && !found_b->next && \
		curr->free_bytes < SMALL)
		{
			next = curr->next;
			munmap(curr, curr->len + sizeof(t_zone));
			return (next);
		}
		found_b->is_free = 1;
	}
	return (curr);
}

/*
** find node(s) to free, and from which list
*/

static void			*free_and_update(t_zone *curr, void *ptr)
{
	t_block		*found_b;

	found_b = NULL;
	if (curr)
	{
		if (ptr >= (void *)curr && ptr < curr->end)
		{
			found_b = (t_block *)fuse_free_blocks(ptr, curr->head, NULL);
			return (actually_free(found_b, curr));
		}
		curr->next = free_and_update(curr->next, ptr);
	}
	return (curr);
}

void				free(void *ptr)
{
	g_manager.large = free_and_update_lg(g_manager.large, ptr);
	g_manager.small = free_and_update(g_manager.small, ptr);
	g_manager.tiny = free_and_update(g_manager.tiny, ptr);
}
