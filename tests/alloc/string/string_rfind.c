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
