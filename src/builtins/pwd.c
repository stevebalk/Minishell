/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:40:32 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 20:12:40 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	builtin_pwd(t_list **env_llst, t_list **env_llst_sorted, int print_pwd)
{
	char	*buffer;
	char	*pwd;
	size_t	size;

	(void)env_llst;
	(void)env_llst_sorted;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (buffer == NULL)
		perror("Unable to allocate buffer");
	if (getcwd(buffer, size) == NULL)
		perror("Error getting current directory");
	if (print_pwd)
		printf("%s\n", buffer);
	pwd = join_three_string("PWD", "=", buffer);
	if (env_llst && env_llst)
		export_single_arg(env_llst, env_llst_sorted, pwd);
	free(pwd);
	free(buffer);
	return (0);
}
