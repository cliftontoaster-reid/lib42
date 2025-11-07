/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 11:20:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc/list.h"

void ft_lstadd_back(t_list** lst, t_list* new) {
  t_list* last;

  if (!lst || !new) return;
  if (*lst == NULL) {
    *lst = new;
    return;
  }
  last = ft_lstlast(*lst);
  if (last) last->next = new;
}
