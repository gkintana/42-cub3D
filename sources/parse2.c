/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:51 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_elems6(char *str, int *elem, char **map_temp)
{
	free (str);
	close (elem[6]);
	free (elem);
	free_2d_array (map_temp);
	return (1);
}

int	check_elems3(char *str, int *i, int *elem, char **map_temp)
{
	int	ctn;

	ctn = 0;
	if (check_elems1(str, i, elem, &ctn))
		return (check_elems6(str, elem, map_temp));
	else if (check_elems2(str, i, elem, &ctn))
		return (check_elems6(str, elem, map_temp));
	return (ctn);
}

int	check_elems4(char *str, int *elem, char **map_temp)
{
	elem[7] = 0;
	while (str)
	{
		map_temp = ft_temp_map(map_temp, str);
		free (str);
		str = get_next_line(elem[6]);
	}
	if (ft_map_row1(str, elem, map_temp))
	{
		free (str);
		close (elem[6]);
		free (elem);
		return (1);
	}
	free (str);
	close (elem[6]);
	return (0);
}

int	check_elems5(char *str, int *elem, char **map_temp)
{
	free (str);
	close (elem[6]);
	free (elem);
	free_2d_array (map_temp);
	printf("Error: Invalid inputs in file\n");
	return (1);
}
