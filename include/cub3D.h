/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:49:59 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/03 18:49:10 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <libft.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

typedef struct s_img
{
	void	*mlx;
	void	*window;
	// char	*map;

	void	*wall;
	void	*player;
	
	char	*white;
	char	*yellow;
	
	int		wall_width;
	int		wall_height;
	int		player_width;
	int		player_height;
	
	int		x;
	int		y;
}				t_img;

#endif
