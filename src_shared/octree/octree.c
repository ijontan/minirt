/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:31:51 by itan              #+#    #+#             */
/*   Updated: 2023/09/06 15:27:16 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_octree	*octree_new_node(t_bounding_box *box, t_list *objects)
{
	t_octree	*node;

	node = malloc(sizeof(t_octree));
	if (!node)
		return (NULL);
	node->bounding_box = *box;
	node->objects = objects;
	node->children = NULL;
	return (node);
}

t_octree	*octree_new(t_bounding_box *box, t_list *objects)
{
	(void)box;
	(void)objects;
	return (NULL);
}

void	octree_free(t_octree *node)
{
	int	i;

	if (!node)
		return ;
	if (node->children)
	{
		i = -1;
		while (++i < 8)
			octree_free(node->children[i]);
		free(node->children);
	}
	free(node);
}
