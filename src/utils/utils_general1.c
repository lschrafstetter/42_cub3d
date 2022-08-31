/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:49:06 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/31 15:36:19 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	**array_init(int height, int width)
{
	int	**int_arr;
	int	i;

	int_arr = ft_calloc(height + 1, sizeof(int *));
	if (!int_arr)
		return (NULL);
	i = 0;
	while (i <= height)
	{
		int_arr[i] = ft_calloc(width + 1, sizeof(int));
		if (!int_arr[i])
		{
			free_intarray(int_arr);
			return (NULL);
		}
		i++;
	}
	return (int_arr);
}

void	free_intarray(int **int_arr)
{
	while (*int_arr)
	{
		free(*int_arr);
		int_arr++;
	}
	free(int_arr);
}

int	str_arr_len(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

void	free_strarray(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

char	*get_first_n_chars(char *str, int n_chars)
{
	char	*ret;

	ret = ft_calloc(n_chars + 1, 1);
	if (!ret)
		return (NULL);
	ft_strlcat(ret, str, n_chars + 1);
	return (ret);
}
