/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:51:10 by elaachac          #+#    #+#             */
/*   Updated: 2021/10/22 00:28:47 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    check_args(char **argv)
{
	check_file(argv[1]);
	check_file(argv[4]);
}

int main(int argc, char **argv)
{
	check_args(argv);
	return (0);
}
