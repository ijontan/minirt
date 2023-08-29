/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:03:48 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 18:13:41 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_parse(char **info, char *s)
{
	if (info)
		free_2darray(info);
	printf("\e[0;31mError: ");
	if (!ft_strncmp(s, "A-r", ft_strlen(s)))
		printf("Ambient lighting ratio out of range [0.0 - 1.0]\e[0m");
	else if (!ft_strncmp(s, "A-c", ft_strlen(s)))
		printf("Ambient lighting color out of range [0 - 255]\e[0m");
		printf("Example expected format: A 0.2 255,60,0\e[0m");
	exit(EXIT_FAILURE);
}
