/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:41 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	check_map_extension(char *file)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (!ext)
	{
		ft_putstr_fd("Error: Invalid Map, No Extension\n", 2);
		exit(1);
	}
	if (ft_strncmp(ext, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error: Invalid Map Extension\n", 2);
		exit(1);
	}
	ext = ft_strchr(file, '.');
	if (ft_strlen(ext) != 4)
	{
		ft_putstr_fd("Error: Invalid Map Extension\n", 2);
		exit(1);
	}
}

void	check_map_validity(char *file)
{
	int		fd;

	fd = open(file, __O_DIRECTORY | __O_PATH);
	if (fd != -1)
	{
		ft_putstr_fd("Error: Argument Not a file\n", 2);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Map file does not exist\n", 2);
		exit (1);
	}
	close(fd);
}

int	check_elements(char *file)
{
	char	*str;
	int		*elem;
	char	**map_temp;

	elem = (int *)malloc(sizeof(int) * 8);
	map_temp = (char **)malloc(sizeof(char *) * 1);
	ft_bzero2(elem, 8);
	map_temp[0] = NULL;
	elem[6] = open(file, O_RDONLY);
	str = get_next_line(elem[6]);
	if (check_elements1(str, elem, map_temp))
	{
		// free_2d_array(map_temp);
		return (1);
	}
	if (ft_elem(elem, 6, map_temp))
		return (1);
	//free_2d_array(map_temp); gets segfault..s
	return (0);
}

int	check_elements2(char *str, int *elem, char **map_temp)
{
	if (!ft_map_row(str))
		return (check_elems5(str, elem, map_temp));
	else
	{
		if (check_elems4(str, elem, map_temp))
			return (1);
		else
			return (0);
	}
}

int	check_elements1(char *str, int *elem, char **map_temp)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((str != NULL))
	{
		i = 0;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			flag = check_elems3(str, &i, elem, map_temp);
			if (flag == 1)
				return (1);
			if (flag == 0)
				return (check_elements2(str, elem, map_temp));
		}
		free (str);
		str = get_next_line(elem[6]);
	}
	return (0);
}
