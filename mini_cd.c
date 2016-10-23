/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 00:04:01 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 11:37:53 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_cd(char **cmd)
{
	struct stat	buf;

	if (cmd[1] && cmd[2])
		return (error(cmd[0], TOO_MANY_ARGUMENTS));
	if (access(cmd[1], F_OK))
		return (error(cmd[1], NO_SUCH_FILE));
	else
	{
		stat(cmd[1], &buf);
		if (!S_ISDIR(buf.st_mode))
			return (error(cmd[1], NOT_A_DIRECTORY));
		else if (access(cmd[1], X_OK))
			return (error(cmd[1], PERMISSION_DENIED));
	}
	return (0);
}

void	mini_cd(char **cmd, t_env *e)
{
	char		*new_pwd;
	t_list		*pwd;
	t_list		*oldpwd;

	if (error_cd(cmd))
		return ;
	new_pwd = NULL;
	if (cmd[1])
	{
		if (cmd[1][0] == '-' && cmd[1][0] == '\0')
			new_pwd = ft_strdup(e->old_pwd);
		else
			new_pwd = ft_strdup(cmd[1]);
	}
	if (new_pwd)
	{
		free(e->old_pwd);
		e->old_pwd = getcwd(NULL, 0);
		chdir(new_pwd);
		free(new_pwd);
		if ((oldpwd = search_var("OLDPWD", e->env_l)))
		{
			free(oldpwd->content);
			oldpwd->content = ft_strjoin("OLDPWD=", e->old_pwd);
			e->env[oldpwd->content_size] = oldpwd->content;
		}
		if ((pwd = search_var("PWD", e->env_l)))
		{
			free(pwd->content);
			pwd->content = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
			e->env[pwd->content_size] = pwd->content;
		}
	}
}
