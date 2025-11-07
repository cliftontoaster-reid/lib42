/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:31:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:55:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ctype/ctype.h"

bool ft_isalnum(char c) {
  unsigned char uc = (unsigned char)c;
  return (uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z') ||
         (uc >= '0' && uc <= '9');
}