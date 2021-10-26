/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:18:29 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/26 17:03:24 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_check(char *pathname)
{
	if (access(pathname, F_OK) == -1)
	{
		perror(pathname);
		exit(0);
	}
}

void	cmd_check(char *pathname, char *path_var)
{
	char	**path;
	char	*tmp;
	int		i;
	int		j;
	int		cmd_ok;

	i = 0;
	j = 0;
	cmd_ok = 0;
	path = ft_split(path_var, ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(tmp, pathname);
		free(tmp);
		i++;
	}
	while (--i)
	{
		if (access(path[i], F_OK) != -1)
			cmd_ok = 1;
	}
	if (cmd_ok == 0)
	{
		free_split(path);
		perror(pathname);
		exit(0);
	}
	free_split(path);
}
