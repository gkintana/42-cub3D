/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoro <mgregoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:46:51 by myael             #+#    #+#             */
/*   Updated: 2022/06/07 14:31:48 by mgregoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_chained_list(t_list *head)
{
	t_list	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_double_array(char **arr)
{
	char	**pointer;

	pointer = arr;
	while (*arr)
	{
		free(*arr);
		*arr = NULL;
		arr++;
	}
	free(pointer);
	arr = NULL;
}

void	free_memory(t_all *all)
{
	free(all->data->e_texture);
	free(all->data->s_texture);
	free(all->data->n_texture);
	free(all->data->w_texture);
	free(all->data);
	free_double_array(all->m->map);
	free(all->m);
	free(all->rc);
	free(all->checker);
	free(all->player);
	free(all->plane);
	free(all->s_tex);
	free(all->n_tex);
	free(all->w_tex);
	free(all->e_tex);
}

int	close_win(t_all *all)
{
	free_memory(all);
	mlx_destroy_image(all->win->mlx, all->win->img);
	mlx_destroy_window(all->win->mlx, all->win->win);
	free(all->win);
	printf("Game finished!\n");
	exit(0);
}

void	check_malloc_err(char *data, char *message, int num)
{
	if (!data)
		error_exit(message, num);
}
