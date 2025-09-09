/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_envp_array_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:11:17 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/09/08 23:23:18 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

static int	env_count(t_env *e)
{
	int	n;

	n = 0;
	while (e)
	{
		if (e->name)
			n++;
		e = e->next;
	}
	return (n);
}

static char	*env_kv(t_env *e)
{
	char	*kv;
	char	*tmp;

	tmp = ft_strjoin(e->name, "=");
	if (!tmp)
		return (NULL);
	kv = ft_strjoin(tmp, e->value ? e->value : "");
	free(tmp);
	return (kv);
}

char	**env_to_array(t_env *list)
{
	int		i;
	int		n;
	char	**arr;

	n = env_count(list);
	arr = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (list)
	{
		if (list->name)
		{
			arr[i] = env_kv(list);
			if (!arr[i])
				return (free_envp_array(arr), (char **)NULL);
			i++;
		}
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_envp_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	env_resync_array(char ***dst_envp, t_env *list)
{
	char	**fresh;

	if (!dst_envp)
		return (1);
	fresh = env_to_array(list);
	if (!fresh)
		return (1);
	free_envp_array(*dst_envp);
	*dst_envp = fresh;
	return (0);
}
