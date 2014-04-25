/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/25 16:49:28 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/25 20:47:37 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

void				print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*el;

	i = 0;
	el = (void *)ptr + symoff;
	stringtable = ptr + stroff;
	while (i < nsyms)
	{
		printf("%s\n", stringtable + el[i].n_un.n_strx);
		i++;
	}
}

void				handle_64(char *ptr)
{
	int						n_cmd;
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						i;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	n_cmd = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	while (i < n_cmd)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void				nm(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)	ptr;

	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
}

int					main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (ac != 2)
	{
		fprintf(stderr, "please give me an arg\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		printf("Error Opening File\n");
		return (0);
	}
	if (fstat(fd, &buf) < 0)
	{
		printf("ERROR fstat\n");
		return (0);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("error mmap");
		return (0);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("ERROR munmap");
		return (0);
	}
	return (0);
}

