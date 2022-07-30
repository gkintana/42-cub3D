/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:49:59 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/30 13:06:04 by gkintana         ###   ########.fr       */
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

/*--------------------------------- CONSTANTS --------------------------------*/
# define HEX_SYSTEM		"0123456789ABCDEF"
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
	char	*floor;
	char	*ceiling;

	int		width;
	int		height;
	int		floor_rgb;
	int		ceiling_rgb;
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
	int		orientation;
	double	pos_x;
	double	pos_y;
	double	vec_x;
	double	vec_y;
	double	plane_x;
	double	plane_y;
	double	pitch;
	double	move_speed;
	double	rotate_speed;
}				t_player_info;

typedef struct s_minimap
{
	int	scale;
	int	offset_x;
	int	offset_y;
}				t_minimap;

typedef struct s_mouse
{
	int	new_x;
	int	new_y;
}				t_mouse;

typedef struct s_program
{
	t_texture		tex;
	t_minilibx		mlx;
	t_player_info	info;
	t_mouse			mouse;
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
// Parse Utils
char	*ft_strchr(const char *s, int c);
void	ft_bzero2(int *array, int len);
int		ft_array_len(char **array);
int		ft_atoi2(const char *str);

// Parse Functions
void	check_map_extension(char *file);
void	check_map_validity(char *file);
int		check_elements(char *file);
int		check_elements1(char *str, int *elem, char **map_temp);
int		check_elements2(char *str, int *elem, char **map_temp);
int		ft_elem(int *array, int len, char **map_temp);
int		check_elems1(char *str, int *i, int *elem, int *ctn);
int		check_elems0(char *str, int *i);
int		check_elems2(char *str, int *i, int *elem, int *ctn);
int		ft_map_row1(char *str, int *elem, char **map_temp);
int		check_elems6(char *str, int *elem, char **map_temp);
int		check_elems3(char *str, int *i, int *elem, char **map_temp);
int		check_elems4(char *str, int *elem, char **map_temp);
int		check_elems5(char *str, int *elem, char **map_temp);
int		t_path1(char *ret, int fd);
void	ft_path2(char *ret, int fd);
int		ft_path(char *str, int i);
int		ft_rgb(char *str, int i);
char	*ft_rgb1(char *str, int i);
char	*ft_rgb2(char *temp);
int		ft_map_row(char *str);
char	**ft_temp_map(char **map_temp, char *str);
int		check_map(char **map);
int		check_top(char **map);
int		check_top1(char **map, int *i, int *j, int *flag);
int		check_bottom(char **map);
int		check_bottom1(char **map, int *i, int *j, int *flag);
int		check_left(char **map);
int		check_left1(char **map, int *j);
int		check_chars(char **map);
int		check_right(char **map);

// Initialization Functions
void	init(t_program *prog, char *file);
void	init0(int *i, char *str, t_program *prog);
void	init_n(int *i, char *str, t_program *prog);
void	init_s(int *i, char *str, t_program *prog);
void	init_e(int *i, char *str, t_program *prog);
void	init_w(int *i, char *str, t_program *prog);
void	init_f(int *i, char *str, t_program *prog);
void	init_c(int *i, char *str, t_program *prog);
void	init_map(char *str, char **map_temp, int fd, t_program *prog);
void	init_mlx(t_program *prog);
void	init_images(t_program *prog);
void	init_player(t_program *prog);
char	*init_rgb(char *str, int *i);
char	*init_path(char *str, int *i);

// Player Position
void	set_player_position(t_program *prog);
void	set_player_orientation(t_program *prog);

// Drawing Functions
void	get_floor_rgb(t_program *prog);
void	get_ceiling_rgb(t_program *prog);
void	draw_line(t_image *img, int x, int start, int end, int color);
void	draw_walls(t_program *prog, int (*buffer)[prog->mlx.win_width]);
void	draw_map(t_program *prog);
void	draw_player(t_program *prog);

// Raycasting
void	calculate_texture(t_program *prog, t_calculations *calc,
		t_raycast *ray);
void	save_texture(t_program *prog, t_calculations *calc,
		t_raycast *ray, int i[]);
int		raycast_loop(t_program *prog);

// Player Movement & Perspective
double	calculate_position_and_vector(t_program *prog, int formula);
double	calculate_position_and_plane(t_program *prog, int formula);
double	calculate_rotation(t_program *prog, int formula, double i[]);
void	horizontal_perspective(t_program *prog, bool rotate_left);
void	vertical_perspective(t_program *prog, bool look_up);

// Events
int		mouse_events(int x, int y, t_program *prog);
int		key_events(int input, t_program *prog);
void	update_frame(t_program *prog);
int		close_window(t_program *prog);

// Utilities
void	put_pixel_at_addr(t_image *img, int x, int y, int color);
void	free_2d_array(char **array);

#endif
