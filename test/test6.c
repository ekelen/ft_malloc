/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2018/09/27 13:19:59 by ekelen           ###   ########.fr       */
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
    addrs = (char**)malloc(sizeof(char*)*10000);

    int i;
    for (i = 0; i < 10000; i++)
    {
        addrs[i] = (char*)malloc(sizeof(char) * 11);
        strcpy(addrs[i], "123456789\n");
        free(addrs[i]);
    }

	ft_putstr("\n---------should be no tiny/size 11()------------\n");
	show_alloc_mem();

    free(addrs);
	return (0);
}
