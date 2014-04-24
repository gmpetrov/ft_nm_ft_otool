/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 17:12:25 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 18:32:09 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <mach-o/loader.h>
#include "header.h"

void	error_open(char *file)
{
	ft_putstr("ft_otool: can't open file: ");
	ft_putstr(file);
	ft_putstr(" (No such file or directory)\n");
}

void	error_not_object(char *file)
{
	ft_putstr(file);
	ft_putstr(" is not an object file\n");
}

int		ft_otool_finder_obj(t_data *data)
{
	struct load_command			*lc;
	struct segment_command_64	*sc;
	struct section_64			*sect;

	sect = NULL;
	lc = (struct load_command *)data->addr;
	if (lc->cmd == LC_SEGMENT_64)
	{
		sc = (struct segment_command_64 *)data->addr;
		otool_text_segment(data, sc, sect);
		munmap(data->addr, data->size);
		close(data->fd);
		return (-1);
	}
	data->addr += lc->cmdsize;
	data->j++;
	return (0);
}
