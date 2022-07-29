/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:02:05 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

//should return 0 if not map first row
int	ft_map_row(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i] && str[i] != '\n')
	{
		if ((str[i] != ' ' && str[i] != '1'))
			return (0);
		if (str[i] == '1')
			flag++;
		i++;
	}
	if (flag == 0)
		return (0);
	return (1);
}

char	**ft_temp_map(char **map_temp, char *str)
{
	char	**new_temp;
	int		rows;
	int		i;

	rows = ft_array_len(map_temp);
	new_temp = (char **)malloc(sizeof(char *) * (rows + 2));
	i = 0;
	while (map_temp[i])
	{
		new_temp[i] = ft_strdup(map_temp[i]);
		i++;
	}
	new_temp[i] = ft_strdup(str);
	new_temp[i + 1] = NULL;
	free_2d_array(map_temp);
	return (new_temp);
}

int	check_map(char **map)
{
	if (check_chars(map) || check_top(map) || check_bottom(map) \
	|| check_left(map) || check_right(map))
	{
		printf("Error: invalid map\n");
		// free_2d_array(map);
		return (1);
	}		
	return (0);
}
