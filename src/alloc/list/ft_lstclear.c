/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/list.h"

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
