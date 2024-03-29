/*
 * Copyright (C) 2019 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    net_gnrc_sixlowpan_frag_vrb Virtual reassembly buffer
 * @ingroup     net_gnrc_sixlowpan_frag
 * @brief       Virtual reassembly buffer
 * @{
 *
 * @file
 * @brief       Virtual reassembly buffer definitions
 * @see         https://tools.ietf.org/html/draft-ietf-lwig-6lowpan-virtual-reassembly-01
 *
 * @author      Martine Lenders <m.lenders@fu-berlin.de>
 */
#ifndef NET_GNRC_SIXLOWPAN_FRAG_VRB_H
#define NET_GNRC_SIXLOWPAN_FRAG_VRB_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "net/gnrc/netif.h"
#include "net/gnrc/sixlowpan/config.h"
#include "net/gnrc/sixlowpan/frag/rb.h"
#include "timex.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Representation of the virtual reassembly buffer entry
 */
typedef struct {
    gnrc_sixlowpan_frag_rb_base_t super;    /**< base type */

    /**
     * @brief   Link-layer destination address to which the fragments are
     *          supposed to be forwarded to
     */
    uint8_t out_dst[IEEE802154_LONG_ADDRESS_LEN];
    /**
     * @brief   Outgoing interface to gnrc_sixlowpan_frag_vrb_t::out_dst
     */
    gnrc_netif_t *out_netif;
    /**
     * @brief   Outgoing tag to gnrc_sixlowpan_frag_vrb_t::out_dst
     */
    uint16_t out_tag;
    /**
     * @brief   Length of gnrc_sixlowpan_frag_vrb_t::out_dst
     */
    uint8_t out_dst_len;
} gnrc_sixlowpan_frag_vrb_t;

/**
 * @brief   Adds a new reassembly buffer entry
 *
 * @param[in] base          Base data of the datagram. Must not be `NULL`.
 * @param[in] out_netif     Network interface that is out-going to @p out_dst.
 * @param[in] out_dst       Link-layer destination address to which to forward
 *                          fragments identified by @p base. Must not be `NULL`.
 * @param[in] out_dst_len   Length of @p out_dst. Must be greater than 0.
 *
 * @pre `base != NULL`
 * @pre `out_dst != NULL`
 * @pre `out_dst_len > 0`
 *
 * @return  A new VRB entry.
 * @return  NULL, if VRB is full.
 */
gnrc_sixlowpan_frag_vrb_t *gnrc_sixlowpan_frag_vrb_add(
        const gnrc_sixlowpan_frag_rb_base_t *base,
        gnrc_netif_t *out_netif, const uint8_t *out_dst, size_t out_dst_len);

/**
 * @brief   Checks timeouts and removes entries if necessary
 */
void gnrc_sixlowpan_frag_vrb_gc(void);

/**
 * @brief   Gets a VRB entry
 *
 * @param[in] src           Link-layer source address of the original fragment.
 * @param[in] src_len       Length of @p src.
 * @param[in] src_tag       Tag of the original fragment.
 *
 * @return  The VRB entry identified by the given parameters.
 * @return  NULL, if there is no entry in the VRB that could be identified
 *          by the given parameters.
 */
gnrc_sixlowpan_frag_vrb_t *gnrc_sixlowpan_frag_vrb_get(
        const uint8_t *src, size_t src_len, unsigned src_tag);

/**
 * @brief   Removes an entry from the VRB
 *
 * @param[in] vrb   A VRB entry
 */
static inline void gnrc_sixlowpan_frag_vrb_rm(gnrc_sixlowpan_frag_vrb_t *vrb)
{
#ifdef MODULE_GNRC_SIXLOWPAN_FRAG
    gnrc_sixlowpan_frag_rb_base_rm(&vrb->super);
#elif   defined(TEST_SUITES)
    /* for testing just zero src_len */
    vrb->super.src_len = 0;
#endif  /* MODULE_GNRC_SIXLOWPAN_FRAG */
}

/**
 * @brief   Determines if a VRB entry is empty
 *
 * @param[in] vrb   A VRB entry
 *
 * @return  true, if @p vrb entry is empty.
 * @return  false, if @p vrb entry is not empty.
 */
static inline bool gnrc_sixlowpan_frag_vrb_entry_empty(gnrc_sixlowpan_frag_vrb_t *vrb)
{
    return (vrb->super.src_len == 0);
}

#if defined(TEST_SUITES) || defined(DOXYGEN)
/**
 * @brief   Resets the VRB to a clean state
 *
 * @note    Only available when @ref TEST_SUITES is defined
 */
void gnrc_sixlowpan_frag_vrb_reset(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* NET_GNRC_SIXLOWPAN_FRAG_VRB_H */
/** @} */
