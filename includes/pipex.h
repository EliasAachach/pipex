/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:49:22 by elaachac          #+#    #+#             */
/*   Updated: 2021/11/16 15:48:25 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

#ifndef DEFINE_DEBUG_ONCE
#define DEFINE_DEBUG_ONCE

#if DEBUG
  #include <stdio.h>
  #define debug(x, ...)      do{fprintf(stderr, "%s: %s (%u): " x "\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);}while(0)
#else
  #define debug(x, ...)      /* x */
#endif

#endif

typedef struct s_node
{
	char			*cmd;
	char			**args;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list
{
	size_t	length;
	t_node	*head;
	t_node	*tail;
}				t_list;

typedef struct s_path
{
	char	*var_env;
	char	**cmd_path;
	char	**cmd_argv;
	int		cmd_index;
	int		argv_index;
	int		error;
	int		file_error;
}				t_path;

t_node	*add_tail_list(t_list **list, char **cmd);
t_node	*add_head_list(t_list **list, char **cmd);
t_node	*init_node(t_node *node, char **cmd);
t_list	*newlist(void);
int		cmd_manage(t_path *path, t_list **exec, char **envp, char **argv);
void	dellist(t_list **list);
void	ft_bzero(void *s, size_t n);
void	init_list(t_list **args);
void	free_path(t_path *path);
void	file_check(char *pathname, t_path *path);
void	free_split(char **array);
void	stock_args(char **cmd, t_path *path);
void	exec_file_error(t_path *path, t_list **exec, char **envp, char **argv);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		cmd_check(char *pathname, t_path *path);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif