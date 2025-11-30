/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:48:43 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 13:21:02 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"

void* map_get(t_map* m, const void* key, size_t key_size,
              size_t* out_value_size) {
  if (m == NULL || key == NULL || key_size == 0) {
    if (out_value_size != NULL) *out_value_size = 0;
    errno = EINVAL;
    return NULL;
  }

  t_list* node = map_find_entry(m, key, key_size, NULL);
  if (node == NULL) {
    if (out_value_size != NULL) *out_value_size = 0;
    return NULL;
  }

  t_map_entry* entry = (t_map_entry*)node->content;
  if (out_value_size != NULL) *out_value_size = entry->value_size;
  return entry->value;
}
