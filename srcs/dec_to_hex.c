/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 16:10:47 by gpetrov           #+#    #+#             */
/*   Updated: 2014/04/24 17:00:26 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		if_forest(long int *rem, int len)
{
	if (rem[len] == 10)
        ft_putchar('a');
    else if (rem[len] == 11)
        ft_putchar('b');
    else if (rem[len] == 12)
        ft_putchar('c');
    else if (rem[len] == 13)
        ft_putchar('d');
    else if (rem[len] == 14)
        ft_putchar('e');
    else if (rem[len] == 15)
        ft_putchar('f');
    else
        ft_putchar(rem[len] + '0');
}

void			dec_to_hex(long long int num)
{
    long int    rem[50];
    int         len;
    int         i;

    len = 0;
    i = 0;
	if (num < 16)
		ft_putchar('0');
	if (num == 0)
	{
		ft_putchar('0');
		return ;
	}
    while (num > 0)
    {
        rem[len] = num % 16;
        num /= 16;
        len++;
    }
    while (--len >= 0)
		if_forest(rem, len);
}
