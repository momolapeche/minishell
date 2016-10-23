/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 10:24:54 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 12:57:58 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_var(char **cmd, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j] == var[j] && cmd[i][j])
			j++;
		if (!cmd[i][j] && var[j] == '=')
			return (1);
	}
	return (0);
}

void	make_env(t_env *e)
{
	t_list	*l;
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (e->nb_env + 1));
	new[e->nb_env] = NULL;
	i = 0;
	l = e->env_l;
	while (l)
	{
		l->content_size = i;
		new[i] = l->content;
		i++;
		l = l->next;
	}
	free(e->env);
	e->env = new;
}

void	mini_unsetenv(char **cmd, t_env *e)
{
	int		i;
	t_list	*l;
	t_list	*tmp;

	if (!cmd[1])
		error(cmd[0], TOO_FEW_ARGUMENTS);
	else
	{
		while (e->env_l && test_var(cmd, e->env_l->content))
		{
			tmp = e->env_l->next;
			free(e->env_l->content);
			free(e->env_l);
			e->env_l = tmp;
			e->nb_env--;
		}
		l = e->env_l;
		while (l->next)
		{
			if (test_var(cmd, l->next->content))
			{
				tmp = l->next->next;
				free(l->next->content);
				free(l->next);
				l->next = tmp;
				e->nb_env--;
			}
			else
				l = l->next;
		}
		make_env(e);
	}
}
