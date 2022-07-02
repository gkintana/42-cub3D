/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:49:59 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/03 00:09:09 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <libft.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

typedef struct s_pixel
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_pixel;

#endif
