/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:52:28 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 13:30:54 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_env_var_name_len(char *str)
{
	char	*cur;

	cur = str;
	cur++;
	while (*cur && (ft_isalnum(*cur) || *cur == '_'))
		cur++;
	return (cur - str);
}

void	concatinate_line_input_to_str(char **dst, char *src)
{
	char	*temp;

	temp = *dst;
	*dst = malloc(ft_strlen(temp) + ft_strlen(src) + 2);
	if (temp != NULL)
	{
		ft_strlcpy(*dst, temp, ft_strlen(temp) + 1);
		ft_strlcat(*dst, src,
			ft_strlen(*dst) + ft_strlen(src) + 1);
		free(temp);
	}
	else
		ft_strlcpy(*dst, src, ft_strlen(src) + 1);
	ft_strlcat(*dst, "\n", ft_strlen(*dst) + 2);
}

void	append_env_var(char **dst_str, char **str, t_ms *ms)
{
	char	*env_variable;
	char	*var_name;
	size_t	var_name_len;

	var_name_len = get_env_var_name_len(*str);
	var_name = malloc((var_name_len) * sizeof(char));
	check_if_malloc_failed((void *)var_name, ms);
	ft_strlcpy(var_name, (*str) + 1, var_name_len);
	(*str) += var_name_len - 1;
	env_variable = get_val_of_var(&(ms->env_llst), var_name);
	free(var_name);
	if (env_variable == NULL)
		return ;
	append_string(ms, dst_str, env_variable, ft_strlen(env_variable));
	if (env_variable)
		free(env_variable);
}
