/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:13:39 by myael             #+#    #+#             */
/*   Updated: 2022/06/14 15:05:21 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	error_exit(char *str, int num)
{
	printf("Error:\n     %s", str);
	exit(num);
}

void	print_double_array(t_map *m)
{
	char	**map;

	map = m->map;
	while (*map)
	{
		printf("%s\n", *map);
		map++;
	}
}

char	*ft_spaces_str(int width, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (width - len + 1));
	while (i < width - len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	skip_empty_lines(t_check *ch)
{
	ch->trimmed = ft_strtrim(ch->line, " \t\v\f\r");
	if (ch->trimmed && *(ch->trimmed))
	{
		free(ch->trimmed);
		return ;
	}
	if (ch->line)
		free(ch->line);
	if (ch->trimmed)
		free(ch->trimmed);
	while (get_next_line(ch->fd, &ch->line))
	{
		ch->trimmed = ft_strtrim(ch->line, " \t\v\f\r");
		if (ch->trimmed && *(ch->trimmed))
		{
			free(ch->trimmed);
			break ;
		}
		free(ch->line);
		ch->line = NULL;
		free(ch->trimmed);
		ch->trimmed = NULL;
	}
	if (!ch->line || !*(ch->line))
		error_exit("Error with map data!", 6);
}
