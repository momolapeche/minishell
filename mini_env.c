/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 00:25:08 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 09:00:08 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(char **cmd, t_env *e)
{
	t_list	*l;

	l = e->env_l;
	while (l)
	{
		ft_putendl(l->content);
		l = l->next;
	}
}