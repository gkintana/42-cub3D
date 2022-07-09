/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoro <mgregoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:47:33 by myael             #+#    #+#             */
/*   Updated: 2022/06/07 14:31:53 by mgregoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_check_struct(t_check	*ch)
{
	ch->amount = 0;
	ch->nt = 0;
	ch->st = 0;
	ch->wt = 0;
	ch->et = 0;
	ch->floor = 0;
	ch->ceiling = 0;
	ch->line = NULL;
	ch->trimmed = NULL;
	ch->fd = -1;
}

void	init_player_checker_struct(t_all *all)
{
	t_ch_map	*check;

	check = malloc(sizeof(t_ch_map));
	check->amount = 0;
	check->e = 0;
	check->n = 0;
	check->s = 0;
	check->w = 0;
	check->space_line = 0;
	all->checker = check;
}

void	init_data_for_textures_and_speed(t_all *all)
{
	all->s_tex = malloc(sizeof(t_win));
	all->w_tex = malloc(sizeof(t_win));
	all->e_tex = malloc(sizeof(t_win));
	all->n_tex = malloc(sizeof(t_win));
	img_to_xpm_data_my(all->win, all->data->s_texture, all->s_tex);
	img_to_xpm_data_my(all->win, all->data->n_texture, all->n_tex);
	img_to_xpm_data_my(all->win, all->data->e_texture, all->e_tex);
	img_to_xpm_data_my(all->win, all->data->w_texture, all->w_tex);
	all->player->move_speed = MOVESPEED;
	all->player->rot_speed = ROTSPEED;
}
