/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 11:20:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "alloc/list.h"

t_list* ft_lstnew(void* content) {
  t_list* node = (t_list*)malloc(sizeof(t_list));
  if (!node) return NULL;
  node->content = content;
  node->next = NULL;
  return node;
}
