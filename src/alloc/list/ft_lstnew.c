/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/list.h"

t_list* ft_lstnew(void* content) {
  t_list* node = (t_list*)malloc(sizeof(t_list));
  if (!node) return NULL;
  node->content = content;
  node->next = NULL;
  return node;
}
