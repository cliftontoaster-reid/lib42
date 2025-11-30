/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:55:56 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 14:58:39 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"
#include "42/memory/ops.h"

bool map_set(t_map* m, const void* key, size_t key_size, const void* value,
             size_t value_size, int owned_flags, void (*del_key)(void*),
             void (*del_value)(void*)) {
  if (m == NULL || key == NULL || key_size == 0) {
    errno = EINVAL;
    return false;
  }

  t_list* node = map_find_entry(m, key, key_size, NULL);
  if (node != NULL) {
    t_map_entry* entry = (t_map_entry*)node->content;
    /* Free old value if owned */
    if (entry->owned & MAP_OWN_VALUE) {
      if (entry->del_value != NULL)
        entry->del_value(entry->value);
      else
        free(entry->value);
    }

    /* Update value */
    entry->value_size = value_size;
    entry->owned = (entry->owned & MAP_OWN_KEY) | (owned_flags & MAP_OWN_VALUE);
    entry->del_value = del_value;
    if (owned_flags & MAP_OWN_VALUE) {
      entry->value = malloc(value_size);
      if (entry->value == NULL) {
        errno = ENOMEM;
        return false;
      }
      ft_memcpy(entry->value, value, value_size);
    } else {
      entry->value = (void*)value;
    }
    return true;
  } else {
    /* Create new entry */
    t_map_entry* entry = malloc(sizeof(t_map_entry));
    if (entry == NULL) {
      errno = ENOMEM;
      return false;
    }

    /* Set key */
    entry->key_size = key_size;
    entry->owned = owned_flags;
    entry->del_key = del_key;
    if (owned_flags & MAP_OWN_KEY) {
      entry->key = malloc(key_size);
      if (entry->key == NULL) {
        free(entry);
        errno = ENOMEM;
        return false;
      }
      ft_memcpy(entry->key, key, key_size);
    } else {
      entry->key = (void*)key;
    }

    /* Set value */
    entry->value_size = value_size;
    entry->del_value = del_value;
    if (owned_flags & MAP_OWN_VALUE) {
      entry->value = malloc(value_size);
      if (entry->value == NULL) {
        if (owned_flags & MAP_OWN_KEY) free(entry->key);
        free(entry);
        errno = ENOMEM;
        return false;
      }
      ft_memcpy(entry->value, value, value_size);
    } else {
      entry->value = (void*)value;
    }

    /* Insert into map */
    t_list* node = ft_lstnew(entry);
    if (node == NULL) {
      if (owned_flags & MAP_OWN_KEY) free(entry->key);
      if (owned_flags & MAP_OWN_VALUE) free(entry->value);
      free(entry);
      errno = ENOMEM;
      return false;
    }
    ft_lstadd_front(&m->entries, node);
    m->size++;
  }
  return true;
}
