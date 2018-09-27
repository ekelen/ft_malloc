/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2018/09/27 13:20:01 by ekelen           ###   ########.fr       */
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
    addrs = (char**)malloc(sizeof(char*)*100);

    int i;
    for (i = 0; i < 100; i++)
    {
        addrs[i] = (char*)malloc(sizeof(char) * 11);
        strcpy(addrs[i], "123456789\n");
    }

	ft_putstr("\n---------should be a lot of tiny/size 11------------\n");
	show_alloc_mem();

    for (i = 0; i < 100; i++)
    {
        free(addrs[i]);
    }

    free(addrs);
    ft_putstr("\n---------should be a no tiny/size 11------------\n");
    show_alloc_mem();
	return (0);
}
