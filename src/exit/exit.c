/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:39:32 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 11:28:11 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	cub_exit(t_data *data, int exit_code)
{
	free_all(data);
	exit(exit_code);
}
