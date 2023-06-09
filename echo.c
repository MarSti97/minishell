/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:19:26 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_shell *data, char **cmd)
{
	int	f;
	int	checker;

	f = 0;
	checker = 0;
	while (cmd[++f])
	{
		if (ft_strncmp(cmd[f], "-n", 3) == 0)
			checker = 1;
		else
			break ;
	}
	while (cmd[f])
	{
		printf("%s", cmd[f]);
		if (cmd[f + 1])
			printf(" ");
		f++;
	}
	if (!checker)
		printf("\n");
	keep_history(NULL, 2);
	data = freedom("da", data, data);
	exit (0);
}

int	strintchr(char	*str, int c)
{
	int	f;

	f = 0;
	while (str[f] && str[f] != c)
		f++;
	if (!str[f])
		f = 0;
	return (f);
}

char	**read_folder(char *str)
{
	char			**folder;
	DIR				*dir;
	struct dirent	*entry;
	int				f;
	char			*dir_name;

	dir_name = ft_strjoin_mod(this_folder_is(1), "/", 0);
	dir = opendir(dir_name);
	free (dir_name);
	folder = NULL;
	if (dir)
	{
		f = strintchr(str, '*');
		entry = readdir(dir);
		while (entry != NULL)
		{
			folder = read_folder_2(entry, str, folder, f);
			entry = readdir(dir);
		}
		closedir(dir);
		return (folder);
	}
	else
		return (NULL);
}

char	**read_folder_2(struct dirent *entry, char *str, char **folder, int f)
{
	if (ft_strncmp(entry->d_name, str, f) == 0 \
		&& back_check(entry->d_name, str) == 0)
	{
		if (!folder)
			folder = ft_split(entry->d_name, 1);
		else
			folder = add_split(folder, entry->d_name);
	}
	return (folder);
}

int	back_check(char *str, char *check)
{
	int	i;
	int	f;

	i = ft_strlen(check);
	f = ft_strlen(str);
	while (i > 0)
	{
		if (check[i] == '*')
			break ;
		if (check[i] != str[f])
			return (i);
		i--;
		f--;
	}
	return (0);
}
