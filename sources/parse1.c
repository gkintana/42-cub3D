/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:45 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_elems1(char *str, int *i, int *elem, int *ctn)
{
	if (check_elems0(str, i))
	{
		if (str[*i] == 'N')
			elem[0]++;
		else if (str[*i] == 'S')
			elem[1]++;
		else if (str[*i] == 'W')
			elem[2]++;
		else if (str[*i] == 'E')
			elem[3]++;
		*i += 2;
		while (str[*i + 1] && ft_isspace(str[*i]) && str[*i] != '\n')
			*i += 1;
		if (str[*i])
			elem[7] += ft_path(str, *i);
		else
			elem[7]++;
		*ctn += 2;
	}
	if (elem[7] > 0)
	{
		printf("Error: Texture path failure\n");
		return (1);
	}
	return (0);
}

int	check_elems0(char *str, int *i)
{
	if ((str[*i] == 'N' && str[*i + 1] && str[*i + 1] == 'O' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])) \
				|| (str[*i] == 'S' && str[*i + 1] && str[*i + 1] == 'O' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])) \
				|| (str[*i] == 'W' && str[*i + 1] && str[*i + 1] == 'E' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])) \
				|| (str[*i] == 'E' && str[*i + 1] && str[*i + 1] == 'A' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])))
		return (1);
	return (0);
}

int	check_elems2(char *str, int *i, int *elem, int *ctn)
{
	if ((str[*i] == 'F' && str[*i + 1] && ft_isspace(str[*i + 1])) \
			|| (str[*i] == 'C' && str[*i + 1] && ft_isspace(str[*i + 1])))
	{
		if (str[*i] == 'F')
			elem[4]++;
		else if (str[*i] == 'C')
			elem[5]++;
		*i += 1;
		while (str[*i + 1] && ft_isspace(str[*i]) && str[*i] != '\n')
			*i += 1;
		if (str[*i])
			elem[7] += ft_rgb(str, *i);
		else
			elem[7]++;
		*ctn += 2;
		if (elem[7] > 0)
		{
			free (str);
			printf("Error: RGB color failure\n");
			free (elem);
			return (1);
		}
	}
	return (0);
}

int	ft_map_row1(char *str, int *elem, char **map_temp)
{
	(void)str;
	(void)elem;
	if (map_temp[ft_array_len(map_temp) - 1][0] != '\n')
		map_temp = ft_temp_map(map_temp, "\n");
	if (check_map(map_temp))
	{
		free_2d_array(map_temp);
		return (1);
	}
	free_2d_array(map_temp);
	return (0);
}
