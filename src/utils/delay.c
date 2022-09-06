/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:57:14 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/06 10:57:55 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	delay(bool start, unsigned long time)
{
	static struct timeval 	starttime;
	static struct timeval 	endtime;
	unsigned long 			delta_time;

	if (start)
		gettimeofday(&starttime, NULL);
	else if (!start)
	{
		gettimeofday(&endtime, NULL);
		delta_time = (endtime.tv_sec - starttime.tv_sec) * 1000000 + (endtime.tv_usec - starttime.tv_usec);
		if (delta_time < time)
			usleep(time - delta_time);
	}
}