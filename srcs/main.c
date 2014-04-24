/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 18:59:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 18:36:41 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <mach-o/loader.h>
#include <sys/mman.h>
#include <stab.h>
#include <nlist.h>
#include "header.h"

int		data_init(t_data *data, struct stat *buf, char *file)
{
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
	{
		error_open(file);
		return (-1);
	}
	data->space = '0';
	fstat(data->fd, buf);
    data->size = buf->st_size;
    data->addr = mmap(0, data->size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, data->fd, 0);
	data->copy = data->addr;
	data->j = 0;
	data->i = 1;
	data->jump = 0;
	data->addr += sizeof(struct mach_header_64);
	return (0);
}

static void		otool_text_section(t_data *data)
{
	if (data->jump == 16)
	{
		data->jump = 0;
		data->add_jump += 16;	
		ft_putstr("\n0000000");
		dec_to_hex(data->add_jump);
		ft_putchar(' ');
		data->space = '0';
	}
	if (data->space == '0')
	{
		dec_to_hex(data->copy[data->i] & 0xff);
		data->space = '1';
	}
	else
	{
		write(1, " ", 1);
		dec_to_hex(data->copy[data->i] & 0xff);
	}
}

void	otool_text_segment
(t_data *data, struct segment_command_64 *sc, struct section_64 *sect)
{
	ft_putstr("(__TEXT,");
	data->addr += sizeof(struct segment_command_64);
	while (data->i <= sc->nsects)
	{
		sect = (struct section_64 *)data->addr;
		data->addr += sizeof(struct section_64);
		if (ft_strcmp(sect->sectname, "__text") == 0)
		{	ft_putstr("__text) section\n");
			ft_putstr("0000000");
			dec_to_hex(sect->addr);
			ft_putchar(' ');
			data->add_jump = sect->addr;
			data->copy += sect->offset;
			data->i = 0;
			while (data->i < sect->size)
			{
				otool_text_section(data);	
				data->jump++;
				data->i++;
			}
		}
		data->i++;
	}
	write(1, "\n", 1);	
}

static int	ft_otool_finder(t_data *data)
{
	struct load_command			*lc;
    struct segment_command_64	*sc;
    struct section_64			*sect;

	sect = NULL;
	lc = (struct load_command *)data->addr;
    if (lc->cmd == LC_SEGMENT_64)
	{
		sc = (struct segment_command_64 *)data->addr;
		if (ft_strcmp(sc->segname, "__TEXT") == 0)
		{
				otool_text_segment(data, sc, sect);
				munmap(data->addr, data->size);
				close(data->fd);
				return (-1);
		}
	}
    data->addr += lc->cmdsize;
	data->j++;
	return (0);
}

void        ft_otool(char *file, t_data *data)
{
    struct stat				buf;
	struct mach_header_64	*mh;
    
	if (data_init(data, &buf, file) == -1)
		return ;
	mh = (struct mach_header_64 *)data->addr;
	if (mh->magic != 25)
	{
		error_not_object(file);
		return ;
	}
    ft_putstr(file);
	ft_putstr(":\n");
	if (mh->filetype == MH_OBJECT)
	{
		ft_otool_finder_obj(data);
		return ;	
	}
    while (data->j < mh->ncmds) 
	{
		if (ft_otool_finder(data) == -1)
			return ;
	}
}

int			main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = 0;
	(void) ac;
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
