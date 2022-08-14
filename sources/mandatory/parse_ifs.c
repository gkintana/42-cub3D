/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:26 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#if __linux__
//should return 0 if all good
int	ft_path(char *str, int i)
{
	char	*ret;
	int		j;
	int		len;
	int		fd;

	j = i;
	while (!ft_isspace(str[j]))
		j++;
	len = j - i;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (1);
	while (!ft_isspace(str[i]))
	{
		ret[j] = str[i];
		j++;
		i += 1;
	}
	ret[j] = '\0';
	fd = open(ret, __O_DIRECTORY | __O_PATH);
	if (ft_path1(ret, fd))
		return (1);
	return (0);
}
#endif

#if __APPLE__
//should return 0 if all good
int	ft_path(char *str, int i)
{
	char	*ret;
	int		j;
	int		len;
	int		fd;

	j = i;
	while (!ft_isspace(str[j]))
		j++;
	len = j - i;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (1);
	while (!ft_isspace(str[i]))
	{
		ret[j] = str[i];
		j++;
		i += 1;
	}
	ret[j] = '\0';
	fd = open(ret, O_DIRECTORY);
	if (ft_path1(ret, fd))
		return (1);
	return (0);
}
#endif

#if __linux__

void	check_map_validity(char *file)
{
	int		fd;

	fd = open(file, __O_DIRECTORY | __O_PATH);
	if (fd != -1)
	{
		ft_putstr_fd("Error\nArgument Not a file\n", 2);
		close(fd);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file does not exist\n", 2);
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
		ft_putstr_fd("Error\nArgument Not a file\n", 2);
		close(fd);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file does not exist\n", 2);
		close(fd);
		exit (1);
	}
	close(fd);
}
#endif
