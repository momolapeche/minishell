/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 15:48:19 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 17:37:42 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	create_env(char **env)
{
	t_env	e;
	int		i;

	i = 0;
	while (env[i])
		i++;
	e.env_l = NULL;
	e.env = (char **)malloc(sizeof(char *) * (i + 1));
	e.env[i] = NULL;
	e.nb_env = i;
	e.old_pwd = ft_strdup("");
	e.exit = NULL;
	while (i--)
	{
		ft_lstadd(&e.env_l, ft_lstnew(env[i], ft_strlen(env[i]) + 1));
		e.env[i] = e.env_l->content;
		e.env_l->content_size = i;
	}
	return (e);
}

t_list	*search_var(char *name, t_list *l)
{
	int	i;

	while (l)
	{
		i = 0;
		while (name[i] && name[i] == ((char *)(l->content))[i])
			i++;
		if (((char *)(l->content))[i] == '=' && !name[i])
			break ;
		l = l->next;
	}
	return (l);
}

void	free_cmd(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
			free(cmd[i][j++]);
		free(cmd[i++]);
	}
	free(cmd);
}

void	free_env(t_env e)
{
	t_list	*tmp;

	while (e.env_l)
	{
		tmp = e.env_l;
		e.env_l = e.env_l->next;
		free(tmp->content);
		free(tmp);
	}
}

char	*path_join(char *path, char *name)
{
	char	*ret;
	int		name_len;
	int		path_len;

	name_len = ft_strlen(name);
	path_len = ft_strlen(path);
	ret = (char *)malloc(sizeof(char) * (name_len + path_len + 2));
	ft_memcpy(ret, path, path_len);
	ret[path_len] = '/';
	ft_memcpy(&ret[path_len + 1], name, name_len);
	ret[path_len + name_len + 1] = '\0';
	return (ret);
}

char	*get_path(t_env *e, char *cmd)
{
	char	*path;
	char	**tmp_split;
	int		i;
	t_list	*path_var;

	path_var = search_var("PATH", e->env_l);
	path = NULL;
	if (path_var && path_var->content && (tmp_split = ft_strsplit(&((char *)(path_var->content))[5], ':')))
	{
		i = 0;
		while (tmp_split[i])
		{
			if (!access(path = path_join(tmp_split[i], cmd), F_OK | X_OK))
				break ;
			free(path);
			i++;
		}
		if (!tmp_split[i])
			path = NULL;
		i = 0;
		while (tmp_split[i])
			free(tmp_split[i++]);
		free(tmp_split);
	}
	return (path);
}

void	exec_cmd(char *path, t_env *e, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		execve(path, cmd, e->env);
		exit(0);
	}
	wait(NULL);
}

int		builtin_exec(t_env *e, char **cmd)
{
	char	*tmp;

	if ((tmp = get_path(e, cmd[0])))
	{
		exec_cmd(tmp, e, cmd);
		free(tmp);
		return (0);
	}
	return (1);
}

void	cmd_handle(t_env *e, char **cmd)
{
	if (cmd[0])
	{
		if (ft_strnequ(cmd[0], "exit", 5))
		{
			if (cmd[1] && cmd[2])
				error(cmd[0], TOO_MANY_ARGUMENTS);
			else
				e->exit = cmd[1] ? ft_strdup(cmd[1]) : ft_strdup("");
		}
		else if (ft_strnequ(cmd[0], "cd", 3))
			mini_cd(cmd, e);
		else if (ft_strnequ(cmd[0], "echo", 5))
			mini_echo(cmd);
		else if (ft_strnequ(cmd[0], "env", 4))
			mini_env(cmd, e);
		else if (ft_strnequ(cmd[0], "setenv", 7))
			mini_setenv(cmd, e);
		else if (ft_strnequ(cmd[0], "unsetenv", 9))
			mini_unsetenv(cmd, e);
		else if (builtin_exec(e, cmd))
		{
			if (!access(cmd[0], F_OK) && !access(cmd[0], X_OK))
					exec_cmd(cmd[0], e, cmd);
			else
				error(cmd[0], COMMAND_NOT_FOUND);
		}
	}
}
/*
void	aff_cmd(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			printf("cmd[%i][%i] = %s\n", i, j, cmd[i][j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}*/

void	minishell(t_env e)
{
	int		i;
	char	*buf;
	char	***cmd;

	while (!e.exit)
	{
		write(1, "$> ", 3);
		get_next_line(0, &buf);
		cmd = split_cmd(buf);
		swap_var_quote(cmd, e.env);
//		aff_cmd(cmd);
		i = 0;
		while (cmd[i])
			cmd_handle(&e, cmd[i++]);
		free_cmd(cmd);
		free(buf);
//		e.exit = ft_strdup("0");
	}
	mini_exit(e);
}

int		main(int ac, char **av, char **env)
{
	minishell(create_env(env));
	return (0);
}
