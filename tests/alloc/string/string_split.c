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

Test(string_split, no_separator) {
  t_string* s = string_from("apple");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 1);
  cr_assert_str_eq(get_token_str(parts, 0), "apple");
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, only_separators) {
  t_string* s = string_from(",,,");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 4);
  for (size_t i = 0; i < parts->size; ++i) {
    cr_assert_null(get_token_str(parts, i));
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, leading_only) {
  t_string* s = string_from(",a");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 2);
  cr_assert_null(get_token_str(parts, 0));
  cr_assert_str_eq(get_token_str(parts, 1), "a");
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, trailing_only) {
  t_string* s = string_from("a,");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 2);
  cr_assert_str_eq(get_token_str(parts, 0), "a");
  cr_assert_null(get_token_str(parts, 1));
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, multi_consecutive_separators) {
  t_string* s = string_from("a,,,b");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 4);
  cr_assert_str_eq(get_token_str(parts, 0), "a");
  cr_assert_null(get_token_str(parts, 1));
  cr_assert_null(get_token_str(parts, 2));
  cr_assert_str_eq(get_token_str(parts, 3), "b");
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
  string_free(s);
}

Test(string_split, null_input_returns_null) {
  t_vec* parts = string_split(NULL, ',');
  cr_assert_null(parts);
}

Test(string_split, tokens_independent_from_source) {
  t_string* s = string_from("foo,bar");
  t_vec* parts = string_split(s, ',');
  cr_assert_not_null(parts);
  cr_assert_eq(parts->size, 2);
  string_free(s); /* free source, tokens should remain valid */
  cr_assert_str_eq(get_token_str(parts, 0), "foo");
  cr_assert_str_eq(get_token_str(parts, 1), "bar");
  for (size_t i = 0; i < parts->size; ++i) {
    t_string* t = *(t_string**)vec_get(parts, i);
    string_free(t);
  }
  vec_free(parts);
}
