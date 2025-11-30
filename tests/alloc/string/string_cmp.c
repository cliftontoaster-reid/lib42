/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cmp.c                                       :+:      :+:    :+:   */
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

Test(string_cmp, lexicographic_cases) {
  t_string* a = string_from("abc");
  t_string* b = string_from("abd");
  cr_assert_lt(string_cmp(a, b), 0);
  cr_assert_gt(string_cmp(b, a), 0);
  cr_assert_eq(string_cmp(a, a), 0);
  string_free(a);
  string_free(b);
}
