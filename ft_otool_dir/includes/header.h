/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 19:17:10 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/25 21:01:17 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <mach-o/loader.h>
# include "libft.h"

/*
**	Struct
*/

typedef struct		s_data
{
	int				fd;
	size_t			size;
	char			*addr;
	int				jump;
	uint64_t		add_jump;
	unsigned int	i;
	unsigned int	j;
	char			space;
	char			*copy;
}					t_data;

/*
**	Prototypes
*/

void				dec_to_hex(long long int num);
void				error_open(char *file);
void				error_not_object(char *file);
int					ft_otool_finder_obj(t_data *data);
void				otool_text_segment(t_data *data,
					struct segment_command_64 *sc, struct section_64 *sec);
void				ft_otool(char *file, t_data *data);

#endif
