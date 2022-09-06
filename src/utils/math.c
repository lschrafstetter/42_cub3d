/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:22:47 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 14:26:28 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	math_free(t_math *math)
{
	if (math->sin)
		free(math->sin);
	if (math->cos)
		free(math->cos);
	if (math->tan)
		free(math->tan);
	free(math);
	math = NULL;
}

t_math	*math_init(void)
{
	t_math	*math;
	int		i;

	math = malloc(sizeof(t_math));
	if (!math)
		return(NULL);
	math->sin = malloc(sizeof(double) * 360);
	math->cos = malloc(sizeof(double) * 360);
	math->tan = malloc(sizeof(double) * 360);
	if (!(math->sin) || !(math->cos) || !(math->tan))
	{
		math_free(math);
		return (NULL);
	}
	i = 0;
	while (i < 360)
	{
		math->sin[i] = fabs(sin((double)i / 180 * M_PI));
		math->cos[i] = fabs(cos((double)i / 180 * M_PI));
		math->tan[i] = fabs(tan((double)i / 180 * M_PI));
		i++;
	}
	return (math);
}
