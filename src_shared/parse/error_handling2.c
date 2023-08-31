/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:40:25 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 23:40:25 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// checks if the float / int format is correct:
// 255: returns true
// 4.0: returns true
// 00.3
// 003
bool	valid_float(char *s)
{
    int i;

    i = 0;
    if (s[i] == '-')
        i++;
    if ((s[i] == '0' && s[i + 1] != '.') || s[i] == '.')
        return (false);
    while (ft_isdigit(s[i]))
        i++;
    if (!s[i])
        return (true);
    if (s[i] == '.')
        i++;
    while (ft_isdigit(s[i]))
        i++;
    if (s[i])
        return (false);
	return (true);
}

static bool	check_triplet_size(char **val)
{
	int	i;

	i = 0;
	while (val[i])
		i++;
	if (i == 3)
		return (true);
	return (false);
}

// checks if the triplet (x, y, z) is correct:
bool	valid_triplet(char *s)
{
    char    **val;
    int     i;

    val = ft_split(s, ',');
    i = -1;
    if (!check_triplet_size(val))
    {
        free_2darray(val);
        return (false);
    }
    while (++i < 3)
    {
        if (!valid_float(val[i]))
        {
            free_2darray(val);
            return (false);
        }
    }
    free_2darray(val);
	return (true);
}

// #include <stdbool.h>
// #include <stdio.h>

// bool ft_isdigit(char n)
// {
//     return (n >= '0' && n <= '9');
// }

// int main(int ac, char **av)
// {
//     (void)ac;
//     printf("%d\n", valid_float(av[1]));
//     printf("%d\n", valid_triplet(av[1]));
// }
