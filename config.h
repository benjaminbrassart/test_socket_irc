/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:42:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/15 22:43:25 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# undef FT_IRC_BUILD_DATE
# undef FT_IRC_VERSION

# define FT_IRC_BUILD_DATE __DATE__ " " __TIME__
# define FT_IRC_VERSION "1.0.0"

#endif
