/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:38:26 by elaachac          #+#    #+#             */
/*   Updated: 2021/11/16 16:10:25 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_file_error(t_path *path, t_list **exec, char **envp, char **argv)
{
	int fd[3];

	pipe(fd);
	close(fd[1]);
	fd[2] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd[2], STDOUT_FILENO);
	close(fd[2]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[2]);
	execve(path->cmd_path[path->cmd_index - 1], (*exec)->tail->args, envp);
}

void	exec_last_cmd(int *fd, t_path *path, char **envp, char **args)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[3]);
	execve(path->cmd_path[path->cmd_index], args, envp);
}

int	exec_cmd(int *fd, t_path *path, char **envp, char **args)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[2], STDIN_FILENO);
		close(fd[2]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path->cmd_path[path->cmd_index], args, envp);
	}
	path->cmd_index++;
	return (0);
}

int	cmd_manage(t_path *path, t_list **exec, char **envp, char **argv)
{
	int	fd[6];
	int	ret;

	fd[2] = open(argv[1], O_RDONLY);
	fd[3] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	fd[4] = dup(STDIN_FILENO);
	fd[5] = dup(STDOUT_FILENO);
	path->cmd_index = 0;
	ret = 0;
	pipe(fd);
	ret = exec_cmd(fd, path, envp, (*exec)->head->args);
	exec_last_cmd(fd, path, envp, (*exec)->tail->args);
	close(fd[0]);
	return (ret);
}
