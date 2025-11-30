/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_rfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:25:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:25:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_rfind_cstr, last_occurrence_and_empty_needle) {
  t_string* s = string_from("bananana");
  cr_assert_eq(string_rfind_cstr(s, "ana"), 5);
  cr_assert_eq(string_rfind_cstr(s, ""), (ssize_t)s->size);
  string_free(s);
}

Test(string_rfind, not_found_returns_minus_one) {
  t_string* s = string_from("abcdef");
  cr_assert_eq(string_rfind_cstr(s, "z"), -1);
  string_free(s);
}

Test(string_rfind_string, last_occurrence_and_empty_needle) {
  t_string* s = string_from("bananana");
  t_string* needle = string_from("ana");
  cr_assert_eq(string_rfind_string(s, needle), 5);
  string_free(needle);
  cr_assert_eq(string_rfind_string(s, string_new()), (ssize_t)s->size);
  string_free(s);
}

Test(string_rfind, dispatch_tagged_and_cstr) {
  t_string* s = string_from("bananana");
  t_string* needle_s = string_from("ana");
  cr_assert_eq(string_rfind(s, needle_s), 5);
  cr_assert_eq(string_rfind(s, "ana"), 5);
  string_free(needle_s);
  string_free(s);
}

Test(string_rfind, overlapping_and_edge_cases) {
  t_string* s = string_from("aaaaa");
  cr_assert_eq(string_rfind_cstr(s, "aa"), 3);
  cr_assert_eq(string_rfind_string(s, string_from("aa")), 3);
  string_free(s);

  t_string* empty = string_new();
  cr_assert_eq(string_rfind_cstr(empty, ""), 0);
  cr_assert_eq(string_rfind_string(empty, string_new()), 0);
  string_free(empty);
}

Test(string_rfind, null_inputs_and_too_large) {
  t_string* s = string_from("abc");
  cr_assert_eq(string_rfind_cstr(NULL, "a"), -1);
  cr_assert_eq(string_rfind_cstr(s, NULL), -1);
  cr_assert_eq(string_rfind_string(NULL, string_new()), -1);
  cr_assert_eq(string_rfind_string(s, string_from("abcd")), -1);
  cr_assert_eq(string_rfind(s, NULL), -1);
  string_free(s);
}
