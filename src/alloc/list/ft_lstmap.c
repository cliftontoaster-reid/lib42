/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 11:20:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "alloc/list.h"

t_list* ft_lstmap(t_list* lst, void* (*f)(void*), void (*del)(void*)) {
  t_list* new_list = NULL;
  t_list* new_node = NULL;
  t_list* last = NULL;
  void* new_content;

  if (!lst || !f) return NULL;
  while (lst) {
    new_content = f(lst->content);
    new_node = ft_lstnew(new_content);
    if (!new_node) {
      if (del && new_content) del(new_content);
      ft_lstclear(&new_list, del);
      return NULL;
    }
    if (!new_list)
      new_list = new_node;
    else
      last->next = new_node;
    last = new_node;
    lst = lst->next;
  }
  return new_list;
}
