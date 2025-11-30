/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:15 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/list.h"

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
