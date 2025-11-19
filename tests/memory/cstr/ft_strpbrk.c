/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
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

Test(ft_strpbrk, char_found_at_start) {
  const char* s = "hello";
  const char* accept = "h";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s);
}

Test(ft_strpbrk, char_found_in_middle) {
  const char* s = "hello";
  const char* accept = "lo";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s + 2); /* first 'l' */
}

Test(ft_strpbrk, multiple_accept_chars_first_match) {
  const char* s = "hello";
  const char* accept = "aeiou";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s + 1); /* 'e' */
}

Test(ft_strpbrk, no_match) {
  const char* s = "hello";
  const char* accept = "xyz";
  char* result = ft_strpbrk(s, accept);
  cr_assert_null(result);
}

Test(ft_strpbrk, empty_accept) {
  const char* s = "hello";
  const char* accept = "";
  char* result = ft_strpbrk(s, accept);
  cr_assert_null(result);
}

Test(ft_strpbrk, empty_string) {
  const char* s = "";
  const char* accept = "abc";
  char* result = ft_strpbrk(s, accept);
  cr_assert_null(result);
}

Test(ft_strpbrk, both_empty) {
  const char* s = "";
  const char* accept = "";
  char* result = ft_strpbrk(s, accept);
  cr_assert_null(result);
}

Test(ft_strpbrk, first_char_matches) {
  const char* s = "test";
  const char* accept = "t";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s);
}

Test(ft_strpbrk, last_char_matches) {
  const char* s = "hello";
  const char* accept = "o";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s + 4);
}

Test(ft_strpbrk, comparison_with_libc) {
  const char* strings[] = {"hello world", "test", "", "abc"};
  const char* accepts[] = {"aeiou", "xyz", "st", "", "abc"};
  for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
    for (size_t j = 0; j < sizeof(accepts) / sizeof(accepts[0]); j++) {
      char* ft_result = ft_strpbrk(strings[i], accepts[j]);
      char* libc_result = strpbrk(strings[i], accepts[j]);
      cr_assert_eq(ft_result, libc_result);
    }
  }
}

Test(ft_strpbrk, special_characters) {
  const char* s = "hello\tworld";
  const char* accept = "\t\n";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s + 5);
}

Test(ft_strpbrk, returns_first_occurrence) {
  const char* s = "abcdef";
  const char* accept = "fed";
  char* result = ft_strpbrk(s, accept);
  cr_assert_eq(result, s + 3); /* 'd' comes first */
}
