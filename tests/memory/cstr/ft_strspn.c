/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
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

Test(ft_strspn, all_chars_in_accept) {
  const char* s = "abcabc";
  const char* accept = "abc";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 6);
}

Test(ft_strspn, stops_at_first_reject) {
  const char* s = "aaabbbccc";
  const char* accept = "ab";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 6); /* stops at first 'c' */
}

Test(ft_strspn, no_chars_match) {
  const char* s = "hello";
  const char* accept = "xyz";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 0);
}

Test(ft_strspn, empty_string) {
  const char* s = "";
  const char* accept = "abc";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 0);
}

Test(ft_strspn, empty_accept) {
  const char* s = "hello";
  const char* accept = "";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 0);
}

Test(ft_strspn, both_empty) {
  const char* s = "";
  const char* accept = "";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 0);
}

Test(ft_strspn, single_char_match) {
  const char* s = "aaaab";
  const char* accept = "a";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 4);
}

Test(ft_strspn, entire_string_matches) {
  const char* s = "test";
  const char* accept = "test";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 4);
}

Test(ft_strspn, comparison_with_libc) {
  const char* strings[] = {"hello", "aaabbbccc", "", "test123", "xyzabc"};
  const char* accepts[] = {"helo", "abc", "", "test", "xyz"};
  for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
    for (size_t j = 0; j < sizeof(accepts) / sizeof(accepts[0]); j++) {
      size_t ft_result = ft_strspn(strings[i], accepts[j]);
      size_t libc_result = strspn(strings[i], accepts[j]);
      cr_assert_eq(ft_result, libc_result);
    }
  }
}

Test(ft_strspn, whitespace_chars) {
  const char* s = "   \t\nhello";
  const char* accept = " \t\n";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 5);
}

Test(ft_strspn, digits) {
  const char* s = "12345abc";
  const char* accept = "0123456789";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 5);
}

Test(ft_strspn, first_char_not_in_accept) {
  const char* s = "hello";
  const char* accept = "aeiou";
  size_t result = ft_strspn(s, accept);
  cr_assert_eq(result, 0);
}
