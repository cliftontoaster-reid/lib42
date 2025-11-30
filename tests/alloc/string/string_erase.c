/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_erase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:45:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:45:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_erase, erase_middle_truncates_and_shifts) {
  t_string* s = string_from("abcdefgh");
  cr_assert(string_erase(s, 2, 3));  // remove "cde"
  cr_assert_eq(s->size, 5);
  cr_assert_str_eq(string_cstr(s), "abfgh");
  string_free(s);
}

Test(string_erase, erase_to_end_when_len_exceeds) {
  t_string* s = string_from("hello");
  cr_assert(string_erase(s, 2, 99));  // removes starting at 'l'
  cr_assert_eq(s->size, 2);
  cr_assert_str_eq(string_cstr(s), "he");
  string_free(s);
}

Test(string_erase, pos_out_of_bounds_returns_false) {
  t_string* s = string_from("abc");
  cr_assert_not(string_erase(s, 3, 1));
  string_free(s);
}
