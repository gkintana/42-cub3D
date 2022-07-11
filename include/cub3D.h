/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:49:59 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/11 22:50:18 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*--------------------------------- LIBRARIES --------------------------------*/
# include <libft.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

/*--------------------------------- KEY CODES --------------------------------*/
# if __linux__
#  define KEYCODE_W		119
#  define KEYCODE_A		97
#  define KEYCODE_S		115
#  define KEYCODE_D		100
#  define KEYCODE_ESC	65307
#  define KEYCODE_UP	65362
#  define KEYCODE_DOWN	65364
#  define KEYCODE_LEFT	65361
#  define KEYCODE_RIGHT	65363
# endif

# if __APPLE__
#  define KEYCODE_W		13
#  define KEYCODE_A		0
#  define KEYCODE_S		1
#  define KEYCODE_D		2
#  define KEYCODE_ESC	53
#  define KEYCODE_UP	126
#  define KEYCODE_DOWN	125
#  define KEYCODE_LEFT	123
#  define KEYCODE_RIGHT	124
# endif

/*------------------------------ CONSTANT VALUES -----------------------------*/
# define PI 			3.1415926535897932384626434
# define WIN_WIDTH		1600
# define WIN_HEIGHT		900

/*-------------------------------- STRUCTURES --------------------------------*/
typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		*pixel;
	int		bpp;
	int		len;
	int		endian;
}				t_image;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		width;
	int		height;
}				t_texture;

typedef struct s_minilibx
{
	void	*ptr;
	void	*window;
	int		win_width;
	int		win_height;

	char	**map;
	t_image	img[5];
}				t_minilibx;

typedef struct s_player_info
{
	double	pos_x;
	double	pos_y;
	double	vec_x;
	double	vec_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rotate_speed;
}				t_player_info;

typedef struct s_minimap
{
	int	scale;
	int	offset_x;
	int	offset_y;
}				t_minimap;

typedef struct s_program
{
	t_texture		tex;
	t_minilibx		mlx;
	t_player_info	info;
	t_minimap		map;
}				t_program;

typedef struct s_calculations
{
	double	camera;
	double	ray_vec_x;
	double	ray_vec_y;
	double	delta_x;
	double	delta_y;
	int		map_x;
	int		map_y;
	
	double	side_dist_x;
	double	side_dist_y;
	double	perp_dist;

	int		offset_x;
	int		offset_y;
	int		side;
}			t_calculations;

typedef struct s_raycast
{
	int		line_height;
	int		start;
	int		end;

	double	wall;
	double	step;
	double	texture_pos;
	int		texture_x;
	int		texture_y;
	int		buffer[WIN_HEIGHT][WIN_WIDTH];
	int		color;
}				t_raycast;

/*---------------------------- FUNCTION PROTOTYPES ---------------------------*/
void	check_map_extension(char *file);
int		check_map_validity(char *file);
char	**save_map(char *file, int lines);

void	draw_line(t_image *img, int x, int start, int end, int color);
void	draw_walls(t_program *prog, int (*buffer)[prog->mlx.win_width]);
void	draw_map(t_program *prog);
void	draw_player(t_program *prog);

int		raycast_loop(t_program *prog);

double	calculate_position_and_vector(t_program *prog, int formula);
double	calculate_position_and_plane(t_program *prog, int formula);
double	calculate_rotation(t_program *prog, int formula, double i[]);
int		key_events(int input, t_program *prog);
int		close_window(t_program *prog);

void	put_pixel_at_addr(t_image *img, int x, int y, int color);
void	free_2d_array(char **array);

#endif
