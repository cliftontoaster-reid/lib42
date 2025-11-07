/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 11:20:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "alloc/list.h"

void ft_lstclear(t_list** lst, void (*del)(void*)) {
  t_list* cur;
  t_list* next;

  if (!lst || !*lst) return;
  cur = *lst;
  while (cur) {
    next = cur->next;
    if (del) del(cur->content);
    free(cur);
    cur = next;
  }
  *lst = NULL;
}
