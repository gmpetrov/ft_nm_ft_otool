/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 18:59:21 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 00:20:48 by gpetrov          ###   ########.fr       */
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

void        ft_nm(char *file)
{
    int fd;
    struct stat stat_buf;
    size_t size;

    char *addr = NULL;
    struct mach_header_64 *mh;
    struct load_command *lc;
    struct segment_command_64 *sc;
    struct section_64 *sect;

    // Open the file and get its size
    fd = open(file, O_RDONLY);
    fstat(fd, &stat_buf);
    size = stat_buf.st_size;

    // Map the file to memory
    addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);
	char *copy = addr;
    // The first bytes of a Mach-O file comprise its header
    mh = (struct mach_header_64 *)addr;

    // Load commands follow the header
    addr += sizeof(struct mach_header_64);

    printf("There are %d load commands\n", mh->ncmds);

    for (int i = 0; (unsigned int)i < mh->ncmds; i++) {
        lc = (struct load_command *)addr;
		
		if (lc->cmdsize == 0) continue;

        // If the load command is a (64-bit) segment,
        // print information about the segment
        if (lc->cmd == LC_SEGMENT_64) {
			sc = (struct segment_command_64 *)addr;
			if (ft_strcmp(sc->segname, "__TEXT") == 0)
			{

				 printf("Segment %s\n\t"
                "vmaddr 0x%llx\n\t"
                "vmsize 0x%llx\n\t"
                "fileoff %llu\n\t"
                "filesize %llu\n\t"
                "nb_sections %d\n",
                sc->segname,
                sc->vmaddr,
                sc->vmsize,
                sc->fileoff,
                sc->filesize,
                sc->nsects);
				unsigned int i = 1;
				addr += sizeof(struct segment_command_64);
				while (i <= sc->nsects)
				{
					sect = (struct section_64 *)addr;
					addr += sizeof(struct section_64);
					if (ft_strcmp(sect->sectname, "__text") == 0)
					{	
						 printf("Section %s\n\t"
						"segname %s\n\t"
						"addr 0x%llx\n\t"
						"size %llx\n\t"
						"offset %d\n\t"
						"align %d\n",
						sect->sectname,
						sect->segname,
						sect->addr,
						sect->size,
						sect->offset,
						sect->align);

						copy += sect->offset;
						unsigned int  i = 0;
						while (i < sect->size)
						{
							printf("size =  %llx\n", sect->size);
							printf("TEST %x\n", copy[i]);
							i++;
						}

				}
					i++;
				}
				
				return ;
		}
	}
	        // Advance to the next load command    
        addr += lc->cmdsize;
    }

    printf("\nDone.\n");

    munmap(addr, size);
    close(fd);
}

/*
void		ft_nm(char *file)
{
    struct stat    test;


	if (open(file, O_RDONLY) >= 0)
	{
		write(1, file, ft_strlen(file));
		write(1, "\n", 1);
	}
	else
    {
		ft_file_error(file);
        return ;
    }
    stat(file, &test);
    printf("peripherique : %d\n", test.st_dev);
    printf("proprietaire : %d\n", test.st_uid);
    printf("stat : %lld\n", test.st_size);
}
*/
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
