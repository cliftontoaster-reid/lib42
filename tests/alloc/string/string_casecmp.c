/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_casecmp.c                                   :+:      :+:    :+:   */
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

Test(string_casecmp, case_insensitive_equal) {
  t_string* a = string_from("Hello");
  t_string* b = string_from("hELLo");
  cr_assert_eq(string_casecmp(a, b), 0);
  string_free(a);
  string_free(b);
}
