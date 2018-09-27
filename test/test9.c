/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2018/09/27 13:41:08 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include <string.h>
#include <limits.h>

void		print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{

    char **addrs;

    addrs = (char**)malloc(sizeof(char)*10);

    int i;
    for (i = 0; i < 100; i++)
    {
        addrs[i] = (char*)malloc(sizeof(char) * UINT_MAX);
    }
    ft_putstr("\n--------- should be many huge things ------------\n");
    show_alloc_mem();

    ft_putstr("\n--------- should be all free ------------\n");


    for (i = 0; i < 100; i++)
    {
        free(addrs[i]);
    }

    free(addrs);
    show_alloc_mem();
	return (0);
}
