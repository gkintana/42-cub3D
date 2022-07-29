/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:00:54 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_w(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.west = init_path(str, i);
}

void	init_f(int *i, char *str, t_program *prog)
{
	*i += 1;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.floor = init_rgb(str, i);
}

void	init_c(int *i, char *str, t_program *prog)
{
	*i += 1;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.ceiling = init_rgb(str, i);
}

void	init_map(char *str, char **map_temp, int fd, t_program *prog)
{
	while (str)
	{
		map_temp = ft_temp_map(map_temp, str);
		free (str);
		str = get_next_line(fd);
	}
	free (str);
	if (map_temp[ft_array_len(map_temp) - 1][0] != '\n')
		map_temp = ft_temp_map(map_temp, "\n");
	prog->mlx.map = map_temp;
}

char	*init_rgb(char *str, int *i)
{
	char	*ret;
	int		j;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * 4097);
	if (!temp)
		return (NULL);
	ft_memset(temp, '\0', 4097);
	j = 0;
	while (str[*i])
	{
		if (!ft_isspace(str[*i]))
		{
			temp[j] = str[*i];
			j++;
		}
		*i += 1;
	}
	ret = (char *)malloc(sizeof(char) * (ft_strlen(temp) + 1));
	ret = ft_strdup(temp);
	free(temp);
	printf("test init1 %sret\n", ret);
	return (ret);
}
