/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:09:39 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 14:58:40 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"

int map_remove(t_map* m, const void* key, size_t key_size) {
  if (m == NULL || key == NULL || key_size == 0) {
    errno = EINVAL;
    return false;
  }

  t_list* prev = NULL;
  t_list* node = map_find_entry(m, key, key_size, &prev);
  if (node == NULL) {
    errno = ENOENT;
    return false;
  }

  /* Unlink from list */
  if (prev == NULL)
    m->entries = node->next;
  else
    prev->next = node->next;

  /* Free entry resources */
  t_map_entry* entry = (t_map_entry*)node->content;
  map_entry_free(entry);
  free(entry);
  free(node);
  m->size--;
  return true;
}
