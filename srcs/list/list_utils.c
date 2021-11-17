/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:40:23 by elaachac          #+#    #+#             */
/*   Updated: 2021/11/17 10:22:43 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*newlist(void)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(*newlist));
	if (newlist == NULL)
		return (NULL);
	if (newlist != NULL)
	{
		newlist->length = 0;
		newlist->head = NULL;
		newlist->tail = NULL;
	}
	return (newlist);
}

void	dellist(t_list **list)
{
	t_node	*tmp;
	t_node	*del;

	if (list != NULL)
	{
		tmp = (*list)->head;
		while ((*list)->length > 0)
		{
			(*list)->length--;
			free_split(tmp->args);
			free(tmp->cmd);
			del = tmp;
			if (tmp->next)
				tmp = tmp->next;
			free(del);
		}
		free(*list);
		*list = NULL;
	}
}

t_node	*init_node(t_node *node, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	i++;
	node->cmd = ft_strdup(cmd[0]);
	node->args = (char **)malloc(sizeof(char *) * i);
	ft_bzero(node->args, sizeof(char *) * i);
	i = 0;
	while (cmd[i])
	{
		node->args[i] = ft_strdup(cmd[i]);
		i++;
	}
	return (node);
}

t_node	*add_head_list(t_list **list, char **cmd)
{
	t_node	*newnode;

	newnode = (t_node *)malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	if ((*list) != NULL)
	{
		if ((*list)->tail == NULL)
		{
			(*list)->head = newnode;
			(*list)->tail = newnode;
			newnode->prev = (*list)->tail;
			newnode->next = (*list)->tail;
		}
		else
		{
			(*list)->head->prev = newnode;
			(*list)->tail->next = newnode;
			newnode->next = (*list)->head;
			newnode->prev = (*list)->tail;
			(*list)->head = newnode;
		}
		(*list)->length++;
	}
	return (init_node(newnode, cmd));
}

t_node	*add_tail_list(t_list **list, char **cmd)
{
	t_node	*newnode;

	newnode = (t_node *)malloc(sizeof(*newnode));
	if (!newnode)
		return (NULL);
	if ((*list) != NULL)
	{
		if ((*list)->tail == NULL)
		{
			(*list)->head = newnode;
			(*list)->tail = newnode;
			newnode->prev = (*list)->head;
			newnode->next = (*list)->head;
		}
		else
		{
			(*list)->head->prev = newnode;
			(*list)->tail->next = newnode;
			newnode->next = (*list)->head;
			newnode->prev = (*list)->tail;
			(*list)->tail = newnode;
		}
		(*list)->length++;
	}
	return (init_node(newnode, cmd));
}
