/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:23 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 15:27:52 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

// Checks the unset argument for not allowed characters
int	is_unset_var_valid(char *var)
{
	int	i;

	i = -1;
	while (i++, var[i])
	{
		if (i == 0 && !check_first_c(var[i]))
			return (0);
		if (i > 0 && !check_other_c(var[i]))
			return (0);
	}
	return (1);
}

int	builtin_unset(t_ms *ms, char **arr)
{
	int	i;
	int	ret_code;

	ret_code = 0;
	i = 0;
	if (!arr)
		return (0);
	while (i++, arr[i])
	{
		if (is_unset_var_valid(arr[i]))
		{
			delete_node_from_llst(&ms->env_llst_sorted,
				find_var_in_llst(&ms->env_llst_sorted, arr[i]));
			delete_node_from_llst(&ms->env_llst,
				find_var_in_llst(&ms->env_llst, arr[i]));
		}
		else
		{
			c_red();
			printf("minishell: unset: `%s': not a valid identifier\n", arr[i]);
			c_reset();
			ret_code = 1;
		}
	}
	return (ret_code);
}

void	test_parser_unset(t_list **env_llst,
			t_list **env_llst_sorted, char *str)
{
	if (ft_strncmp("unset", str, 5) == 0 && ft_strlen(str) > 5)
	{
		delete_node_from_llst(env_llst_sorted,
			find_var_in_llst(env_llst_sorted, str + 6));
		delete_node_from_llst(env_llst, find_var_in_llst(env_llst, str + 6));
	}
}
