/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/18 20:53:56 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
** checks if the current index being accessed in the map is one of the following
** characters "N or S or E or W"
*/
bool	is_valid_start_position(t_program *prog, int i[])
{
	if (prog->mlx.map[i[0]][i[1]] == 'N'
		|| prog->mlx.map[i[0]][i[1]] == 'S'
		|| prog->mlx.map[i[0]][i[1]] == 'E'
		|| prog->mlx.map[i[0]][i[1]] == 'W')
		return (true);
	return (false);
}

/*
** parses the map and sets the player's starting location at the first
** occurrence of the following characters "N or S or E or W".
** furthermore, it also saves the starting orientation to the structure
** which will be used in the set_player_orientation function
**
** i[0] = index for y-axis of map
** i[1] = index for x-axis of map
** i[2] = acts like a boolean to indicate if the player's starting
**        location has been set
*/
void	set_player_position(t_program *prog)
{
	int	i[3];

	ft_bzero(&i, 3 * sizeof(int));
	i[0] = -1;
	while (prog->mlx.map[++i[0]] && !i[2])
	{
		i[1] = -1;
		while (prog->mlx.map[i[0]][++i[1]] && !i[2])
		{
			if (is_valid_start_position(prog, i))
			{
				prog->info.pos_x = i[1] + 0.50;
				prog->info.pos_y = i[0] + 0.50;
				i[2] = 1;
			}
		}
	}
	if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'N')
		prog->info.orientation = 1;
	else if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'S')
		prog->info.orientation = 2;
	else if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'E')
		prog->info.orientation = 3;
	else if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'W')
		prog->info.orientation = 4;
}

/*
** sets the player's initial facing direction according to the direction
** specified in the map file
*/
void	set_player_orientation(t_program *prog)
{
	if (prog->info.orientation == 1)
	{
		prog->info.vec_y = -1;
		prog->info.plane_x = 0.66;
	}
	else if (prog->info.orientation == 2)
	{
		prog->info.vec_y = 1;
		prog->info.plane_x = -0.66;
	}
	else if (prog->info.orientation == 3)
	{
		prog->info.vec_x = 1;
		prog->info.plane_y = 0.66;
	}
	else if (prog->info.orientation == 4)
	{
		prog->info.vec_x = -1;
		prog->info.plane_y = -0.66;
	}
}

/*
** event handler for mouse inputs, kind of works but we have to click the window
** in order for the changes to be seen
*/
int	mouse_events(int input, int x, int y, t_program *prog)
{
	(void)input, (void)x, (void)y, (void)prog;
	// printf("x=%d\ny=%d\n", x, y);
	// int i, j;
	// mlx_mouse_get_pos(prog->mlx.ptr, prog->mlx.window, &i, &j);
	// printf("x=%d\ny=%d\n", i, j);
	// int a = mlx_mouse_move(0,0,0,0);
	// (void)a;
	printf("x=%d\ny=%d\n", x, y);
	if (y < prog->mlx.win_height / 2)
	{
		prog->info.pitch += 400 * prog->info.move_speed;
		if (prog->info.pitch > 200)
			prog->info.pitch = 200;
	}
	else
	{
		prog->info.pitch -= 400 * prog->info.move_speed;
		if (prog->info.pitch < -200)
			prog->info.pitch = -200;
	}
	if (x < prog->mlx.win_width / 2)
		left_and_right_keys(prog, true);
	else
		left_and_right_keys(prog, false);
	update_frame(prog);
	return (0);
}

int main(int argc, char **argv)
{
	t_program	prog;

	if (argc == 2) {
		ft_bzero(&prog, sizeof(t_program));

		prog.tex.north = "assets/xpm/wall_1.xpm";
		prog.tex.south = "assets/xpm/wall_2.xpm";
		prog.tex.east = "assets/xpm/wall_5.xpm";
		prog.tex.west = "assets/xpm/wall_4.xpm";

		check_map_extension(argv[1]);
		prog.mlx.map = save_map(argv[1], check_map_validity(argv[1]));

		prog.mlx.ptr = mlx_init();
		prog.mlx.win_width = WIN_WIDTH;
		prog.mlx.win_height = WIN_HEIGHT;
		prog.mlx.window = mlx_new_window(prog.mlx.ptr, prog.mlx.win_width, prog.mlx.win_height, "cub3D");

		prog.mlx.img[0].ptr = mlx_new_image(prog.mlx.ptr, prog.mlx.win_width, prog.mlx.win_height);
		prog.mlx.img[0].addr = mlx_get_data_addr(prog.mlx.img[0].ptr, &prog.mlx.img[0].bpp, &prog.mlx.img[0].len, &prog.mlx.img[0].endian);
		prog.mlx.img[1].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.north, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[1].pixel = (int *)mlx_get_data_addr(prog.mlx.img[1].ptr, &prog.mlx.img[1].bpp, &prog.mlx.img[1].len, &prog.mlx.img[1].endian);
		prog.mlx.img[2].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.south, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[2].pixel = (int *)mlx_get_data_addr(prog.mlx.img[2].ptr, &prog.mlx.img[2].bpp, &prog.mlx.img[2].len, &prog.mlx.img[2].endian);
		prog.mlx.img[3].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.east, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[3].pixel = (int *)mlx_get_data_addr(prog.mlx.img[3].ptr, &prog.mlx.img[3].bpp, &prog.mlx.img[3].len, &prog.mlx.img[2].endian);
		prog.mlx.img[4].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.west, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[4].pixel = (int *)mlx_get_data_addr(prog.mlx.img[4].ptr, &prog.mlx.img[4].bpp, &prog.mlx.img[4].len, &prog.mlx.img[4].endian);

		set_player_position(&prog);
		set_player_orientation(&prog);

		prog.info.pitch = 0;
		prog.info.move_speed = 0.065;
		prog.info.rotate_speed = 0.035;

		prog.map.scale = 100;
		prog.map.offset_x = 15;
		prog.map.offset_y = 15;

		raycast_loop(&prog);
		// mlx_mouse_hide(prog.mlx.ptr, prog.mlx.window);
		mlx_mouse_hook(prog.mlx.window, mouse_events, &prog);
		// mlx_loop_hook(prog.mlx.ptr, mouse_events, &prog);
		// mlx_hook(prog.mlx.window, 6, 0L, mouse_events, &prog);
		mlx_hook(prog.mlx.window, 2, 1L<<0, key_events, &prog);
		mlx_hook(prog.mlx.window, 17, 1L<<17, close_window, &prog);
		mlx_loop(prog.mlx.ptr);
		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}