/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_internal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:10:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 13:20:55 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.int.h"

bool map_key_cmp(const t_map* m, const t_map_entry* entry, const void* key,
                 size_t key_size) {
  if (entry->key_size != key_size) return false;
  if (m->cmp != NULL)
    return m->cmp(entry->key, entry->key_size, key, key_size) == 0;
  return memcmp(entry->key, key, key_size) == 0;
}

t_list* map_find_entry(t_map* m, const void* key, size_t key_size,
                       t_list** out_prev) {
  t_list* current = m->entries;
  t_list* prev = NULL;
  while (current != NULL) {
    t_map_entry* entry = (t_map_entry*)current->content;
    if (map_key_cmp(m, entry, key, key_size)) {
      if (out_prev != NULL) *out_prev = prev;
      return current;
    }
    prev = current;
    current = current->next;
  }
  if (out_prev != NULL) *out_prev = NULL;
  return NULL;
}

void map_entry_free(t_map_entry* entry) {
  if (entry->owned & MAP_OWN_KEY) {
    if (entry->del_key != NULL)
      entry->del_key(entry->key);
    else
      free(entry->key);
  }
  if (entry->owned & MAP_OWN_VALUE) {
    if (entry->del_value != NULL)
      entry->del_value(entry->value);
    else
      free(entry->value);
  }
}
