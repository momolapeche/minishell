/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 08:55:12 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 12:49:57 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resize_env(t_env *e)
{
	char	**n_env;
	int		i;

	n_env = (char **)malloc(sizeof(char *) * (e->nb_env + 1));
	n_env[e->nb_env] = NULL;
	i = 0;
	while (e->env[i])
	{
		n_env[i] = e->env[i];
		i++;
	}
	free(e->env);
	e->env = n_env;
}

t_list	*get_var(t_env *e, char const *s)
{
	int		i;
	t_list	*l;
	t_list	*new;

	l = e->env_l;
	while (l)
	{
		i = 0;
		while (((char *)(l->content))[i] == s[i] && s[i])
			i++;
		if (!s[i] && ((char *)(l->content))[i] == '=')
			return (l);
		if (!l->next)
			break ;
		l = l->next;
	}
	new = ft_lstnew(NULL, 0);
	new->content_size = e->nb_env++;
	ft_lstaddl(&e->env_l, new);
	resize_env(e);
	return (l ? l->next : e->env_l);
}

int		error_setenv(char **cmd)
{
	int	i;

	i = 0;
	if (!ft_isalnum(cmd[1][0]) && cmd[1][0])
		return (error(cmd[0], VARIABLE_NAME_BEGIN_LETTER));
	while (ft_isalnum(cmd[1][i]) && cmd[1][i])
		i++;
	return (cmd[1][i] ? error(cmd[0], VARIABLE_NAME_MUST_ALNUM) : 0);
}

void	mini_setenv(char **cmd, t_env *e)
{
	t_list	*var;
	char	*tmp;

	if (!cmd[1])
		mini_env(cmd, e);
	else if (error_setenv(cmd))
		return ;
	else
	{
		var = get_var(e, cmd[1]);
		tmp = ft_strjoin(cmd[1], "=");
		tmp = ft_strjoin_free(tmp, cmd[2] ? cmd[2] : "", 1);
		if (var->content)
			free(var->content);
		var->content = tmp;
		e->env[var->content_size] = var->content;
	}
}
