/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:02:36 by myael             #+#    #+#             */
/*   Updated: 2022/06/14 15:27:31 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	make_double_array_map_2(t_map *m, t_all *all, t_list *head)
{
	m->map[++all->i] = NULL;
	m->height = all->height;
	m->width = all->width;
	all->m = m;
	free_chained_list(head);
}

void	make_double_array_map(t_all *all, t_list *lst, int height, int width)
{
	t_list	*head;
	t_map	*m;
	char	*temp;

	all->i = -1;
	m = malloc(sizeof(t_map));
	m->map = malloc(sizeof(char *) * (height + 1));
	head = lst;
	while (lst)
	{
		if ((int)ft_strlen(lst->content) < width)
		{
			temp = ft_spaces_str(width, ft_strlen(lst->content));
			m->map[++all->i] = ft_strjoin(lst->content, temp);
			free(temp);
		}
		else
			m->map[++all->i] = ft_strdup(lst->content);
		free(lst->content);
		lst = lst->next;
	}
	make_double_array_map_2(m, all, head);
}

void	continue_parsing(t_all *all, t_list *lst)
{
	make_double_array_map(all, lst, all->height, all->width);
	init_player_checker_struct(all);
	check_map_correctness(all);
	check_if_map_has_player(all);
}

void	parse_map(t_check *ch, t_all *all)
{
	t_list	*lst;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(ch->line));
	all->width = ft_strlen(ch->line);
	all->height = 1;
	while (get_next_line(ch->fd, &ch->line))
	{
		ft_lstadd_back(&lst, ft_lstnew(ch->line));
		all->temp = ft_strlen(ch->line);
		if (all->temp > all->width)
			all->width = all->temp;
		all->height++;
	}
	if (all->height != 1)
	{
		ch->trimmed = ft_strtrim(ch->line, " \t\n");
		if (*(ch->trimmed))
		{
			ft_lstadd_back(&lst, ft_lstnew(ch->line));
			all->height++;
		}
		free(ch->trimmed);
	}
	continue_parsing(all, lst);
}

void	parse_data(char **argv, t_all *all)
{
	t_data	*data;
	t_check	ch;

	init_check_struct(&ch);
	data = malloc(sizeof(t_data));
	if (!data)
		error_exit("Malloc error", 21);
	ch.fd = open(argv[1], O_RDONLY);
	if (ch.fd == -1)
		error_exit("Couldn't open the file", 22);
	while (get_next_line(ch.fd, &ch.line) && ch.amount < 6)
	{
		ch.trimmed = ft_strtrim(ch.line, " \t\v\f\r");
		free(ch.line);
		if (ch.trimmed && *(ch.trimmed))
			add_texture_to_struct(data, &ch);
		else if (ch.trimmed)
			free(ch.trimmed);
	}
	if (ch.amount < 6)
		error_exit("Not enough data", 23);
	skip_empty_lines(&ch);
	parse_map(&ch, all);
	all->data = data;
	close(ch.fd);
}
