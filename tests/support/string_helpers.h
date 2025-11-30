/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_helpers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:15:34 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 17:15:37 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>
#include <stdlib.h>

#include "42/alloc/string.h"

// Helper to create a new string for tests
static inline t_string* sh_new(const char* s) { return string_from(s); }

// Create an invalid t_string with wrong magic for tagged tests
static inline t_string* sh_make_invalid() {
  t_string* s = (t_string*)malloc(sizeof(t_string));
  if (!s) return NULL;
  s->magic = 0xDEADBEEF;
  s->capacity = 0;
  s->size = 0;
  s->data = NULL;
  return s;
}

// Free invalid t_string created by sh_make_invalid
static inline void sh_free_invalid(t_string* s) { free(s); }
