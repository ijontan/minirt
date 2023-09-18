/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:22:28 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 11:46:35 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_object(t_list **objects, void *object, unsigned char type)
{
	t_list		*new;
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return ;
	obj->object = object;
	obj->type = type;
	new = ft_lstnew(obj);
	if (!new)
	{
		free(obj);
		return ;
	}
	new->content = obj;
	ft_lstadd_front(objects, new);
}

/*
do something

typedef void	(*t_ft)(void *);

eg1:
void	funtion(void *objects)
{
	t_object	*obj;
	const t_ft	fun_ptr[3] = {&ft_example, &ft_example, &ft_example};

	obj = objects;
	fun_ptr[obj->type](obj->object);
}

use
ft_lstiter(objects, funtion);

eg2:
void	function(t_list *objects)
{
	t_object	*obj;
	const t_ft	fun_ptr[3] = {&ft_example, &ft_example, &ft_example};

	while (objects)
	{
		obj = objects->content;
		fun_ptr[obj->type](obj->object);
		objects = objects->next;
	}
} 
*/
