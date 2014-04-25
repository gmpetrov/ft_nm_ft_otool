/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_arch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeets <wbeets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/25 22:55:25 by wbeets            #+#    #+#             */
/*   Updated: 2014/04/25 23:51:04 by wbeets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		read_header(int fd)
{
	int		i;
	int		j;
	char	str[61];
	char	*num;

	i = 3;
	if (read(fd, &str, 60) < 0)
	{
		ft_putstr("error");
	}
		while (str[i] > '0' && str[i] < '9')
			i++;
		num = (char *)malloc((i + 1) * sizeof(char));
		i = 3;
		j = 0;
		while (str[i] > '0' && str[i] < '9')
		{
			num[j] = str[i];
			i++;
			j++;
		}
		num[j] = '\0';
		j = ft_atoi(num);
		free(num);
		num = (char *)malloc((j + 1) * sizeof(char));
		num[j] = '\0';
		read(fd, num, j);
		ft_putstr(num);
	ft_putstr(str);
	return (0);
}

int	check_if_arch(char *file)
{
	int		fd;
	char	str[9];

	str[8] = '\0';
	fd = open(file, O_RDONLY);
	read(fd, &str, 8);

	if (ft_strcmp(str, "!<arch>\n") == 0)
	{
		ft_putstr("i am an archive file\n");
		read_header(fd);
		return (1);
	}
	close(fd);
	return (0);
}
