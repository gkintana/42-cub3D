/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_floor_and_ceiling_checker.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:28:22 by myael             #+#    #+#             */
/*   Updated: 2022/06/14 15:03:58 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// if error - ft_atoi_color returns -1
// else it return num from 0 to 255

int	ft_atoi_color(const char *str)
{
	int	num;

	num = 0;
	if (!*str || (*str < '1' && *str > '9'))
		return (-1);
	if (*str == '0')
	{
		if (str[1] && str[1] >= '0' && str[1] <= '9')
			return (-1);
		return (0);
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		if (num > 255)
			return (-1);
	}
	return (num);
}

char	*add_color_to_struct(char *str, t_color *col, int index)
{
	int	num;

	if (!str)
		error_exit("Wrong color data", 17);
	num = ft_atoi_color(str);
	if (num == -1)
		error_exit("RGB data of color is wrong", 18);
	else
	{
		if (index == 0)
			col->r = num;
		else if (index == 1)
			col->g = num;
		else
			col->b = num;
		while (*str && *str >= '0' && *str <= '9')
			str++;
	}
	return (str);
}

void	check_correctness_of_color(char *str, t_color *col)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		str = add_color_to_struct(str, col, i);
		if (i < 2 && *str && *str == ',')
			str++;
		else if ((i < 2 && *str != ',') || (i == 2 && *str))
			error_exit("Wrong format of color data", 19);
		++i;
	}
}

void	add_color_of_floor_and_ceiling(char **args, t_check *ch, t_data *data)
{
	t_color	col;

	check_correctness_of_color(args[1], &col);
	if (!ft_strncmp("F", args[0], 2) && !ch->floor)
	{
		data->floor[0] = col.r;
		data->floor[1] = col.g;
		data->floor[2] = col.b;
		ch->floor++;
	}
	else if (!ft_strncmp("C", args[0], 2) && !ch->ceiling)
	{
		data->ceiling[0] = col.r;
		data->ceiling[1] = col.g;
		data->ceiling[2] = col.b;
		ch->ceiling++;
	}
	else
		error_exit("Identifiers repetitive", 20);
}
