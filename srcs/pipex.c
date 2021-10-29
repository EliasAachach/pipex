/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:51:10 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/29 12:23:18 by elaachac         ###   ########.fr       */
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

void	check_args(int argc, char **argv, t_path *path, t_list **exec)
{
	int		i;

	i = 2;
	file_check(argv[1], path->var_env);
	while (i < argc - 1)
	{
		path->cmd_argv = ft_split(argv[i], ' ');
		if (cmd_check(path->cmd_argv[0], path) == 1)
		{
			free(path->var_env);
			free_split(path->cmd_argv);
			exit(0);
		}
		add_tail_list(exec, path->cmd_argv);
		// stock_args(path->cmd_argv, path);
		i++;
		// free_split(path->cmd_argv);
	}
}

void	free_path(t_path *path)
{
	if (path->var_env)
		free(path->var_env);
	if (path->cmd_path)
		free_split(path->cmd_path);
	if (path->cmd_argv)
		free_split(path->cmd_argv);
}

void	init_path(t_path *path, char **envp, int argc)
{
	path->var_env = ft_strdup(get_path(envp) + 5);
	path->cmd_path = (char **)malloc(sizeof(char *) * argc - 3);
	path->cmd_argv = (char **)malloc(sizeof(char *) * argc - 3);
	// path->cmd_argv[0] = NULL;
	path->cmd_index = 0;
	path->argv_index = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_path	path;
	t_list	*exec;

	exec = NULL;
	init_list(&exec);
	init_path(&path, envp, argc);
	check_args(argc, argv, &path, &exec);
	cmd_manage(&path, &exec, envp, argv);
	free_path(&path);
	dellist(&exec);
	return (0);
}
