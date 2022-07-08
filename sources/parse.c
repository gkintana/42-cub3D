/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/09 02:01:03 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
 * this function simply checks if the argument being passed is a file with a
 * .cub extension.
 * 
 * Note: will still work or sometimes even segfault when given invalid
 * 		 arguments
 */
void	check_map_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file) - 1;
	if (i >= 4 && file[i] == 'b' && file[i - 1] == 'u' && file[i - 2] == 'c' 
		&& file[i - 3] == '.')
		return ;
	ft_putstr_fd("Invalid Map Extension\n", 2);
	exit(1);
}

// int find_errors(char *line)
// {
	
// }

/*
 * function intended to parse map before proceding with the initializations,
 * calculations, raycasting, etc.
 */
int	check_map_validity(char *file)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error! Map file does not exist\n", 2);
		exit(1);
	}
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		// if (find_errors(str))
		// {
		// 	ft_putstr_fd("Invalid Map\n", 2);
		// 	exit(1);
		// }
		// printf("%s", str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	free(str);
	str = NULL;
	close(fd);
	return (i);
}

/*
 * saves the map in a 2d array if it passes the parser
 */
char	**save_map(char *file, int lines)
{
	char	**map;
	char	*temp;
	int		fd;
	int		i;

	map = (char **)ft_calloc(lines + 1, sizeof(char *));
	fd = open(file, O_RDONLY);
	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		map[i++] = ft_strdup(temp);
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	temp = NULL;
	close(fd);
	return (map);
}