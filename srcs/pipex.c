/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:51:10 by elaachac          #+#    #+#             */
/*   Updated: 2021/11/16 16:44:31 by elaachac         ###   ########.fr       */
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
	file_check(argv[1], path);
	while (i < argc - 1)
	{
		path->cmd_argv = ft_split(argv[i], ' ');
		path->error += cmd_check(path->cmd_argv[0], path);
		if (path->file_error == 1 || (path->error != 0 && i == 2))
			path->file_error = 2;
		add_tail_list(exec, path->cmd_argv);
		if (path->cmd_argv)
		{
			free_split(path->cmd_argv);
			path->cmd_argv = NULL;
		}
		i++;
	}
	if (path->error > 0)
	{
		open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		free_path(path);
		dellist(exec);
		exit(127);
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
	ft_bzero(path->cmd_path, sizeof(char *) * argc - 3);
	path->cmd_index = 0;
	path->argv_index = 0;
	path->error = 0;
	path->file_error = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_path	path;
	t_list	*exec;

	exec = NULL;
	if (argc != 5)
		return (0);
	init_list(&exec);
	init_path(&path, envp, argc);
	check_args(argc, argv, &path, &exec);
	if (path.file_error == 2)
		exec_file_error(&path, &exec, envp, argv);
	cmd_manage(&path, &exec, envp, argv);
	free_path(&path);
	dellist(&exec);
	return (0);
}
