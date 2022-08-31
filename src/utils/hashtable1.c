/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:29:34 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/31 13:48:13 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashlist	*hashlist_new(char *key, int value)
{
	t_hashlist	*new;

	new = malloc(sizeof(t_hashlist));
	new->next = NULL;
	new->key = ft_strdup(key);
	new->value = value;
	return (new);
}

void	hashlist_addfront(t_hashlist **lst, t_hashlist *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	hashlist_addback(t_hashlist **lst, t_hashlist *new)
{
	t_hashlist	*temp;

	if (!(*lst))
	{
		hashlist_addfront(lst, new);
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

static void	hashlist_clearnodes(t_hashlist **lst)
{
	if (*lst)
	{
		hashlist_clearnodes(&(*lst)->next);
		if ((*lst)->key)
			free((*lst)->key);
		free(*lst);
		*lst = NULL;
	}
}

void	hashlist_clear(t_hashlist **lst)
{
	if (lst)
		hashlist_clearnodes(lst);
	free(lst);
	lst = NULL;
}
