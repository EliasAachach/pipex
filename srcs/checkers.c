/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:18:29 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/22 01:09:15 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_file(char *pathname)
{
	if (access(pathname, F_OK) == -1)
	{
		perror(pathname);
		exit(0);
	}
}
