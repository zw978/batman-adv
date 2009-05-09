/*
 * Copyright (C) 2007-2008 B.A.T.M.A.N. contributors:
 * Marek Lindner, Simon Wunderlich
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */

/* Kernel Programming */
#define LINUX

#define DRIVER_AUTHOR "Marek Lindner <lindner_marek@yahoo.de>, Simon Wunderlich <siwu@hrz.tu-chemnitz.de>"
#define DRIVER_DESC   "B.A.T.M.A.N. Advanced"
#define DRIVER_DEVICE "batman-adv"

#define SOURCE_VERSION "0.2-alpha"
#define COMPAT_VERSION 7
#define DIRECTLINK 0x40
#define VIS_SERVER 0x20
#define TQ_MAX_VALUE 255
#define JITTER 20
#define TTL 50		/* Time To Live of broadcast messages */
#define MAX_ADDR 16	/* number of interfaces which can be added to batman. */


#define PURGE_TIMEOUT 200000  /* purge originators after time in ms if no valid packet comes in -> TODO: check influence on TQ_LOCAL_WINDOW_SIZE */
#define LOCAL_HNA_TIMEOUT 3600000

#define TQ_LOCAL_WINDOW_SIZE 64     /* sliding packet range of received originator messages in squence numbers (should be a multiple of our word size) */
#define TQ_GLOBAL_WINDOW_SIZE 10
#define TQ_LOCAL_BIDRECT_SEND_MINIMUM 1
#define TQ_LOCAL_BIDRECT_RECV_MINIMUM 1
#define TQ_TOTAL_BIDRECT_LIMIT 1

#define TQ_HOP_PENALTY 10

#define NUM_WORDS (TQ_LOCAL_WINDOW_SIZE / WORD_BIT_SIZE)

#define PACKBUFF_SIZE 2000
#define LOG_BUF_LEN 8192	/* has to be a power of 2 */
#define ETH_STR_LEN 20

#define MAX_AGGREGATION_BYTES 512   /* should not be bigger than 512 bytes or change the size of forw_packet->direct_link_flags */
#define MAX_AGGREGATION_MS 100

#define MODULE_INACTIVE 0
#define MODULE_ACTIVE 1
#define MODULE_WAITING 2


/*
 * Logging
 */

#define LOG_TYPE_CRIT 0		/* highest priority for fatal errors such as blocked sockets / failed packet delivery / programming errors */
#define LOG_TYPE_WARN 1		/* warnings for  small errors like wrong user input / damaged packets / etc */
#define LOG_TYPE_NOTICE 2	/* notice information for new interfaces / changed settings / new originators / etc */
#define LOG_TYPE_BATMAN 4	/* all messages related to routing / flooding / broadcasting / etc */
#define LOG_TYPE_ROUTES 8	/* route or hna added / changed / deleted */
#define LOG_TYPE_CRIT_NAME	"critical"
#define LOG_TYPE_WARN_NAME	"warnings"
#define LOG_TYPE_NOTICE_NAME	"notices"
#define LOG_TYPE_BATMAN_NAME	"batman"
#define LOG_TYPE_ROUTES_NAME	"routes"


#ifndef REVISION_VERSION
#define REVISION_VERSION "0"
#endif

#include <linux/mutex.h>	/* mutex */
#include <linux/module.h>	/* needed by all modules */
#include <linux/netdevice.h>	/* netdevice */
#include <linux/if_ether.h>	/* ethernet header */
#include <linux/poll.h>		/* poll_table */
#include <linux/kthread.h>	/* kernel threads */
#include <linux/pkt_sched.h>	/* schedule types */
#include <linux/workqueue.h>	/* workqueue */
#include <net/sock.h>		/* struct sock */
#include "types.h"

extern struct list_head if_list;
extern struct hlist_head forw_list;
extern struct hashtable_t *orig_hash;

extern spinlock_t orig_hash_lock;
extern spinlock_t forw_list_lock;

extern atomic_t originator_interval;
extern atomic_t vis_interval;
extern atomic_t aggregation_enabled;
extern int16_t num_hna;
extern int16_t num_ifs;

extern struct net_device *soft_device;

extern unsigned char broadcastAddr[];
extern char hna_local_changed;
extern char module_state;
extern struct workqueue_struct *bat_event_workqueue;





void start_purge_timer(void);
void activate_module(void);
void shutdown_module(void);
void inc_module_count(void);
void dec_module_count(void);
int addr_to_string(char *buff, uint8_t *addr);
int compare_orig(void *data1, void *data2);
int choose_orig(void *data, int32_t size);
int is_my_mac(uint8_t *addr);
int is_bcast(uint8_t *addr);
int is_mcast(uint8_t *addr);


