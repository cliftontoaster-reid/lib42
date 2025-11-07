/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:12:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strrchr, char_found_at_end) {
  const char* s = "hello";
  char* result = ft_strrchr(s, 'o');
  cr_assert_eq(result, s + 4);
}

Test(ft_strrchr, char_found_at_start) {
  const char* s = "hello";
  char* result = ft_strrchr(s, 'h');
  cr_assert_eq(result, s);
}

Test(ft_strrchr, last_occurrence) {
  const char* s = "hello";
  char* result = ft_strrchr(s, 'l');
  cr_assert_eq(result, s + 3); /* last 'l', not first */
}

Test(ft_strrchr, char_not_found) {
  const char* s = "hello";
  char* result = ft_strrchr(s, 'x');
  cr_assert_null(result);
}

Test(ft_strrchr, find_null_terminator) {
  const char* s = "hello";
  char* result = ft_strrchr(s, '\0');
  cr_assert_eq(result, s + 5);
}

Test(ft_strrchr, empty_string_find_null) {
  const char* s = "";
  char* result = ft_strrchr(s, '\0');
  cr_assert_eq(result, s);
}

Test(ft_strrchr, empty_string_find_char) {
  const char* s = "";
  char* result = ft_strrchr(s, 'a');
  cr_assert_null(result);
}

Test(ft_strrchr, multiple_occurrences) {
  const char* s = "abcabc";
  char* result = ft_strrchr(s, 'b');
  cr_assert_eq(result, s + 4);
}

Test(ft_strrchr, single_char_string) {
  const char* s = "a";
  char* result = ft_strrchr(s, 'a');
  cr_assert_eq(result, s);
}

Test(ft_strrchr, comparison_with_libc) {
  const char* strings[] = {"test", "hello world", "", "a", "aaaa", "find!"};
  int chars[] = {'t', 'o', 'x', 'a', '!', '\0', 'l'};
  for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
    for (size_t j = 0; j < sizeof(chars) / sizeof(chars[0]); j++) {
      char* ft_result = ft_strrchr(strings[i], chars[j]);
      char* libc_result = strrchr(strings[i], chars[j]);
      cr_assert_eq(ft_result, libc_result);
    }
  }
}

Test(ft_strrchr, special_chars) {
  const char* s = "tab\there";
  char* result = ft_strrchr(s, '\t');
  cr_assert_eq(result, s + 3);
}

Test(ft_strrchr, all_same_char) {
  const char* s = "aaaaa";
  char* result = ft_strrchr(s, 'a');
  cr_assert_eq(result, s + 4);
}
