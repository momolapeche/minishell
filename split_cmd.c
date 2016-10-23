/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 22:15:38 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 17:37:32 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quote_len(char const *line, char const quote)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != quote)
		i++;
	return (line[i] == quote ? i : -1);
}

int		nb_arg(char const *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (line[i] && line[i] != ';')
	{
		if (line[i] != ' ' && line[i] != '\t' && ++nb)
			while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ';')
				i += line[i] == '\'' || line[i] == '\"' ? quote_len(&line[i + 1], line[i]) + 2 : 1;
		else
			i++;
	}
	return (nb);
}

int		nb_cmd(char const *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (line[i])
	{
		if (line[i] != ';' && nb_arg(&line[i]) && ++nb)
			while (line[i] && line[i] != ';')
				i += line[i] == '\'' || line[i] == '\"' ? quote_len(&line[i + 1], line[i]) + 2 : 1;
		else
			i++;
	}
	return (nb);
}

char	**split_arg(char const *line, int *tmp)
{
	char	**ret;
	int		i;
	int		nb;
	int		j;

	nb = nb_arg(&line[*tmp]);
	ret = (char **)malloc(sizeof(char *) * (nb + 1));
	ret[nb] = NULL;
	i = 0;
	while (line[*tmp] == ';')
		(*tmp)++;
	while (i < nb)
	{
		while (line[*tmp] == ' ' || line[*tmp] == '\t')
			(*tmp)++;
		j = *tmp;
		while (line[*tmp] && line[*tmp] != ' ' && line[*tmp] != '\t' && line[*tmp] != ';')
			*tmp += line[*tmp] == '\'' || line[*tmp] == '\"' ? quote_len(&line[*tmp + 1], line[*tmp]) + 2 : 1;
		ret[i] = ft_strsub(line, j, *tmp - j);
		i++;
	}
	while (line[*tmp] == ';' || line[*tmp] == ' ' || line[*tmp] == '\t')
		(*tmp)++;
	return (ret);
}

char	***split_cmd(char const *line)
{
	char	***cmd;
	int		nb;
	int		i;
	int		tmp;

	nb = nb_cmd(line);
//	ft_putendl(ft_itoa(nb));
	cmd = (char ***)malloc(sizeof(char **) * (nb + 1));
	i = 0;
	tmp = 0;
	while (i < nb)
		cmd[i++] = split_arg(line, &tmp);
	cmd[i] = NULL;
	return (cmd);
}
