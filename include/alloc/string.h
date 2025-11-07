/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:40:30 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:51:04 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "alloc/vec.h"

typedef struct s_string {
  char* data;
  size_t size;
  size_t capacity;
} t_string;

/// @brief
/// @param cstr
/// @return
t_string* string_from(const char* cstr);

/// @brief
/// @return
t_string* string_new();

/// @brief
/// @param str
/// @param cstr
/// @return
bool string_append(t_string* str, const char* cstr);

/// @brief
/// @param str
/// @param cstr
/// @return
bool string_prepend(t_string* str, const char* cstr);

/// @brief
/// @param s
void string_free(t_string* s);

/// @brief
/// @param s
/// @return
t_string* string_clone(const t_string* s);

/// @brief
/// @param s
/// @param min_capacity
/// @return
bool string_reserve(t_string* s, size_t min_capacity);

/// @brief
/// @param s
/// @return
bool string_shrink_to_fit(t_string* s);

/// @brief
/// @param s
void string_clear(t_string* s);

/// @brief
/// @param s
/// @param new_size
/// @param fill
/// @return
bool string_resize(t_string* s, size_t new_size, char fill);

/// @brief
/// @param s
/// @param c
/// @return
bool string_push_char(t_string* s, char c);

/// @brief
/// @param s
/// @param out
/// @return
bool string_pop_char(t_string* s, char* out);

/// @brief
/// @param s
/// @param pos
/// @param cstr
/// @return
bool string_insert(t_string* s, size_t pos, const char* cstr);

/// @brief
/// @param s
/// @param pos
/// @param len
/// @return
bool string_erase(t_string* s, size_t pos, size_t len);

/// @brief
/// @param s
/// @param pos
/// @param len
/// @param cstr
/// @return
bool string_replace(t_string* s, size_t pos, size_t len, const char* cstr);

/// @brief
/// @param s
/// @param pos
/// @param len
/// @return
t_string* string_substr(const t_string* s, size_t pos, size_t len);

/// @brief
/// @param s
/// @param needle
/// @param start
/// @return
ssize_t string_find(const t_string* s, const char* needle, size_t start);

/// @brief
/// @param s
/// @param needle
/// @return
ssize_t string_rfind(const t_string* s, const char* needle);

/// @brief
/// @param s
/// @param prefix
/// @return
bool string_starts_with(const t_string* s, const char* prefix);

/// @brief
/// @param s
/// @param suffix
/// @return
bool string_ends_with(const t_string* s, const char* suffix);

/// @brief
/// @param s
/// @param chars
/// @return
t_string* string_trim(const t_string* s, const char* chars);

/// @brief
/// @param s
/// @return
char* string_cstr(t_string* s);

/// @brief
/// @param a
/// @param b
/// @return
int string_cmp(const t_string* a, const t_string* b);

/// @brief
/// @param a
/// @param b
/// @return
bool string_equals(const t_string* a, const t_string* b);

/// @brief
/// @param a
/// @param b
/// @return
bool string_casecmp(const t_string* a, const t_string* b);

/// @brief
/// @param s
/// @param fmt
/// @param ...
/// @return
bool string_format(t_string* s, const char* fmt, ...)
    __attribute__((format(printf, 2, 3)));

/// @brief
/// @param s
/// @param sep
/// @return
t_vec* string_split(const t_string* s, char sep);