/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 09:58:18 by rmenegau          #+#    #+#             */
/*   Updated: 2016/10/23 12:51:51 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *cmd, int error)
{
	ft_putstr(cmd);
	write(1, ": ", 2);
	if (error == TOO_MANY_ARGUMENTS)
		write(1, "Too many arguments.\n", 20);
	if (error == TOO_FEW_ARGUMENTS)
		write(1, "Too few arguments.\n", 19);
	if (error == COMMAND_NOT_FOUND)
		write(1, "Command not found.\n", 19);
	if (error == NO_SUCH_FILE)
		write(1, "No such file or directory.\n", 27);
	if (error == PERMISSION_DENIED)
		write(1, "Permission denied.\n", 19);
	if (error == NOT_A_DIRECTORY)
		write(1, "Not a directory.\n", 17);
	if (error == VARIABLE_NAME_BEGIN_LETTER)
		write(1, "Variable name must begin with a letter.\n", 40);
	if (error == VARIABLE_NAME_MUST_ALNUM)
		write(1, "Variable name must contain alphanumeric characters.\n", 52);
	return (1);
}
