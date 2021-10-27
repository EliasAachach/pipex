/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:49:22 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/27 15:44:30 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_path
{
	char	*var_env;
	char	**cmd_path;
	int		cmd_index;
}				t_path;

void	ft_bzero(void *s, size_t n);
void	free_path(t_path *path);
void	file_check(char *pathname, char *path);
void	free_split(char **array);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		cmd_check(char *pathname, t_path *path);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif