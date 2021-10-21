/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:51:10 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/21 19:50:50 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    check_args(char **argv)
{
	if (access(argv[1], F_OK) == -1)
	{
		printf("ERROR\n");
		exit (0);
	}
	if (access(argv[4], F_OK) == -1)
	{
		printf("ERROR\n");
		exit (0);
	}
}

int main(int argc, char **argv)
{
	check_args(argv);
	return (0);
}
