/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 11:20:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "alloc/list.h"

void ft_lstdelone(t_list* lst, void (*del)(void*)) {
  t_list* next;

  if (!lst) return;

  /* If there is a following node we can "remove" the current node by
   * copying the next node's content into the current node and freeing the
   * next node. This effectively relinks the surrounding nodes while keeping
   * the same pointer value for the caller. */
  if (lst->next) {
    next = lst->next;
    /* Free the current node's content if a deleter is provided. Do NOT
     * free the content coming from `next` because we are moving that
     * pointer into `lst->content` and it must remain valid. */
    if (del && lst->content) del(lst->content);
    lst->content = next->content;
    lst->next = next->next;
    free(next);
    return;
  }

  /* If this is the last node we cannot relink without access to the
   * previous node, so fall back to the original behavior: free the
   * content (if del provided) and free the node itself. */
  if (del && lst->content) del(lst->content);
  free(lst);
}
