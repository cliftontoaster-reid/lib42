/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_equals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:20:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:20:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_equals, equal_and_not_equal) {
  t_string* a = string_from("abc");
  t_string* b = string_from("abc");
  t_string* c = string_from("abcd");
  cr_assert(string_equals(a, b));
  cr_assert_not(string_equals(a, c));
  string_free(a);
  string_free(b);
  string_free(c);
}
