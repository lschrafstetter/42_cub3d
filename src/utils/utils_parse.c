/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:34:18 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 16:05:07 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_line(char *str)
{
	if (!ft_strncmp(str, " ", 1))
		return (1);
	if (!ft_strncmp(str, "0", 1))
		return (1);
	if (!ft_strncmp(str, "1", 1))
		return (1);
	if (!ft_strncmp(str, "\n", 1))
		return (1);
	return (0);
}

int	is_no_ea_so_we(char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (1);
	if (!ft_strncmp(str, "EA ", 3))
		return (1);
	if (!ft_strncmp(str, "SO ", 3))
		return (1);
	if (!ft_strncmp(str, "WE ", 3))
		return (1);
	return (0);
}
