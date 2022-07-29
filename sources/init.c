/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:00:39 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

//added F and C color
void	init(t_program *prog, char *file)
{
	int		fd;
	int		i;
	char	*str;
	char	**map_temp;

	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	map_temp = (char **)malloc(sizeof(char *) * 1);
	map_temp[0] = NULL;
	while ((str != NULL))
	{
		i = 0;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' \
		|| str[i] == 'W' || str[i] == 'F' || str[i] == 'C')
			init0(&i, str, prog);
		else if (ft_map_row(str))
		{
			init_map(str, map_temp, fd, prog);
			break ;
		}
		free(str);
		str = get_next_line(fd);
	}
	close (fd);
	init_mlx(prog);
}

void	init0(int *i, char *str, t_program *prog)
{
	if (str[*i] == 'N')
		init_n(i, str, prog);
	else if (str[*i] == 'S')
		init_s(i, str, prog);
	else if (str[*i] == 'E')
		init_e(i, str, prog);
	else if (str[*i] == 'W')
		init_w(i, str, prog);
	else if (str[*i] == 'F')
		init_f(i, str, prog);
	else if (str[*i] == 'C')
		init_c(i, str, prog);
}

void	init_n(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.north = init_path(str, i);
}

void	init_s(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.south = init_path(str, i);
}

void	init_e(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.east = init_path(str, i);
}
