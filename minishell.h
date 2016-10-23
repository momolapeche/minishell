/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 17:05:40 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 12:44:03 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/stat.h>

# define TOO_MANY_ARGUMENTS 0
# define TOO_FEW_ARGUMENTS 1
# define COMMAND_NOT_FOUND 2
# define NO_SUCH_FILE 3
# define PERMISSION_DENIED 4
# define NOT_A_DIRECTORY 5
# define VARIABLE_NAME_BEGIN_LETTER 6
# define VARIABLE_NAME_MUST_ALNUM 7

typedef struct	s_env
{
	t_list	*env_l;
	char	**env;
	int		nb_env;
	char	*old_pwd;
	char	*exit;
}				t_env;

t_list	*search_var(char *name, t_list *l);
void	free_env(t_env e);
char	***split_cmd(char const *line);
void	swap_var_quote(char ***cmd, char **env);
int		error(char *cmd, int error);
void	mini_exit(t_env e);
void	mini_env(char **cmd, t_env *e);
void	mini_setenv(char **cmd, t_env *e);
void	mini_unsetenv(char **cmd, t_env *e);
void	mini_cd(char **cmd, t_env *e);
void	mini_echo(char **cmd);

#endif
