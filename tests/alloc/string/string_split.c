/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:50:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:50:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "42/alloc/vec.h"
#include "support/string_helpers.h"

static char* get_token_str(t_vec* v, size_t i) {
  t_string** p = (t_string**)vec_get(v, i);
  return string_cstr(*p);
}

Test(string_split, basic_tokens) {
  t_string* s = string_from("apple,banana,cherry");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 3);
  cr_assert_str_eq(get_token_str(parts, 0), "apple");
  cr_assert_str_eq(get_token_str(parts, 1), "banana");
  cr_assert_str_eq(get_token_str(parts, 2), "cherry");
  // free
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, preserves_empty_tokens) {
  t_string* s = string_from("a,,c");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 3);
  cr_assert_str_eq(get_token_str(parts, 0), "a");
  cr_assert_null(get_token_str(parts, 1));  // empty -> cstr returns NULL
  cr_assert_str_eq(get_token_str(parts, 2), "c");
  // cleanup
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, leading_and_trailing_empty) {
  t_string* s = string_from(",a,");
  t_vec* parts = string_split(s, ',');
  cr_assert_eq(parts->size, 3);
  cr_assert_null(get_token_str(parts, 0));
  cr_assert_str_eq(get_token_str(parts, 1), "a");
  cr_assert_null(get_token_str(parts, 2));
  // cleanup
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, empty_string_returns_single_empty_token) {
  t_string* s = string_new();
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 1);
  cr_assert_null(get_token_str(parts, 0));
  // cleanup
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}
