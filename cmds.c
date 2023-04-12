/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:09 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/12 14:46:29 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*find_path(char *cmd)
{
	char	*the_path;
    char    *cmd_temp;
    char    **paths;
    int     i;

    i = -1;
	cmd_temp = ft_strjoin("/", cmd, 0);
    paths = ft_split(getenv("PATH"), ':');
    while (paths[++i])
    {
        the_path = ft_strjoin(paths[i], cmd_temp, 0);
        if (access(the_path, F_OK) == 0)
        {
            freesplit(paths);
            free(cmd_temp);
            return (the_path);
        }
        free (the_path);
	}
    freesplit(paths);
    free (cmd_temp);
	return (NULL);
}

void    execute(char *path, char **cmd)
{
    pid_t	pid;
    
    pid = fork();
	if (pid == -1)
		perror("Error (fork): "); // fix error handling!
	else if (pid == 0)
        execve(path, cmd, NULL);
	else
		waitpid(pid, NULL, 0);
	freesplit(cmd);
    free(path);
}

void	bad_cmd(char *path, char **cmd)
{
	ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(cmd[0], 2);
	freesplit(cmd);
	free(path);
}