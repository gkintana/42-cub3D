/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:49:59 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/09 01:06:40 by gkintana         ###   ########.fr       */
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
#  define KEYCODE_UP	
#  define KEYCODE_DOWN	
#  define KEYCODE_LEFT	
#  define KEYCODE_RIGHT	
# endif

/*------------------------------ CONSTANT VALUES -----------------------------*/
# define PI 			3.1415926535897932384626434
# define WALL_WIDTH		50
# define WALL_HEIGHT	50

/*-------------------------------- STRUCTURES --------------------------------*/
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		*pixel;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

// Approach done based on this series
// https://www.youtube.com/watch?v=gYRrGTC7GtA
// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*window;
// 	int		width;
// 	int		height;
// 	char	**map;

// 	// char	*white;
// 	// char	*yellow;
// 	t_img	img[2];

// 	void	*wall;
// 	int		wall_width;
// 	int		wall_height;

// 	void	*player;
// 	double	player_speed;
// 	int		player_width;
// 	int		player_height;
// 	// int		x;
// 	// int		y;

// 	double	px;		// player x-coordinate
// 	double	py;		// player y-coordinate
// 	double	pdx;	// distance x
// 	double	pdy;	// distance y
// 	double	pa;		// player angle
// }				t_data;


// Lode's Raycasting Tutorial
typedef struct s_data
{
	void	*mlx;
	void	*mlx_window;
	int		win_width;
	int		win_height;
	char	**map;

	t_img	img[2];
	double	pos_x;
	double	pos_y;
	double	vec_x;
	double	vec_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rotate_speed;

	int		texture_width;
	int		texture_height;
}		t_data;

typedef struct s_calculations
{
	double	camera;
	double	ray_vec_x;
	double	ray_vec_y;

	int		map_x;
	int		map_y;
	
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_dist;

	int		offset_x;
	int		offset_y;
	int		side;
}			t_calculations

typedef struct s_raycast
{
	// double	camera;
	// double	ray_vec_x;
	// double	ray_vec_y;

	// int		map_x;
	// int		map_y;
	
	// double	side_dist_x;
	// double	side_dist_y;
	// double	delta_dist_x;
	// double	delta_dist_y;
	// double	perp_dist;

	// int		offset_x;
	// int		offset_y;
	// int		side;

	int		line_height;
	int		line_start;
	int		line_end;

	int		color;
}				t_raycast;

#endif
