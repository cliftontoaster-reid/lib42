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
