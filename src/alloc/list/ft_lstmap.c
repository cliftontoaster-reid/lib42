/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
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
    if (!new_content) {
      ft_lstclear(&new_list, del);
      return NULL;
    }
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
