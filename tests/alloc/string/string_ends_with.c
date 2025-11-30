/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ends_with.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:34:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 17:37:36 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_ends_with, suffix_cases) {
  t_string* s = string_from("document.pdf");
  cr_assert(string_ends_with(s, ".pdf"));
  cr_assert_not(string_ends_with(s, NULL));
  cr_assert(string_ends_with(s, ""));
  cr_assert_not(string_ends_with(s, ".txt"));
  string_free(s);
}
