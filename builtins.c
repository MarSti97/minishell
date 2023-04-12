/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:50:38 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/12 21:01:13 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void    env_cmd(void)
{
    extern char **environ;
    int         i;

    i = -1;
    while (environ[++i])
        printf("%s\n", environ[i]);
}

