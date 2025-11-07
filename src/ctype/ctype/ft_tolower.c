/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:48:54 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:56:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype/ctype.h"

char ft_tolower(char c) {
  unsigned char uc = (unsigned char)c;
  return (uc >= 'A' && uc <= 'Z') ? (uc + 32) : uc;
}
