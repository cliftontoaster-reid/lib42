/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_foreach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:59:50 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 15:06:30 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/map.int.h"

t_list* map_foreach(t_map* m,
                    void* (*func)(const t_map_entry* entry, void* arg),
                    void* arg) {
  if (m == NULL || func == NULL) return NULL;

  t_list* results = NULL;
  t_list* current = m->entries;

  while (current != NULL) {
    t_map_entry* entry = (t_map_entry*)current->content;

    void* result = func(entry, arg);
    t_list* result_node = ft_lstnew(result);
    if (result_node == NULL) {
      /* We return what is already created, user is responsible for freeing */
      return results;
    }
    current = current->next;
    ft_lstadd_back(&results, result_node);
  }
  return results;
}
