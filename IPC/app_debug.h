/*
 * app_debug.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#ifndef __APP_DEBUG_H__
#define __APP_DEBUG_H__

#if APP_DEBUG_EN == 1
#define DBG(fmt, args...)   fprintf(stdout, "[APP_DBG] " fmt, ##args)
#define ERR(fmt, args...)   fprintf(stdout, "[APP_ERR] " fmt, ##args)
#elif APP_DEBUG_EN == 2
#define DBG(fmt, args...)   fprintf(stdout, "[APP_DBG] " fmt, ##args)
#define ERR(fmt, args...)   fprintf(stderr, "[APP_ERR] " fmt, ##args)
#elif APP_DEBUG_EN == 3
#define DBG(fmt, args...)   fprintf(stderr, "[APP_DBG] " fmt, ##args)
#define ERR(fmt, args...)   fprintf(stderr, "[APP_ERR] " fmt, ##args)
#else
#define DBG(fmt, args...)
#define ERR(fmt, args...)
#endif /* APP_DEBUG_EN */

#endif /* __APP_DEBUG_H__ */

