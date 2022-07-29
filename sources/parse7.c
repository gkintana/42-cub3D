/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:02:17 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_left(char **map)
{
	int	j;
	int	i;

	i = 0;
	j = ft_array_len(map) - 1;
	while (1)
	{
		while (ft_isspace(map[j][i]) && map[j][i] != '\n')
			i++;
		if (!map[j][i])
			return (1);
		if (map[j][i] == '\n')
			j--;
		else
			break ;
	}
	j--;
	while (j > 0)
	{
		if (check_left1(map, &j))
			return (1);
		j -= 1;
	}
	return (0);
}

int	check_left1(char **map, int *j)
{
	int	flag[2];
	int	i;

	ft_bzero2(flag, 2);
	i = 0;
	while (map[*j][i] == ' ')
	{
		i++;
		if (map[*j][i] == '0')
			return (1);
	}
	if (map[*j][i] != '1')
		return (1);
	while (map[*j][i] == '1')
	{
		if (map[*j + 1][i] == '1')
			flag[0] = 1;
		if (map[*j - 1][i] == '1')
			flag[1] = 1;
		i++;
	}
	if (flag[0] == 0 || flag[1] == 0)
		return (1);
	return (0);
}

int	check_chars(char **map)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	j = 0;
	while (j < ft_array_len(map))
	{
		i = 0;
		while (i < (int)ft_strlen(map[j]))
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' \
			|| map[j][i] == 'E')
				flag++;
			else if (map[j][i] != ' ' && map[j][i] != '1' && map[j][i] != '0' \
			&& map[j][i] != '\n')
				return (1);
			i++;
		}
		j++;
	}
	if (flag != 1)
		return (1);
	return (0);
}

int	check_right(char **map)
{
	int	j;
	int	i;
	int	flag;

	i = 0;
	j = ft_array_len(map) - 2;
	while (j > 0)
	{
		flag = 0;
		i = ft_strlen(map[j]) - 2;
		if (map[j][i] != '1')
			return (1);
		while (i > 0 && map[j][i] == '1')
		{
			if (map[j - 1][i] == '1')
				flag = 1;
			i--;
		}
		if (flag == 0)
			return (1);
		j--;
	}
	return (0);
}

int	ft_elem(int *array, int len, char **map_temp)
{
	int	i;

	(void)map_temp;
	i = 0;
	while (i < len)
	{
		if (array[i] != 1)
		{
			ft_putstr_fd("Error: Invalid Map Elements\n", 2);
			free (array);
			// free_2d_array(map_temp);
			return (1);
		}
		i++;
	}
	free (array);
	return (0);
}
