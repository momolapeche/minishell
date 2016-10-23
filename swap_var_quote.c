/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_var_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 04:03:23 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 08:44:59 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		swap_var_len(char const *line, int *i, char **env)
{
	int		len;
	int		j;
	int		k;

	len = 0;
	while (ft_isalnum(line[++(*i)]))
		len++;
	j = 0;
	while (env[j])
	{
		k = 0;
		while (env[j][k] && k < len && env[j][k] == line[*i - len + k])
			k++;
		if (env[j][k] == '=')
			return (ft_strlen(&env[j][k + 1]));
		j++;
	}
	return (-1);
}

int		swap_quote_len(char const *line, char const quote, int *i, char **env)
{
	int	len;

	len = 0;
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '$')
			len += swap_var_len(line, i, env);
		else
		{
			len++;
			(*i)++;
		}
	}
	(*i)++;
	return (len);
}

int		arg_new_len(char const *arg, char **env)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"'))
			len += swap_quote_len(arg, arg[i - 1], &i, env);
		if (arg[i] == '$')
			len += swap_var_len(arg, &i, env);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

int		swap_var(char *ret, char const *line, int *i, char **env)
{
	int		len;
	int		j;
	int		k;

	len = 0;
	while (ft_isalnum(line[++(*i)]))
		len++;
	j = 0;
	while (env[j])
	{
		k = 0;
		while (env[j][k] && k < len && env[j][k] == line[*i - len + k])
			k++;
		if (env[j][k] == '=')
			break ;
		j++;
	}
	ft_memcpy(ret, &env[j][k + 1], (len = ft_strlen(&env[j][k + 1])));
	return (len);
}

void	fill_ret(char *ret, char const *arg, int const len, char **env)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (j < len)
	{
		if (arg[i] == '$')
			j += swap_var(&ret[j], arg, &i, env);
		else if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote = arg[i++];
			while (arg[i] && arg[i] != quote)
			{
				if (arg[i] == '$')
					j += swap_var(&ret[j], arg, &i, env);
				else
					ret[j++] = arg[i++];
			}
			i++;
		}
		else
			ret[j++] = arg[i++];
	}
	ret[j] = '\0';
}

char	*swap(char const *arg, char **env)
{
	char	*ret;
	int		len;

	len = arg_new_len(arg, env);
//	printf("len = %i\n", len);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	fill_ret(ret, arg, len, env);
	return (ret);
}

void	swap_var_quote(char ***cmd, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			cmd[i][j] = swap(cmd[i][j], env);
			j++;
		}
		i++;
	}
}
