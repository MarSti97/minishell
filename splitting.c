/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 06:48:55 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/07 21:05:25 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int word_count(char **split);

char	**add_split(char **split, char *new, int arg)
{
    int     i;
    int     len;
    char    **new_split;

    if (split[0] == NULL) // this might not be needed now its fixed
        return (ft_split(new, 32));
    i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * (i + 2));
    if (!new_split)
		return (0);
    i = -1;
    while (split[++i])
    {
        len = ft_strlen(split[i]);
        new_split[i] = ft_calloc(len + 1, sizeof(char));
        ft_strlcpy(new_split[i], split[i], len + 1);
    }
    len = ft_strlen(new);
    new_split[i] = ft_calloc(len + 1, sizeof(char));
	if (len > 0)
    	ft_strlcpy(new_split[i], new, len + 1);
    new_split[++i] = NULL;
	if (!arg)
    	freesplit(split);
    return(new_split);
}

char	**copy_split(char **split, int arg)
{
    int     i;
    int     len;
    char    **new_split;

    i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * (i + 1));
    if (!new_split)
		return (0);
    i = -1;
    while (split[++i])
    {
        len = ft_strlen(split[i]);
        new_split[i] = ft_calloc(len + 1, sizeof(char));
        ft_strlcpy(new_split[i], split[i], len + 1);
    }
    new_split[i] = NULL;
	if (!arg)
    	freesplit(split);
    return(new_split);
}

char	**remove_split(char **split, char *rem, int arg)
{
    int     i;
	int		f;
    int     len;
    char    **new_split;

    i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * i);
    if (!new_split)
		return (0);
    i = -1;
	f = -1;
    while (split[++i])
    {
		if ((ft_strncmp(split[i], rem, ft_strlen(rem)) != 0))
		{
			len = ft_strlen(split[i]);
			new_split[++f] = ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(new_split[f], split[i], len + 1);
		}
    }
    new_split[++f] = NULL;
	if (!arg)
    	freesplit(split);
    return(new_split);
}

char	**modify_split(char **split, char *mod, int arg, int flag)
{
    int     i;
	int		f;
    int     len;
    char    **new_split;

    i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * i);
    if (!new_split)
		return (0);
    i = -1;
	f = -1;
    while (split[++i])
    {
		if ((ft_strncmp(split[i], mod, strintchr(mod, flag) - 1) != 0))
		{
			len = ft_strlen(split[i]);
			new_split[++f] = ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(new_split[f], split[i], len + 1);
		}
		else
			new_split[++f] = mod;
    }
    new_split[++f] = NULL;
	if (!arg)
    	freesplit(split);
    return(new_split);
}

static int word_count(char **split)
{
    int i;

    i = 0;
    while (split[i])
        i++;
    return (i);
}

char	*split_n_join(char *str, char **split, int spliter)
{
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	if (!split)
		split = ft_split(str, spliter);
	if (split[1] != NULL)
	{
		while(split[++i])
			res = ft_strjoin_mod(res, split[i], 0);
	}
	else 
		res = ft_strdup(split[0]);
	freedom("sa", split, str);
	return (res);
}
