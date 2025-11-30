/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_find.c                                      :+:      :+:    :+:   */
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

Test(string_find_cstr, finds_first_occurrence) {
  t_string* s = string_from("hello hello hello");
  cr_assert_eq(string_find_cstr(s, "hello", 0), 0);
  cr_assert_eq(string_find_cstr(s, "hello", 1), 6);
  cr_assert_eq(string_find_cstr(s, "hello", 7), 12);
  cr_assert_eq(string_find_cstr(s, "world", 0), -1);
  string_free(s);
}

Test(string_find_cstr, empty_needle_returns_start_or_minus_one) {
  t_string* s = string_from("abc");
  cr_assert_eq(string_find_cstr(s, "", 0), 0);
  cr_assert_eq(string_find_cstr(s, "", 2), 2);
  cr_assert_eq(string_find_cstr(s, "", 3), 3);
  cr_assert_eq(string_find_cstr(s, "", 4), -1);  // start > size
  string_free(s);
}

Test(string_find, null_args_returns_minus_one) {
  cr_assert_eq(string_find(NULL, "a", 0), -1);
  t_string* s = string_from("a");
  cr_assert_eq(string_find(s, NULL, 0), -1);
  string_free(s);
}

Test(string_find_string, first_occurrence_and_empty_needle) {
  t_string* s = string_from("banana");
  t_string* needle = string_from("ana");
  cr_assert_eq(string_find_string(s, needle, 0), 1);
  string_free(needle);
  cr_assert_eq(string_find_string(s, string_new(), 0), 0);
  cr_assert_eq(string_find_string(s, string_new(), 3), 3);
  string_free(s);
}

Test(string_find, dispatch_tagged_and_cstr) {
  t_string* s = string_from("hello hello hello");
  t_string* needle_s = string_from("hello");
  cr_assert_eq(string_find(s, needle_s, 0), 0);
  cr_assert_eq(string_find(s, "hello", 1), string_find_cstr(s, "hello", 1));
  cr_assert_eq(string_find(s, needle_s, 0), string_find_string(s, needle_s, 0));
  string_free(needle_s);
  string_free(s);
}

Test(string_find, overlapping_and_edge_cases) {
  t_string* s = string_from("aaaaa");
  cr_assert_eq(string_find_cstr(s, "aa", 0), 0);
  cr_assert_eq(string_find_cstr(s, "aa", 1), 1);
  cr_assert_eq(string_find_cstr(s, "aa", 4), -1);
  t_string* needle_aa = string_from("aa");
  cr_assert_eq(string_find_string(s, needle_aa, 2), 2);
  string_free(needle_aa);
  string_free(s);

  t_string* empty = string_new();
  cr_assert_eq(string_find_cstr(empty, "", 0), 0);
  cr_assert_eq(string_find_string(empty, string_new(), 0), 0);
  string_free(empty);
}

Test(string_find, null_inputs_and_too_large) {
  t_string* s = string_from("abc");
  cr_assert_eq(string_find_cstr(NULL, "a", 0), -1);
  cr_assert_eq(string_find_cstr(s, NULL, 0), -1);
  t_string* temp_empty = string_new();
  cr_assert_eq(string_find_string(NULL, temp_empty, 0), -1);
  string_free(temp_empty);
  t_string* too_large = string_from("abcd");
  cr_assert_eq(string_find_string(s, too_large, 0), -1);
  string_free(too_large);
  cr_assert_eq(string_find(s, NULL, 0), -1);
  string_free(s);
}
