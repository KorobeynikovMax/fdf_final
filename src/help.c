/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:13:29 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 15:35:26 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			ft_isdigithex(char c)
{
	char			*digits;
	int				i;

	i = 0;
	digits = "0123456789ABCDEF";
	while (i < 16)
	{
		if (digits[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}

int					ft_atoihex(char *str)
{
	size_t			i;
	unsigned long	result;

	i = 0;
	result = 0;
	if (str[i] != '0' || !(str[i + 1] == 'x' || str[i + 1] == 'X'))
		fdf_exit("error: hex color reading.");
	i += 2;
	while (ft_isdigithex(str[i]) > -1)
	{
		result = result * 16 + ft_isdigithex(str[i]);
		i++;
	}
	return (result);
}

void				list_put(t_list_z **coordinates, t_list_z *new)
{
	if (coordinates)
	{
		if (new)
			new->next = *coordinates;
		*coordinates = new;
	}
}

t_list_z			*list_get(t_list_z **coordinates)
{
	t_list_z		*top;

	top = NULL;
	if (coordinates && *coordinates)
	{
		top = *coordinates;
		*coordinates = (*coordinates)->next;
	}
	return (top);
}

void				fdf_exit(char *reason)
{
	ft_putstr(reason);
	ft_putchar('\n');
	exit(1);
}
