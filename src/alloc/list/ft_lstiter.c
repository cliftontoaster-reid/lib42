/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 11:20:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc/list.h"

void ft_lstiter(t_list* lst, void (*f)(void*)) {
  while (lst) {
    if (f) f(lst->content);
    lst = lst->next;
  }
}
