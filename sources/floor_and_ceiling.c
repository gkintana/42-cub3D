/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:50:21 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/05 20:37:04 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
** returns the decimal representation of the hexadecimal values provided
** in this function's parameters
**
** formula was based on the calculations provided at this website
** https://www.rapidtables.com/convert/number/hex-to-decimal.html
*/
// static int	convert_hex_to_int(int r, int g, int b)
static int	convert_hex_to_int(t_rgb *rgb, bool is_floor)
{
	if (is_floor)
		return ((int)(((rgb->floor_r / 16) * pow(16, 5))
			+ ((rgb->floor_r % 16) * pow(16, 4))
			+ ((rgb->floor_g / 16) * pow(16, 3))
			+ ((rgb->floor_g % 16) * pow(16, 2))
			+ ((rgb->floor_b / 16) * pow(16, 1))
			+ ((rgb->floor_b % 16) * pow(16, 0))));
	else
		return ((int)(((rgb->ceiling_r / 16) * pow(16, 5))
			+ ((rgb->ceiling_r % 16) * pow(16, 4))
			+ ((rgb->ceiling_g / 16) * pow(16, 3))
			+ ((rgb->ceiling_g % 16) * pow(16, 2))
			+ ((rgb->ceiling_b / 16) * pow(16, 1))
			+ ((rgb->ceiling_b % 16) * pow(16, 0))));
}

/*
** sets the respective rgb value to the rgb[6] array used in the
** get_floor_and_ceiling_rgb & print_rgb_info functions
**
** rgb[0] = Floor R
** rgb[1] = Floor G
** rgb[2] = Floor B
** rgb[3] = Ceiling R
** rgb[4] = Ceiling G
** rgb[5] = Ceiling B
*/
// static void	save_rgb_components(char **rgb_array[], int rgb[])
static void	save_rgb_components(t_rgb *rgb, char **rgb_array[])
{
	rgb->floor_r = ft_atoi(rgb_array[0][0]);
	rgb->floor_g = ft_atoi(rgb_array[0][1]);
	rgb->floor_b = ft_atoi(rgb_array[0][2]);
	rgb->ceiling_r = ft_atoi(rgb_array[1][0]);
	rgb->ceiling_g = ft_atoi(rgb_array[1][1]);
	rgb->ceiling_b = ft_atoi(rgb_array[1][2]);

	// rgb[0] = ft_atoi(rgb_array[0][0]);
	// rgb[1] = ft_atoi(rgb_array[0][1]);
	// rgb[2] = ft_atoi(rgb_array[0][2]);
	// rgb[3] = ft_atoi(rgb_array[1][0]);
	// rgb[4] = ft_atoi(rgb_array[1][1]);
	// rgb[5] = ft_atoi(rgb_array[1][2]);
}

/*
** prints the rgb hex and int values of the floor and ceiling colors.
** Will be mainly used for double checking & evaluations
**
** Should be inside the get_floor_and_ceiling_rgb function, right after
** setting prog->tex.ceiling_rgb and before freeing rgb_array[0]
*/
// void	print_rgb_info(t_program *prog, int rgb[])
void	print_rgb_info(t_rgb *rgb)
{
	printf("Floor RGB (Hex Value) = %c%c%c%c%c%c\n",
		HEX_SYSTEM[rgb->floor_r / 16], HEX_SYSTEM[rgb->floor_r % 16],
		HEX_SYSTEM[rgb->floor_g / 16], HEX_SYSTEM[rgb->floor_g % 16],
		HEX_SYSTEM[rgb->floor_b / 16], HEX_SYSTEM[rgb->floor_b % 16]);
	printf("Floor RGB (Int Value) = %d\n", rgb->floor);
	printf("Ceiling RGB (Hex Value) = %c%c%c%c%c%c\n",
		HEX_SYSTEM[rgb->ceiling_r / 16], HEX_SYSTEM[rgb->ceiling_r % 16],
		HEX_SYSTEM[rgb->ceiling_g / 16], HEX_SYSTEM[rgb->ceiling_g % 16],
		HEX_SYSTEM[rgb->ceiling_b / 16], HEX_SYSTEM[rgb->ceiling_b % 16]);
	printf("Ceiling RGB (Int Value) = %d\n", rgb->ceiling);


	// printf("Floor RGB (Hex Value) = %c%c%c%c%c%c\n",
	// 	HEX_SYSTEM[rgb[0] / 16], HEX_SYSTEM[rgb[0] % 16],
	// 	HEX_SYSTEM[rgb[1] / 16], HEX_SYSTEM[rgb[1] % 16],
	// 	HEX_SYSTEM[rgb[2] / 16], HEX_SYSTEM[rgb[2] % 16]);
	// printf("Floor RGB (Int Value) = %d\n", prog->tex.floor_rgb);
	// printf("Ceiling RGB (Hex Value) = %c%c%c%c%c%c\n",
	// 	HEX_SYSTEM[rgb[3] / 16], HEX_SYSTEM[rgb[3] % 16],
	// 	HEX_SYSTEM[rgb[4] / 16], HEX_SYSTEM[rgb[4] % 16],
	// 	HEX_SYSTEM[rgb[5] / 16], HEX_SYSTEM[rgb[5] % 16]);
	// printf("Ceiling RGB (Int Value) = %d\n", prog->tex.ceiling_rgb);
}

// https://www.developintelligence.com/blog/2017/02/rgb-to-hex-understanding-the-major-web-color-codes/
/*
** saves the rgb information stored in prog->tex.floor & prog->tex.ceiling
** to the rgb[6] array and computes for the hexadecimal representation of
** each individual rgb component. Afterwards, it takes the sum of all components
** which will then be type-casted into an int and saved to prog->tex.floor_rgb
** & prog->tex.ceiling_rgb for use in later functions
**
** rgb_array[0] = 2d array containing the rgb values of the floor's color
** rgb_array[0][0] = Floor R
** rgb_array[0][1] = Floor G
** rgb_array[0][2] = Floor B
** rgb_array[1] = 2d array containing the rgb values of the ceiling's color
** rgb_array[1][0] = Ceiling R
** rgb_array[1][1] = Ceiling G
** rgb_array[1][2] = Ceiling B
*/
void	get_floor_and_ceiling_rgb(t_program *prog)
{
	char	**rgb_array[2];
	// int		rgb[6];

	// ft_bzero(&rgb, 6 * sizeof(int));
	rgb_array[0] = ft_split(prog->tex.floor, ',');
	rgb_array[1] = ft_split(prog->tex.ceiling, ',');
	// save_rgb_components(rgb_array, rgb);
	save_rgb_components(&prog->tex.rgb, rgb_array);
	prog->tex.rgb.floor = convert_hex_to_int(&prog->tex.rgb, true);
	prog->tex.rgb.ceiling = convert_hex_to_int(&prog->tex.rgb, false);
	// prog->tex.floor_rgb = convert_hex_to_int(rgb[0], rgb[1], rgb[2]);
	// prog->tex.ceiling_rgb = convert_hex_to_int(rgb[3], rgb[4], rgb[5]);
	// print_rgb_info(prog, rgb);
	print_rgb_info(&prog->tex.rgb);
	free_2d_array(rgb_array[0]);
	free_2d_array(rgb_array[1]);
}
