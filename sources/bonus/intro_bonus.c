/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/08/10 20:00:54 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <miniaudio_bonus.h>

static int	music(char *path)
{
    ma_result	result;
    ma_engine	engine;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
	{
        ft_putstr_fd("Error\nAudio Failed", 2);
        return (1);
    }
    ma_engine_play_sound(&engine, path, NULL);
	sleep(8);
    ma_engine_uninit(&engine);
    return (0);
}

static void	init_intro_images(t_program *prog, void *pic[], int width[],
			int height[])
{
	pic[0] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/1.xpm",
		&width[0], &height[0]);
	pic[1] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/2.xpm",
		&width[1], &height[1]);
	pic[2] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/3.xpm",
		&width[2], &height[2]);
	pic[3] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/4.xpm",
		&width[3], &height[3]);
}

static void	destroy_intro_images(t_program *prog, void *pic[])
{
	mlx_destroy_image(prog->mlx.ptr, pic[0]);
	mlx_destroy_image(prog->mlx.ptr, pic[1]);
	mlx_destroy_image(prog->mlx.ptr, pic[2]);
	mlx_destroy_image(prog->mlx.ptr, pic[3]);
}

static void	start_slideshow(t_program *prog, void *pic[])
{
	mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window, pic[0], 0, 0);
	mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window, pic[1], 950, 0);
	sleep(2);
	mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
	mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window, pic[2], 175, 0);
	sleep(2);
	mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
	mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window, pic[3], 0, 0);
}

void	play_intro(t_program *prog)
{
	int		width[4];
	int		height[4];
	void	*pic[4];

	ft_bzero(pic, sizeof(void *) * 4);
	init_intro_images(prog, pic, width, height);
	start_slideshow(prog, pic);
	music("assets/intro/temp.mp3");
	destroy_intro_images(prog, pic);
	ft_bzero(pic, sizeof(void *) * 4);
}
