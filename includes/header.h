/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 19:17:10 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 13:46:40 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

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
	
}					t_data;

#endif
