/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:56:54 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 15:44:16 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/map.int.h"

void map_clear(t_map* m) {
  if (m == NULL) return;

  t_list* current = m->entries;
  while (current != NULL) {
    t_map_entry* entry = (t_map_entry*)current->content;
    map_entry_free(entry);
    free(entry);
    t_list* next = current->next;
    free(current);
    current = next;
  }
  m->entries = NULL;
  m->size = 0;
}
