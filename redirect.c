/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:24:52 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/10 11:23:37 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_in(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '<')
		flag = 1;
	while (new[sp + flag] == 32)
		sp++;
	data->len = space(data, new + sp + flag, 1);
	if (data->res == NULL)
	{
		error("Syntax error", 2);
		data->exit_flag = 1;
	}
	else if (flag == 1)
		g_glob.here_flag = here_doc(data);
	else
		open_it(data);
	freedom("a", data->res);
	return (data->len + flag + sp);
}

int	file_out(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '>')
		flag = 1;
	while (new[sp + flag] == 32)
		sp++;
	data->len = space(data, new + sp + flag, 1);
	if (data->res == NULL)
	{
		error("Syntax error", 2);
		data->exit_flag = 1;
	}
	else
	{
		data->out_flag = 1;
		store_it(data, flag);
		free(data->res);
	}
	return (data->len + flag + sp);
}

void	open_it(t_shell *data)
{
	data->fd[0] = open(data->res, O_RDONLY);
	if (data->fd[0] < 0)
	{
		error("Error", 1);
		data->cmd = freedom("s", data->cmd);
	}
}