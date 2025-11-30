/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:50:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:50:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_replace_cstr, replace_middle_shorter_and_longer) {
  t_string* s = string_from("Hello brave new world");
  cr_assert(
      string_replace_cstr(s, 6, 5, "friend"));  // "Hello friend new world"
  cr_assert_str_eq(string_cstr(s), "Hello friend new world");
  string_free(s);
}

Test(string_replace_cstr, replace_len_exceed_end_truncates) {
  t_string* s = string_from("abcdef");
  cr_assert(
      string_replace_cstr(s, 3, 99, "XYZ"));  // replace from index 3 to end
  cr_assert_str_eq(string_cstr(s), "abcXYZ");
  string_free(s);
}

Test(string_replace, null_src_returns_false) {
  t_string* s = string_from("abc");
  cr_assert_not(string_replace(s, 1, 1, NULL));
  string_free(s);
}

Test(string_replace_string, pos_out_of_bounds_returns_false) {
  t_string* s = string_from("a");
  t_string* repl = string_from("b");
  cr_assert_not(string_replace_string(s, 2, 1, repl));
  string_free(s);
  string_free(repl);
}
