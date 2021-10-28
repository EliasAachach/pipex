/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:38:26 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/28 17:39:18 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd(int *fd, t_path *path, char **envp, char **args)
{
	pid_t	child;

	fd[0] += 0;
	child = fork();
	if (child == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(path->cmd_path[path->cmd_index++], args, envp);
	}
	return (0);
}

int	cmd_manage(t_path *path, t_list **exec, char **envp, char **argv)
{
	int	fd[2];
	int	ret;

	path->cmd_index = 0;
	ret = 0;
	pipe(fd);
	fd[0] = open(argv[1], O_RDONLY);
	ret = exec_cmd(fd, path, envp, (*exec)->head->args);
	fd[1] = open(argv[2 + (*exec)->lenght], O_WRONLY | O_CREAT, 0644);
	ret = exec_cmd(fd, path, envp, (*exec)->head->args);
	close(fd[0]);
	return (ret);
}
