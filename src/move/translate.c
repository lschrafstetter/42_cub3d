/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:41:44 by lschrafs          #+#    #+#             */
/*   Updated: 2022/09/09 11:55:59 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	translate_forward(t_data *data)
{
	if (data->player->dir_int > 0 && data->player->dir_int < 90)
		translate_diagonal_q1(data);
	else if (data->player->dir_int > 90 && data->player->dir_int < 180)
		translate_diagonal_q2(data);
	else if (data->player->dir_int > 180 && data->player->dir_int < 270)
		translate_diagonal_q3(data);
	else if (data->player->dir_int > 270)
		translate_diagonal_q4(data);
	else if (data->player->dir_int == 0)
		translate_parallel_x_pos(data, MOV_STEP);
	else if (data->player->dir_int == 90)
		translate_parallel_y_neg(data, MOV_STEP);
	else if (data->player->dir_int == 180)
		translate_parallel_x_neg(data, MOV_STEP);
	else if (data->player->dir_int == 270)
		translate_parallel_y_pos(data, MOV_STEP);
}

static void	translate_backward(t_data *data)
{
	if (data->player->dir_int > 0 && data->player->dir_int < 90)
		translate_diagonal_q3(data);
	else if (data->player->dir_int > 90 && data->player->dir_int < 180)
		translate_diagonal_q4(data);
	else if (data->player->dir_int > 180 && data->player->dir_int < 270)
		translate_diagonal_q1(data);
	else if (data->player->dir_int > 270)
		translate_diagonal_q2(data);
	else if (data->player->dir_int == 0)
		translate_parallel_x_neg(data, MOV_STEP);
	else if (data->player->dir_int == 90)
		translate_parallel_y_pos(data, MOV_STEP);
	else if (data->player->dir_int == 180)
		translate_parallel_x_pos(data, MOV_STEP);
	else if (data->player->dir_int == 270)
		translate_parallel_y_neg(data, MOV_STEP);
}

static void	translate_right(t_data *data)
{
	if (data->player->dir_int > 0 && data->player->dir_int < 90)
		translate_diagonal_q4(data);
	else if (data->player->dir_int > 90 && data->player->dir_int < 180)
		translate_diagonal_q1(data);
	else if (data->player->dir_int > 180 && data->player->dir_int < 270)
		translate_diagonal_q2(data);
	else if (data->player->dir_int > 270)
		translate_diagonal_q3(data);
	else if (data->player->dir_int == 0)
		translate_parallel_y_pos(data, MOV_STEP);
	else if (data->player->dir_int == 90)
		translate_parallel_x_pos(data, MOV_STEP);
	else if (data->player->dir_int == 180)
		translate_parallel_y_neg(data, MOV_STEP);
	else if (data->player->dir_int == 270)
		translate_parallel_x_neg(data, MOV_STEP);
}

static void	translate_left(t_data *data)
{
	if (data->player->dir_int > 0 && data->player->dir_int < 90)
		translate_diagonal_q2(data);
	else if (data->player->dir_int > 90 && data->player->dir_int < 180)
		translate_diagonal_q3(data);
	else if (data->player->dir_int > 180 && data->player->dir_int < 270)
		translate_diagonal_q4(data);
	else if (data->player->dir_int > 270)
		translate_diagonal_q1(data);
	else if (data->player->dir_int == 0)
		translate_parallel_y_neg(data, MOV_STEP);
	else if (data->player->dir_int == 90)
		translate_parallel_x_neg(data, MOV_STEP);
	else if (data->player->dir_int == 180)
		translate_parallel_y_pos(data, MOV_STEP);
	else if (data->player->dir_int == 270)
		translate_parallel_x_pos(data, MOV_STEP);
}

void	translate(t_data *data)
{
	if (data->player->mov_forward && !(data->player->mov_backward))
		translate_forward(data);
	if (data->player->mov_backward && !(data->player->mov_forward))
		translate_backward(data);
	if (data->player->strafe_left && !(data->player->strafe_right))
		translate_left(data);
	if (data->player->strafe_right && !(data->player->strafe_left))
		translate_right(data);
}
