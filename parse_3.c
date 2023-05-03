/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:43:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/03 09:54:21 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	env_var_new(t_shell *data, char *new)
{
	char	*var;
	char	*res;
	int		var_len;
	
	var_len = get_cmd(new, -1);
	var = ft_substr(new, 1, var_len - 1);
	res = getenv(var);
	if (res == NULL)
	{
		free(var);
		return(var_len);
	}
	data->res =  ft_strjoin_mod(data->res, res, 0);
	free(var);
	return(var_len);
}

void	check_substr_new(t_shell *data, char *new, char c)
{
	char	*beg;
	int		len;

	if (c == 39)
	{
		data->res = ft_strjoin_mod(data->res, new, 0);
		free(new);
		return ;
	}
	len = ft_strlen(new);
	while(ft_strchr(new, 36) != NULL)
	{
		beg = NULL;
		if (new[0] != 36)
		{
			beg = ft_strchr(new, 36);
			beg = ft_substr(new, 0, len - ft_strlen(beg));
		}
		new = env_var(new, len, beg);
	}
	if (len != 0)
		data->res = ft_strjoin_mod(data->res, new, 0);
	free(new);
}

char	*remove_quotes(char *str, int qte, int arg)
{
	char	*res;
	char	*ptr;
	char	*start;
	char	*end;
	
	ptr = str;
	res = NULL;
	start = ft_strchr(ptr, qte);
	while (start != NULL)
	{
		end = ft_strchr(start + 1, qte);
		if (end)
			ptr = split_n_join(ft_substr(ptr, 0, end - ptr), NULL, qte);
		res = ft_strjoin_mod(res, ptr, 0);
		if (end)
			free(ptr);
		ptr = end + 1;	
		start = ft_strchr(end, qte);
	}
	if (!res)
		res = ft_strdup(str);
	if (arg == 1)
		free(str);
	return (res);
}