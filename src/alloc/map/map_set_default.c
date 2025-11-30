/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:01:27 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 15:13:02 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "42/alloc/map.int.h"
int map_set_default(t_map* m, const void* key, const void* value) {
  size_t key_size = m->default_key_size;
  size_t value_size = m->default_value_size;
  if (key_size == 0 || value_size == 0) {
    /* Cannot use default sizes for variable-sized keys/values */
    errno = EINVAL;
    return false;
  }

  return map_set(m, key, key_size, value, value_size, MAP_OWN_BOTH, free, free);
}
