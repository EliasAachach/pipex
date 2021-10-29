/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:38:26 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/29 14:45:09 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_cmd(int *fd, t_path *path, char **envp, char **args)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(path->cmd_path[path->cmd_index], args, envp);
	}
	path->cmd_index++;
	return (0);
}

int	cmd_manage(t_path *path, t_list **exec, char **envp, char **argv)
{
	int	fd[4];
	int	ret;

	path->cmd_index = 0;
	ret = 0;
	pipe(fd);
		// dup2(fd[0], STDIN_FILENO);
		// execve(path->cmd_path[path->cmd_index], (*exec)->head->args, envp);
	ret = exec_cmd(fd, path, envp, (*exec)->head->args);
	dup2(fd[0], fd[1]);
	fd[1] = open(argv[2 + (*exec)->length], O_WRONLY | O_CREAT, 0644);
	ret = exec_cmd(fd, path, envp, (*exec)->head->next->args);
	close(fd[0]);
	return (ret);
}
