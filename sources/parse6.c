/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:02:11 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_top(char **map)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	if (ft_map_row(map[0]) == 0)
		return (1);
	i = 0;
	j = 0;
	while (ft_isspace(map[j][i]) && map[j][i + 1] != '\n')
		i++;
	if (!map[j][i])
		return (1);
	if (check_top1(map, &i, &j, &flag))
		return (1);
	return (0);
}

int	check_top1(char **map, int *i, int *j, int *flag)
{
	int	max_check;

	max_check = ft_strlen(map[0]) * 5;
	while (map[*j][*i + 1] != '\n' && *flag < max_check)
	{
		while (map[*j][*i] == '1' && map[*j][*i + 1] == '1' && (*j == 0 \
		|| (*j > 0 && map[*j - 1][*i] != '1')))
			*i += 1;
		*flag += 1;
		while (map[*j][*i] == '1' && map[*j + 1][*i] && map[*j + 1][*i] == '1' \
		&& map[*j][*i + 1] == ' ')
			*j += 1;
		*flag += 1;
		while (map[*j][*i] == '1' && map[*j][*i + 1] == '1' && \
		(*j == 0 || (*j > 0 && map[*j - 1][*i + 1] != '0')))
			*i += 1;
		*flag += 1;
		while (map[*j][*i] == '1' && *j > 0 && *i > 0 && \
		map[*j - 1][*i - 1] == ' ' && map[*j - 1][*i] == '1')
			*j -= 1;
		*flag += 1;
	}
	if (map[*j][*i + 1] != '\n')
		return (1);
	return (0);
}

int	check_bottom(char **map)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	j = ft_array_len(map) - 1;
	i = 0;
	while (1)
	{
		while (ft_isspace(map[j][i]) && map[j][i] != '\n')
			i++;
		if (!map[j][i])
			return (1);
		if (map[j][i] == '\n')
			j -= 1;
		else
			break ;
	}
	while (map[j][i + 1] != '\n')
		if (check_bottom1(map, &i, &j, &flag))
			break ;
	if (map[j][i + 1] != '\n' && map[j][i + 1])
		return (1);
	return (0);
}

int	check_bottom1(char **map, int *i, int *j, int *flag)
{
	int	max_check;

	max_check = ft_strlen(map[*j]) * 3;
	while (map[*j][*i] == '1' && map[*j][*i + 1] == '1' \
	&& ((*j == ft_array_len(map) - 1) \
	|| ((*j < ft_array_len(map) - 1) && map[*j + 1][*i] != '1')))
		*i += 1;
	*flag += 1;
	while (map[*j][*i] == '1' && map[*j - 1][*i] && map[*j - 1][*i] == '1' \
	&& map[*j][*i + 1] == ' ')
		*j -= 1;
	*flag += 1;
	while (map[*j][*i] == '1' && map[*j][*i + 1] == '1' && \
	((*j == ft_array_len(map) - 1) \
	|| ((*j < ft_array_len(map) - 1) && map[*j + 1][*i + 1] != '0')))
		*i += 1;
	*flag += 1;
	while (map[*j][*i] == '1' && (*j < ft_array_len(map) - 1) && *i > 0 \
	&& map[*j + 1][*i] == '1' && map[*j + 1][*i - 1] == ' ')
		*j += 1;
	*flag += 1;
	if (*flag > max_check)
		return (1);
	return (0);
}
