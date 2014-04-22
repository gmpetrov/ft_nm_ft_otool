/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 18:59:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/22 19:43:49 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "header.h"

void		ft_file_error(char *file)
{
	ft_putstr("nm: can't open file: ");
	ft_putstr(file);
	ft_putstr(" (No such file or directory)\n");
}

void		ft_nm(char *file)
{
	if (open(".", O_RDONLY) != -1)
	{
		write(1, file, ft_strlen(file));
		write(1, "\n", 1);
	}
	else
		ft_file_error(file);
}

int			main(int ac, char **av)
{
	int		i;

	i = 0;
	(void) ac;
	if (ac == 1)
		ft_nm("a.out");
	else
	{
		while (av[++i])
			ft_nm(av[i]);
	}
	return (0);
}
