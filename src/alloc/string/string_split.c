/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:16:14 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/19 12:30:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/string.h"
#include "42/alloc/vec.h"
#include "42/memory/cstr.h"

/**
 * @brief Split a string into a vector of substrings separated by @p sep.
 *
 * Returns a t_vec containing t_string* elements for each token. Empty
 * tokens are preserved (for consecutive separators). The caller takes
 * ownership of the returned vector and each t_string* inside it.
 *
 * @param s Source string to split. Must not be NULL.
 * @param sep Character used as the delimiter.
 * @return Pointer to a t_vec on success or NULL on allocation failure.
 * @warning This function allocates memory for the vector and each split
 *          element. The caller is responsible for freeing all elements
 *          and the vector itself to avoid memory leaks.
 */
t_vec* string_split(const t_string* s, char sep) {
  if (s == NULL) return NULL;
  t_vec* result = vec_create(sizeof(t_string*));
  if (result == NULL) return NULL;
  if (s->data == NULL || s->size == 0) {
    t_string* empty_str = string_new();
    if (empty_str == NULL) {
      vec_free(result);
      return NULL;
    }
    if (!vec_push_back(result, &empty_str)) {
      string_free(empty_str);
      vec_free(result);
      return NULL;
    }
    return result;
  }

  size_t start = 0;
  for (size_t i = 0; i < s->size; ++i) {
    if (s->data[i] == sep) {
      t_string* token;
      if (start == i) {
        token = string_new();
      } else {
        token = string_substr(s, start, i - start);
      }
      if (token == NULL) {
        while (result->size > 0) {
          t_string* t = *(t_string**)vec_get(result, result->size - 1);
          string_free(t);
          vec_pop_back(result);
        }
        vec_free(result);
        return NULL;
      }
      if (!vec_push_back(result, &token)) {
        string_free(token);
        while (result->size > 0) {
          t_string* t = *(t_string**)vec_get(result, result->size - 1);
          string_free(t);
          vec_pop_back(result);
        }
        vec_free(result);
        return NULL;
      }
      start = i + 1;
    }
  }

  t_string* last;
  if (start == s->size) {
    last = string_new();
  } else {
    last = string_substr(s, start, s->size - start);
  }
  if (last == NULL) {
    while (result->size > 0) {
      t_string* t = *(t_string**)vec_get(result, result->size - 1);
      string_free(t);
      vec_pop_back(result);
    }
    vec_free(result);
    return NULL;
  }
  if (!vec_push_back(result, &last)) {
    string_free(last);
    while (result->size > 0) {
      t_string* t = *(t_string**)vec_get(result, result->size - 1);
      string_free(t);
      vec_pop_back(result);
    }
    vec_free(result);
    return NULL;
  }

  return result;
}
