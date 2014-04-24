/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 18:59:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 13:48:55 by gpetrov          ###   ########.fr       */
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


void		ft_file_error(char *file)
{
	ft_putstr("nm: can't open file: ");
	ft_putstr(file);
	ft_putstr(" (No such file or directory)\n");
}

void        ft_otool(char *file, t_data *data)
{
    struct stat stat_buf;
	struct mach_header_64 *mh;
    struct load_command *lc;
    struct segment_command_64 *sc;
    struct section_64 *sect;

	data->space = '0';
    data->fd = open(file, O_RDONLY);
    fstat(data->fd, &stat_buf);
    data->size = stat_buf.st_size;

    data->addr = mmap(0, data->size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, data->fd, 0);
	char *copy = data->addr;
    mh = (struct mach_header_64 *)data->addr;

    data->addr += sizeof(struct mach_header_64);

	ft_putstr(file);
	ft_putstr(":\n");
	data->j = 0;
    while (data->j < mh->ncmds) 
	{
        lc = (struct load_command *)data->addr;
        if (lc->cmd == LC_SEGMENT_64) {
			sc = (struct segment_command_64 *)data->addr;
			if (ft_strcmp(sc->segname, "__TEXT") == 0)
			{
				ft_putstr("(__TEXT,");
				data->i = 1;
				data->addr += sizeof(struct segment_command_64);
				while (data->i <= sc->nsects)
				{
					sect = (struct section_64 *)data->addr;
					data->addr += sizeof(struct section_64);
					if (ft_strcmp(sect->sectname, "__text") == 0)
					{	printf("__text) section\n");
						 printf("0000000%llx ", sect->addr);
						data->add_jump = sect->addr;
						copy += sect->offset;
						data->i = 0;
						data->jump = 0;
						while (data->i < sect->size)
						{
							if (data->jump == 16)
							{
								data->jump = 0;
								data->add_jump += 16;
								printf("\n0000000%llx ", data->add_jump);
								data->space = '0';

							}
							if (data->space == '0')
							{
								printf("%.2x", copy[data->i]);
								data->space = '1';
							}
							else
								printf(" %.2x", copy[data->i]);
							data->jump++;
							data->i++;
						}
					}
					data->i++;
				}
				
				return ;
			}
		}
        data->addr += lc->cmdsize;
		data->j++;
    }

    printf("\nDone.\n");

    munmap(data->addr, data->size);
    close(data->fd);
}

int			main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = 0;
	(void) ac;
	if (ac == 1)
		ft_otool("a.out", &data);
	else
	{
		while (av[++i])
			ft_otool(av[i], &data);
	}
	return (0);
}
