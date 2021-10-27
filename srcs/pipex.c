/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:51:10 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/27 12:58:10 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
{
	char	**env;

	env = envp;
	while (*env != 0)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			return (*env);
		env++;
	}
	return (NULL);
}

void	check_args(int argc, char **argv, t_path *path)
{
	int		i;
	char	**cmd;

	i = 2;
	file_check(argv[1], path->var_env);
	while (i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (cmd_check(cmd[0], path) == 1)
		{
			free(path->var_env);
			free_split(cmd);
			exit(0);
		}
		i++;
		free_split(cmd);
	}
}

void	free_path(t_path *path)
{
	free(path->var_env);
	free_split(path->cmd_path);
}

void	init_path(t_path *path, char **envp, int argc)
{
	path->var_env = ft_strdup(get_path(envp) + 5);
	path->cmd_path = (char **)malloc(sizeof(char *) * argc - 3);
	path->cmd_index = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_path	path;

	init_path(&path, envp, argc);
	check_args(argc, argv, &path);
	free_path(&path);
	return (0);
}
