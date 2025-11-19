/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/memory/cstr.h"

Test(ft_strcspn, no_chars_in_reject) {
  const char* s = "hello";
  const char* reject = "xyz";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 5);
}

Test(ft_strcspn, stops_at_first_reject_char) {
  const char* s = "hello world";
  const char* reject = " ";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 5);
}

Test(ft_strcspn, first_char_in_reject) {
  const char* s = "hello";
  const char* reject = "h";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 0);
}

Test(ft_strcspn, empty_string) {
  const char* s = "";
  const char* reject = "abc";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 0);
}

Test(ft_strcspn, empty_reject) {
  const char* s = "hello";
  const char* reject = "";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 5);
}

Test(ft_strcspn, both_empty) {
  const char* s = "";
  const char* reject = "";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 0);
}

Test(ft_strcspn, multiple_reject_chars) {
  const char* s = "abcdefgh";
  const char* reject = "xyz";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 8);
}

Test(ft_strcspn, reject_in_middle) {
  const char* s = "test123";
  const char* reject = "0123456789";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 4);
}

Test(ft_strcspn, comparison_with_libc) {
  const char* strings[] = {"hello world", "test", "", "abc123", "nodigits"};
  const char* rejects[] = {" ", "xyz", "", "0123456789", "abc"};
  for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
    for (size_t j = 0; j < sizeof(rejects) / sizeof(rejects[0]); j++) {
      size_t ft_result = ft_strcspn(strings[i], rejects[j]);
      size_t libc_result = strcspn(strings[i], rejects[j]);
      cr_assert_eq(ft_result, libc_result);
    }
  }
}

Test(ft_strcspn, special_chars) {
  const char* s = "hello\tworld";
  const char* reject = "\t\n";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 5);
}

Test(ft_strcspn, all_chars_rejected) {
  const char* s = "aaa";
  const char* reject = "a";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 0);
}

Test(ft_strcspn, last_char_rejected) {
  const char* s = "abcd!";
  const char* reject = "!";
  size_t result = ft_strcspn(s, reject);
  cr_assert_eq(result, 4);
}
