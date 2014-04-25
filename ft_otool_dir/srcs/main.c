/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 18:59:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 18:49:33 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = 0;
	if (ac == 1)
	{
		ft_putstr("[Usage] - ./ft_otool <object file>\n");
		return (0);
	}
	else
	{
		while (av[++i])
			ft_otool(av[i], &data);
	}
	return (0);
}
