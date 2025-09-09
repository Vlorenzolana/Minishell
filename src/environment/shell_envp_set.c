/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:42:02 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/09/09 07:42:23 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static t_env	*env_find(t_env *env, const char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static t_env	*env_new_pair(const char *name, const char *value)
{
	t_env	*e;

	e = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!e)
		return (NULL);
	e->name = ft_strdup(name);
	e->value = ft_strdup(value ? value : "");
	e->visible = true;
	if (!e->name || !e->value)
	{
		free(e->name);
		free(e->value);
		free(e);
		return (NULL);
	}
	return (e);
}

int	env_set(t_env **env, const char *name, const char *value)
{
	t_env	*cur;
	t_env	*node;

	if (!env || !name || !*name)
		return (1);
	cur = env_find(*env, name);
	if (cur)
	{
		free(cur->value);
		cur->value = ft_strdup(value ? value : "");
		return (cur->value == NULL);
	}
	node = env_new_pair(name, value);
	if (!node)
		return (1);
	add_shell_envp(env, node);
	return (0);
}
