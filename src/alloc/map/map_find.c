/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:07:14 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 15:07:50 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/map.int.h"

t_map_entry* map_find(t_map* m,
                      bool (*predicate)(const t_map_entry* entry, void* arg),
                      void* arg) {
  if (m == NULL || predicate == NULL) return NULL;

  t_list* current = m->entries;

  while (current != NULL) {
    t_map_entry* entry = (t_map_entry*)current->content;
    if (predicate(entry, arg)) {
      return entry;
    }
    current = current->next;
  }
  return NULL;
}
