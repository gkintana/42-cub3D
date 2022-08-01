/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/08/01 19:24:51 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ft_path1(char *ret, int fd)
{
	if (fd != -1)
	{
		printf("Error: texture path %s not a file\n", ret);
		close (fd);
		free (ret);
		ret = NULL;
		return (1);
	}
	fd = open(ret, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: texture path %s not accessible\n", ret);
		free (ret);
		ret = NULL;
		return (1);
	}
	close(fd);
	return (0);
}

void	ft_path2(char *ret, int fd)
{
	close (fd);
	free (ret);
	ret = NULL;
}

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
	ft_path2(ret, fd);
	return (0);
}
#endif

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
	ft_path2(ret, fd);
	return (0);
}
#endif
