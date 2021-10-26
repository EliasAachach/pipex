/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:51:10 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/26 16:30:35 by elaachac         ###   ########.fr       */
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

void	check_args(int argc, char **argv, char *path_var)
{
	int		i;
	char	**cmd;

	i = 2;
	file_check(argv[1]);
	while (i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		cmd_check(cmd[0], path_var);
		i++;
		free_split(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*path_var;

	path_var = ft_strdup(get_path(envp) + 5);
	check_args(argc, argv, path_var);
	free(path_var);
	return (0);
}
