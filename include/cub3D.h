/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:49:59 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/08 01:52:38 by gkintana         ###   ########.fr       */
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

	t_img	img;
	double	position_x;
	double	position_y;
	double	vector_x;
	double	vector_y;
	double	plane_x;
	double	plane_y;

	// double	time_new;
	// double	time_old;

}		t_data;

typedef struct s_raycast
{
	
}				t_raycast;

#define MOVE	0.042
#define ROT		0.030

#endif
