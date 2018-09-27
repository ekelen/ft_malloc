/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2018/09/27 13:37:31 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include <string.h>

void		print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{

    char **addrs;
    char **addrs2;
    addrs = (char**)malloc(sizeof(char*)*100);
    addrs2 = (char**)malloc(sizeof(char*)*100);

    int i;
    for (i = 0; i < 100; i++)
    {
        addrs[i] = (char*)malloc(sizeof(char) * 11);
        addrs2[i] = NULL;
        strcpy(addrs[i], "123456789\n");
    }
    ft_putstr("\n---------total # 1 ------------\n");
    show_alloc_mem();

    ft_putstr("\n---------total # 2: tinies should be same ------------\n");
    for (i = 0; i < 100; i++)
    {
        addrs2[i] = realloc(addrs[i], sizeof(char) * 11);
    }
	show_alloc_mem();

    for (i = 0; i < 100; i++)
    {
        free(addrs[i]);
        free(addrs2[i]);
    }

    free(addrs);
    free(addrs2);
    ft_putstr("\n---------should be a no tiny/size 11 and no size 800 ------------\n");
    show_alloc_mem();
	return (0);
}
