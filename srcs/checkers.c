/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:18:29 by elaachac          #+#    #+#             */
/*   Updated: 2021/11/15 18:14:08 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_check(char *pathname, char *file_path, t_path *path)
{
	if (access(pathname, F_OK) == -1)
	{
		free(file_path);
		file_path = NULL;
		if (path->error == 0)
		{
			perror(pathname);
			path->error = 1;
		}
		exit(0);
	}
}

int	cmd_check2(int cmd_ok, char **env_path, char *pathname, t_path *path)
{
	if (cmd_ok == 0)
	{
		free_split(path->cmd_path);
		free_split(env_path);
		if (path->error == 0)
		{
			write(2, pathname, ft_strlen(pathname));
			write(2, " : Command not found\n", 21);
			path->error = 1;
		}
		return (1);
	}
	else
		free_split(env_path);
	return (0);
}

void	cmd_check3(int i, int *cmd_ok, char **env_path, t_path *path)
{
	while (--i)
	{
		if (access(env_path[i], F_OK) != -1)
		{
			path->cmd_path[path->cmd_index] = ft_strdup(env_path[i]);
			path->cmd_index++;
			*cmd_ok = 1;
			break ;
		}
	}
}

int	cmd_check(char *pathname, t_path *path)
{
	char	**env_path;
	char	*tmp;
	int		i;
	int		cmd_ok;

	path->error = 0;
	i = -1;
	cmd_ok = 0;
	tmp = NULL;
	env_path = NULL;
	env_path = ft_split(path->var_env, ':');
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		free(env_path[i]);
		env_path[i] = NULL;
		env_path[i] = ft_strjoin(tmp, pathname);
		free(tmp);
	}
	cmd_check3(i, &cmd_ok, env_path, path);
	return (cmd_check2(cmd_ok, env_path, pathname, path));
}
