/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/08/01 19:24:04 by gkintana         ###   ########.fr       */
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

#if __linux__

void	check_map_validity(char *file)
{
	int		fd;

	fd = open(file, __O_DIRECTORY | __O_PATH);
	if (fd != -1)
	{
		ft_putstr_fd("Error: Argument Not a file\n", 2);
		close(fd);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Map file does not exist\n", 2);
		close(fd);
		exit (1);
	}
	close(fd);
}
#endif

#if __APPLE__

void	check_map_validity(char *file)
{
	int		fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd("Error: Argument Not a file\n", 2);
		close(fd);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Map file does not exist\n", 2);
		close(fd);
		exit (1);
	}
	close(fd);
}
#endif

void	check_elements0(char **data, int *elem, char **map_temp)
{
	if (data)
	{
		free_2d_array(data);
		data = NULL;
	}
	close(elem[6]);
	free (elem);
	elem = NULL;
	if (map_temp)
	{
		free_2d_array(map_temp);
		map_temp = NULL;
	}
}

int	check_last2(int *j, char **map)
{
	int	len;
	int	i;
	int	k;

	k = *j;
	len = 0;
	while (k > 0)
	{
		i = 0;
		if (map[k][i] && ft_isspace(map[k][i]) && map[k][i] != '\n')
			i++;
		if (!map[k][i + 1] || map[k][i + 1] == '\n')
			break ;
		else
		{
			k--;
			len++;
		}
	}
	if (k <= 0)
		return (0);
	if (!ft_map_row(map[k + 1]))
		return (0);
	*j = k;
	return (len);
}

/*old
int	check_last2(int *j, char **map)
{
	int	len;
	int	i;
	int	k;

	k = *j;
	len = 0;
	while (1)
	{
		i = 0;
		if (map[k][i] && ft_isspace(map[k][i]) && map[k][i] != '\n')
			i++;
		if (map[k][i] && map[k][i] != '\n' && k > 0)
		{
			printf("test3 %d: %s\n i is %d and char %c", k, map[k], i, map[k][i]);
			k--;
			len++;
		}
		else
			break ;
	}
	*j = k;
	return (len);
}
*/
int	check_last(char **map)
{
	int	j;
	int	i;

	i = 0;
	j = ft_array_len(map) - 1;
	while (j > 0)
	{
		while (ft_isspace(map[j][i]) && map[j][i] != '\n')
			i++;
		if (map[j][i] == '\n')
			j--;
		else
			break ;
	}
	return (j);
}
