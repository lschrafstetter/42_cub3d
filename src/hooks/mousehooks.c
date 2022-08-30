/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:07 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/30 13:32:32 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	hook_mouse(int x, int y, t_data *data)
{
	(void) data;
	printf("x: %i, y: %i\n", x, y);
	return (0);
}
