/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:18:29 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/27 12:48:58 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_check(char *pathname, char *path)
{
	if (access(pathname, F_OK) == -1)
	{
		free(path);
		perror(pathname);
		exit(0);
	}
}

int	cmd_check2(int cmd_ok, char **path, char *pathname)
{
	if (cmd_ok == 0)
	{
		free_split(path);
		perror(pathname);
		return (1);
	}
	free_split(path);
	return (0);
}

int	cmd_check(char *pathname, t_path *path)
{
	char	**env_path;
	char	*tmp;
	int		i;
	int		cmd_ok;

	i = -1;
	cmd_ok = 0;
	env_path = ft_split(path->var_env, ':');
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		free(env_path[i]);
		env_path[i] = ft_strjoin(tmp, pathname);
		free(tmp);
	}
	while (--i)
	{
		if (access(env_path[i], F_OK) != -1)
		{
			path->cmd_path[path->cmd_index] = ft_strdup(env_path[i]);
			path->cmd_index++;
			cmd_ok = 1;
		}
	}
	return (cmd_check2(cmd_ok, env_path, pathname));
}
