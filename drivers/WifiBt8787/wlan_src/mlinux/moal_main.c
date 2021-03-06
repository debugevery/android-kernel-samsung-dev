/** @file moal_main.c
  *
  * @brief This file contains the major functions in WLAN
  * driver. 
  *
  * Copyright (C) 2008-2010, Marvell International Ltd. 
  * 
  * This software file (the "File") is distributed by Marvell International 
  * Ltd. under the terms of the GNU General Public License Version 2, June 1991 
  * (the "License").  You may use, redistribute and/or modify this File in 
  * accordance with the terms and conditions of the License, a copy of which 
  * is available by writing to the Free Software Foundation, Inc.,
  * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA or on the
  * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
  *
  * THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE 
  * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE 
  * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about 
  * this warranty disclaimer.
  *
  */

/********************************************************
Change log:
    10/21/2008: initial version
********************************************************/

#include	"moal_main.h"
#include 	"moal_sdio.h"
#ifdef UAP_SUPPORT
#include    "moal_uap.h"
#endif
#ifdef STA_SUPPORT
#include    "moal_priv.h"
#endif

/********************************************************
		Local Variables
********************************************************/

/** Driver version */
const char driver_version[] =
    "SD8787-%s-M2614" MLAN_RELEASE_VERSION "-GPL" "-(" "FP" FPNUM ")"
#ifdef	DEBUG_LEVEL2
    "-dbg"
#endif
    " ";

/** Firmware name */
char *fw_name = NULL;

/** MAC address */
char *mac_addr = NULL;

#ifdef MFG_CMD_SUPPORT
/** Mfg mode */
int mfg_mode = 0;
#endif

/** SDIO interrupt mode (0: INT_MODE_SDIO, 1: INT_MODE_GPIO) */
int intmode = INT_MODE_SDIO;
/** GPIO interrupt pin number */
int gpiopin = 0;

/** Auto deep sleep */
int auto_ds = 0;

/** IEEE PS mode */
int ps_mode = 0;

/** Max Tx buffer size */
int max_tx_buf = 0;

#ifdef SDIO_SUSPEND_RESUME
/** PM keep power */
int pm_keep_power = 1;
#endif

#if defined(STA_SUPPORT)
/** 802.11d configuration */
int cfg_11d = 0;
#endif

/** woal_callbacks */
static mlan_callbacks woal_callbacks = {
    .moal_get_fw_data = moal_get_fw_data,
    .moal_init_fw_complete = moal_init_fw_complete,
    .moal_shutdown_fw_complete = moal_shutdown_fw_complete,
    .moal_send_packet_complete = moal_send_packet_complete,
    .moal_recv_packet = moal_recv_packet,
    .moal_recv_event = moal_recv_event,
    .moal_ioctl_complete = moal_ioctl_complete,
    .moal_alloc_mlan_buffer = moal_alloc_mlan_buffer,
    .moal_free_mlan_buffer = moal_free_mlan_buffer,
    .moal_write_reg = moal_write_reg,
    .moal_read_reg = moal_read_reg,
    .moal_udelay = moal_udelay,
    .moal_write_data_sync = moal_write_data_sync,
    .moal_read_data_sync = moal_read_data_sync,
    .moal_malloc = moal_malloc,
    .moal_mfree = moal_mfree,
    .moal_memset = moal_memset,
    .moal_memcpy = moal_memcpy,
    .moal_memmove = moal_memmove,
    .moal_memcmp = moal_memcmp,
    .moal_get_system_time = moal_get_system_time,
    .moal_init_timer = moal_init_timer,
    .moal_free_timer = moal_free_timer,
    .moal_start_timer = moal_start_timer,
    .moal_stop_timer = moal_stop_timer,
    .moal_init_lock = moal_init_lock,
    .moal_free_lock = moal_free_lock,
    .moal_spin_lock = moal_spin_lock,
    .moal_spin_unlock = moal_spin_unlock,
    .moal_print = moal_print,
    .moal_assert = moal_assert,
};

#ifdef UAP_SUPPORT
/** BSS attributes */
static mlan_bss_attr woal_bss_uap[] = {
    {MLAN_BSS_TYPE_UAP, MLAN_DATA_FRAME_TYPE_ETH_II, MTRUE, 0, 0},
};
#endif

#ifdef STA_SUPPORT
/** BSS attributes */
static mlan_bss_attr woal_bss_sta[] = {
    {MLAN_BSS_TYPE_STA, MLAN_DATA_FRAME_TYPE_ETH_II, MTRUE, 0, 0},
};
#endif

#if defined(STA_SUPPORT) && defined(UAP_SUPPORT)
/** BSS attributes */
static mlan_bss_attr woal_bss_multi[] = {
    {MLAN_BSS_TYPE_STA, MLAN_DATA_FRAME_TYPE_ETH_II, MTRUE, 0, 0},
    {MLAN_BSS_TYPE_UAP, MLAN_DATA_FRAME_TYPE_ETH_II, MTRUE, 0, 0},
};

/** Default Driver mode */
int drv_mode = DRV_MODE_UAP_STA;
#else
#ifdef STA_SUPPORT
int drv_mode = DRV_MODE_STA;
#else
int drv_mode = DRV_MODE_UAP;
#endif /* STA_SUPPORT */
#endif /* STA_SUPPORT & UAP_SUPPORT */

/** Supported drv_mode table */
static moal_drv_mode drv_mode_tbl[] = {
#ifdef STA_SUPPORT
    {
     /* drv_mode */
     .drv_mode = DRV_MODE_STA,
     /* intf number */
     .intf_num = sizeof(woal_bss_sta) / sizeof(woal_bss_sta[0]),
     /* bss_attr */
     .bss_attr = woal_bss_sta,
     /* fw name */
     .fw_name = DEFAULT_FW_NAME,
     }
    ,
#endif /* STA_SUPPORT */
#ifdef UAP_SUPPORT
    {
     /* drv_mode */
     .drv_mode = DRV_MODE_UAP,
     /* intf number */
     .intf_num = sizeof(woal_bss_uap) / sizeof(woal_bss_uap[0]),
     /* bss_attr */
     .bss_attr = woal_bss_uap,
     /* fw name */
     .fw_name = DEFAULT_AP_FW_NAME,
     }
    ,
#endif /* UAP_SUPPORT */
#if defined(STA_SUPPORT) && defined(UAP_SUPPORT)
    {
     /* drv_mode */
     .drv_mode = DRV_MODE_UAP_STA,
     /* intf number */
     .intf_num = sizeof(woal_bss_multi) / sizeof(woal_bss_multi[0]),
     /* bss_attr */
     .bss_attr = woal_bss_multi,
     /* fw name */
     .fw_name = DEFAULT_AP_STA_FW_NAME,
     }
    ,
#endif
};

/********************************************************
		Global Variables
********************************************************/

/** Semaphore for add/remove card */
struct semaphore AddRemoveCardSem;
/**
 * the maximum number of adapter supported 
 **/
#define MAX_MLAN_ADAPTER    2
/**
 * The global variable of a pointer to moal_handle
 * structure variable
 **/
moal_handle *m_handle[MAX_MLAN_ADAPTER];

#ifdef DEBUG_LEVEL1
#ifdef DEBUG_LEVEL2
#define	DEFAULT_DEBUG_MASK	(0xffffffff & ~MEVENT)
#else
#define DEFAULT_DEBUG_MASK	(MMSG | MFATAL | MERROR)
#endif /* DEBUG_LEVEL2 */
t_u32 drvdbg = DEFAULT_DEBUG_MASK;
t_u32 ifdbg = 0;
#endif /* DEBUG_LEVEL1 */

/********************************************************
		Local Functions
********************************************************/
/** 
 *  @brief This function initializes software
 *  
 *  @param handle A pointer to moal_handle structure
 *
 *  @return 	   MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
mlan_status
woal_init_sw(moal_handle * handle)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;
    unsigned int i;
    mlan_device device;
    t_void *pmlan;

    ENTER();

    /* find moal_drv_mode entry from drv_mode_tbl */
    handle->drv_mode = NULL;
    for (i = 0; i < (sizeof(drv_mode_tbl) / sizeof(drv_mode_tbl[0])); i++) {
        if (drv_mode_tbl[i].drv_mode == drv_mode) {
            handle->drv_mode = &drv_mode_tbl[i];
            break;
        }
    }

    if (!handle->drv_mode) {
        PRINTM(MERROR, "Invalid drv_mode=%d\n", drv_mode);
        LEAVE();
        return MLAN_STATUS_FAILURE;
    }

    /* Initialize moal_handle structure */
    handle->hardware_status = HardwareStatusInitializing;
    /* PnP and power profile */
    handle->surprise_removed = MFALSE;
    init_waitqueue_head(&handle->init_wait_q);

#if defined(SDIO_SUSPEND_RESUME)
    handle->is_suspended = MFALSE;
    handle->hs_activated = MFALSE;
    init_waitqueue_head(&handle->hs_activate_wait_q);
#endif

    /* Initialize measurement wait queue */
    handle->meas_wait_q_woken = MFALSE;
    init_waitqueue_head(&handle->meas_wait_q);

#ifdef REASSOCIATION
    MOAL_INIT_SEMAPHORE(&handle->reassoc_sem);

#if (WIRELESS_EXT >= 18)
    handle->reassoc_on = MFALSE;
#else
    handle->reassoc_on = MTRUE;
#endif

    /* Initialize the timer for the reassociation */
    woal_initialize_timer(&handle->reassoc_timer,
                          woal_reassoc_timer_func, handle);

    handle->is_reassoc_timer_set = MFALSE;
#endif /* REASSOCIATION */

    /* Register to MLAN */
    memset(&device, 0, sizeof(mlan_device));
    device.pmoal_handle = handle;

#ifdef MFG_CMD_SUPPORT
    device.mfg_mode = (t_u32) mfg_mode;
#endif
    device.int_mode = (t_u32) intmode;
    device.gpio_pin = (t_u32) gpiopin;
    device.auto_ds = (t_u32) auto_ds;
    device.ps_mode = (t_u32) ps_mode;
    device.max_tx_buf = (t_u32) max_tx_buf;
#if defined(STA_SUPPORT)
    device.cfg_11d = (t_u32) cfg_11d;
#endif
#ifdef SDIO_MULTI_PORT_TX_AGGR
#ifdef MMC_QUIRK_BLKSZ_FOR_BYTE_MODE
    device.mpa_tx_cfg = MLAN_INIT_PARA_ENABLED;
#else
    device.mpa_tx_cfg = MLAN_INIT_PARA_DISABLED;
#endif
#endif
#ifdef SDIO_MULTI_PORT_RX_AGGR
#ifdef MMC_QUIRK_BLKSZ_FOR_BYTE_MODE
    device.mpa_rx_cfg = MLAN_INIT_PARA_ENABLED;
#else
    device.mpa_rx_cfg = MLAN_INIT_PARA_DISABLED;
#endif
#endif

    for (i = 0; i < handle->drv_mode->intf_num; i++) {
        device.bss_attr[i].bss_type = handle->drv_mode->bss_attr[i].bss_type;
        device.bss_attr[i].frame_type =
            handle->drv_mode->bss_attr[i].frame_type;
        device.bss_attr[i].active = handle->drv_mode->bss_attr[i].active;
        device.bss_attr[i].bss_priority =
            handle->drv_mode->bss_attr[i].bss_priority;
        device.bss_attr[i].bss_num = handle->drv_mode->bss_attr[i].bss_num;
    }
    memcpy(&device.callbacks, &woal_callbacks, sizeof(mlan_callbacks));

    sdio_claim_host(((struct sdio_mmc_card *) handle->card)->func);
    if (MLAN_STATUS_SUCCESS == mlan_register(&device, &pmlan))
        handle->pmlan_adapter = pmlan;
    else
        ret = MLAN_STATUS_FAILURE;
    sdio_release_host(((struct sdio_mmc_card *) handle->card)->func);

    LEAVE();
    return ret;
}

/** 
 *  @brief This function frees the structure of moal_handle
 *    
 *  @param handle   A pointer to moal_handle structure
 *
 *  @return 	    N/A
 */
void
woal_free_moal_handle(moal_handle * handle)
{
    ENTER();
    if (!handle) {
        PRINTM(MERROR, "The handle is NULL.\n");
        LEAVE();
        return;
    }

    if ((handle->nl_sk) && ((handle->nl_sk)->sk_socket)) {
        sock_release((handle->nl_sk)->sk_socket);
        handle->nl_sk = NULL;
    }

    if (handle->pmlan_adapter)
        mlan_unregister(handle->pmlan_adapter);
    PRINTM(MINFO, "Free Adapter\n");
    if (handle->malloc_count || handle->lock_count || handle->mbufalloc_count) {
        PRINTM(MERROR,
               "mlan has memory leak: malloc_count=%lu lock_count=%lu mbufalloc_count=%lu\n",
               handle->malloc_count, handle->lock_count,
               handle->mbufalloc_count);
    }
    /* Free the moal handle itself */
    kfree(handle);
    LEAVE();
}

/** 
 *  @brief This function initializes firmware
 *  
 *  @param handle  A pointer to moal_handle structure
 *
 *  @return 	   MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
mlan_status
woal_init_fw(moal_handle * handle)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;
    int err;
    mlan_fw_image fw;
    t_u32 revision_id = 0;

    ENTER();

    memset(&fw, 0, sizeof(mlan_fw_image));

    if (!fw_name) {
/** Revision ID register */
#define REV_ID_REG      0x5c
        sdio_claim_host(((struct sdio_mmc_card *) handle->card)->func);
        woal_read_reg(handle, REV_ID_REG, &revision_id);
        sdio_release_host(((struct sdio_mmc_card *) handle->card)->func);
        /* Check revision ID */
        switch (revision_id) {
        case SD8787_W0:
        case SD8787_W1:
            handle->drv_mode->fw_name = SD8787_W1_FW_NAME;
            break;
        case SD8787_A0_A1:
            handle->drv_mode->fw_name = SD8787_AX_FW_NAME;
            break;
        default:
            break;
        }
    }
    if ((err =
         request_firmware(&handle->firmware, handle->drv_mode->fw_name,
                          handle->hotplug_device)) < 0) {
        PRINTM(MFATAL, "request_firmware() failed, error code = %#x\n", err);
        ret = MLAN_STATUS_FAILURE;
        goto done;
    }
    fw.pfw_buf = (t_u8 *) handle->firmware->data;
    fw.fw_len = handle->firmware->size;
    sdio_claim_host(((struct sdio_mmc_card *) handle->card)->func);
    ret = mlan_dnld_fw(handle->pmlan_adapter, &fw);
    sdio_release_host(((struct sdio_mmc_card *) handle->card)->func);
    if (ret == MLAN_STATUS_FAILURE)
        goto done;
    PRINTM(MMSG, "WLAN FW is active\n");

    handle->hardware_status = HardwareStatusFwReady;
    if (ret != MLAN_STATUS_SUCCESS)
        goto done;

    handle->init_wait_q_woken = MFALSE;
    sdio_claim_host(((struct sdio_mmc_card *) handle->card)->func);
    ret = mlan_init_fw(handle->pmlan_adapter);
    sdio_release_host(((struct sdio_mmc_card *) handle->card)->func);
    if (ret == MLAN_STATUS_FAILURE) {
        goto done;
    } else if (ret == MLAN_STATUS_SUCCESS) {
        handle->hardware_status = HardwareStatusReady;
        goto done;
    }
    /* Wait for mlan_init to complete */
    wait_event_interruptible(handle->init_wait_q, handle->init_wait_q_woken);
    if (handle->hardware_status != HardwareStatusReady) {
        ret = MLAN_STATUS_FAILURE;
        goto done;
    }
    ret = MLAN_STATUS_SUCCESS;

  done:
    if (handle->firmware)
        release_firmware(handle->firmware);
    if (ret != MLAN_STATUS_SUCCESS) {
        ret = MLAN_STATUS_FAILURE;
    }
    LEAVE();
    return ret;
}

/** 
 *  @brief This function will fill in the mlan_buffer
 *  
 *  @param pmbuf   A pointer to mlan_buffer
 *  @param skb     A pointer to struct sk_buff 
 *
 *  @return        N/A
 */
static void
woal_fill_mlan_buffer(mlan_buffer * pmbuf, struct sk_buff *skb)
{
    struct ethhdr *eth = NULL;
    struct timeval tstamp;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
    struct iphdr *iph;
#endif
    t_u8 tid = 0;

    ENTER();

    eth = (struct ethhdr *) skb->data;
    switch (eth->h_proto) {
    case __constant_htons(ETH_P_IP):
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
        iph = ip_hdr(skb);
        tid = IPTOS_PREC(iph->tos);
#else
        tid = IPTOS_PREC(skb->nh.iph->tos);
#endif
        PRINTM(MDATA, "packet type ETH_P_IP: %04x, tid=%#x prio=%#x\n",
               eth->h_proto, tid, skb->priority);
        break;
    case __constant_htons(ETH_P_ARP):
        PRINTM(MDATA, "ARP packet %04x\n", eth->h_proto);
    default:
        break;
    }
/** Offset for TOS field in the IP header */
#define IPTOS_OFFSET 5
    skb->priority = tid = (tid >> IPTOS_OFFSET);
    /* Record the current time the packet was queued; used to determine the
       amount of time the packet was queued in the driver before it was sent to 
       the firmware.  The delay is then sent along with the packet to the
       firmware for aggregate delay calculation for stats and MSDU lifetime
       expiry. */
    do_gettimeofday(&tstamp);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
    skb->tstamp = timeval_to_ktime(tstamp);
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,14)
    skb_set_timestamp(skb, &tstamp);
#else
    memcpy(&skb->stamp, &tstamp, sizeof(skb->stamp));
#endif
    pmbuf->pdesc = skb;
    pmbuf->pbuf = skb->head + sizeof(mlan_buffer);
    pmbuf->data_offset = skb->data - (skb->head + sizeof(mlan_buffer));
    pmbuf->data_len = skb->len;
    pmbuf->priority = skb->priority;
    pmbuf->in_ts_sec = (t_u32) tstamp.tv_sec;
    pmbuf->in_ts_usec = (t_u32) tstamp.tv_usec;

    LEAVE();
    return;
}

/** 
 *  @brief This function opens the network device
 *  
 *  @param dev     A pointer to net_device structure
 *
 *  @return        0 --success, otherwise fail
 */
static int
woal_open(struct net_device *dev)
{
    moal_private *priv = (moal_private *) netdev_priv(dev);
    t_u8 carrier_on = MFALSE;

    ENTER();

    if (!MODULE_GET) {
        LEAVE();
        return -EFAULT;
    }
#ifdef UAP_SUPPORT
    if ((GET_BSS_ROLE(priv) == MLAN_BSS_ROLE_UAP) && (priv->media_connected))
        carrier_on = MTRUE;
#endif
#ifdef STA_SUPPORT
    if ((GET_BSS_ROLE(priv) == MLAN_BSS_ROLE_STA) &&
        (priv->media_connected || priv->is_adhoc_link_sensed))
        carrier_on = MTRUE;
#endif
    if (carrier_on == MTRUE) {
        netif_carrier_on(priv->netdev);
        if (netif_queue_stopped(priv->netdev))
            netif_wake_queue(priv->netdev);
    } else
        netif_carrier_off(priv->netdev);
    woal_request_open(priv);

    LEAVE();
    return 0;
}

/** 
 *  @brief This function closes the network device
 *  
 *  @param dev     A pointer to net_device structure
 *
 *  @return        0
 */
static int
woal_close(struct net_device *dev)
{
    moal_private *priv = (moal_private *) netdev_priv(dev);

    ENTER();

    woal_request_close(priv);
    MODULE_PUT;

    LEAVE();
    return 0;
}

/** 
 *  @brief This function handles packet transmission
 *  
 *  @param skb     A pointer to sk_buff structure
 *  @param dev     A pointer to net_device structure
 *
 *  @return        0 --success, otherwise fail
 */
int
woal_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
    moal_private *priv = (moal_private *) netdev_priv(dev);
    mlan_buffer *pmbuf = NULL;
    mlan_status status;
    struct sk_buff *new_skb = NULL;

    ENTER();

    PRINTM(MDATA, "%lu BSS(%d): Data <= kernel\n", jiffies, priv->bss_index);

    if (priv->phandle->surprise_removed == MTRUE) {
        kfree(skb);
        priv->stats.tx_dropped++;
        goto done;
    }
    if (!skb->len || (skb->len > ETH_FRAME_LEN)) {
        PRINTM(MERROR, "Tx Error: Bad skb length %d : %d\n",
               skb->len, ETH_FRAME_LEN);
        kfree(skb);
        priv->stats.tx_dropped++;
        goto done;
    }
    if (skb_headroom(skb) < (MLAN_MIN_DATA_HEADER_LEN + sizeof(mlan_buffer))) {
        PRINTM(MWARN, "Tx: Insufficient skb headroom %d\n", skb_headroom(skb));
        /* Insufficient skb headroom - allocate a new skb */
        new_skb =
            skb_realloc_headroom(skb,
                                 MLAN_MIN_DATA_HEADER_LEN +
                                 sizeof(mlan_buffer));
        if (unlikely(!new_skb)) {
            PRINTM(MERROR, "Tx: Cannot allocate skb\n");
            kfree(skb);
            priv->stats.tx_dropped++;
            goto done;
        }
        kfree_skb(skb);
        skb = new_skb;
        PRINTM(MINFO, "new skb headroom %d\n", skb_headroom(skb));
    }
    pmbuf = (mlan_buffer *) skb->head;
    pmbuf->bss_num = priv->bss_index;
    woal_fill_mlan_buffer(pmbuf, skb);
    status = mlan_send_packet(priv->phandle->pmlan_adapter, pmbuf);
    switch (status) {
    case MLAN_STATUS_PENDING:
        atomic_inc(&priv->phandle->tx_pending);
        if (atomic_read(&priv->phandle->tx_pending) >= MAX_TX_PENDING) {
            netif_stop_queue(priv->netdev);
            dev->trans_start = jiffies;
        }
        queue_work(priv->phandle->workqueue, &priv->phandle->main_work);
        break;
    case MLAN_STATUS_SUCCESS:
        priv->stats.tx_packets++;
        priv->stats.tx_bytes += skb->len;
        dev_kfree_skb_any(skb);
        break;
    case MLAN_STATUS_FAILURE:
    default:
        priv->stats.tx_dropped++;
        dev_kfree_skb_any(skb);
        break;
    }
  done:
    LEAVE();
    return 0;
}

/** 
 *  @brief This function sets the MAC address to firmware.
 *  
 *  @param dev     A pointer to mlan_private structure
 *  @param addr    MAC address to set
 *
 *  @return        0 --success, otherwise fail
 */
static int
woal_set_mac_address(struct net_device *dev, void *addr)
{
    int ret = 0;
    moal_private *priv = (moal_private *) netdev_priv(dev);
    struct sockaddr *phw_addr = (struct sockaddr *) addr;

    ENTER();

    memset(priv->current_addr, 0, ETH_ALEN);
    /* dev->dev_addr is 6 bytes */
    HEXDUMP("dev->dev_addr:", dev->dev_addr, ETH_ALEN);

    HEXDUMP("addr:", (t_u8 *) phw_addr->sa_data, ETH_ALEN);
    memcpy(priv->current_addr, phw_addr->sa_data, ETH_ALEN);
    if (MLAN_STATUS_SUCCESS != woal_request_set_mac_address(priv)) {
        PRINTM(MERROR, "Set MAC address failed\n");
        ret = -EFAULT;
        goto done;
    }
    HEXDUMP("priv->MacAddr:", priv->current_addr, ETH_ALEN);
    memcpy(dev->dev_addr, priv->current_addr, ETH_ALEN);
  done:
    LEAVE();
    return ret;
}

#ifdef STA_SUPPORT
/** 
 *  @brief This function sets multicast addresses to firmware
 *  
 *  @param dev     A pointer to net_device structure
 *
 *  @return        N/A
 */
static void
woal_set_multicast_list(struct net_device *dev)
{
    moal_private *priv = (moal_private *) netdev_priv(dev);
    ENTER();
    woal_request_set_multicast_list(priv, dev);
    LEAVE();
}
#endif

/** 
 *  @brief This function handles the timeout of packet
 *  		transmission
 *  
 *  @param dev     A pointer to net_device structure
 *
 *  @return        N/A
 */
static void
woal_tx_timeout(struct net_device *dev)
{
    moal_private *priv = (moal_private *) netdev_priv(dev);
    ENTER();
    PRINTM(MERROR, "%lu : Tx timeout, bss_index=%d\n", jiffies,
           priv->bss_index);
    dev->trans_start = jiffies;
    priv->num_tx_timeout++;
    LEAVE();
}

/** 
 *  @brief This function returns the network statistics
 *  
 *  @param dev     A pointer to net_device structure
 *
 *  @return        A pointer to net_device_stats structure
 */
static struct net_device_stats *
woal_get_stats(struct net_device *dev)
{
    moal_private *priv = (moal_private *) netdev_priv(dev);
    return &priv->stats;
}

#ifdef STA_SUPPORT
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
/** Network device handlers */
static const struct net_device_ops woal_netdev_ops = {
    .ndo_open = woal_open,
    .ndo_start_xmit = woal_hard_start_xmit,
    .ndo_stop = woal_close,
    .ndo_do_ioctl = woal_do_ioctl,
    .ndo_set_mac_address = woal_set_mac_address,
    .ndo_tx_timeout = woal_tx_timeout,
    .ndo_get_stats = woal_get_stats,
    .ndo_set_multicast_list = woal_set_multicast_list,
};
#endif

/**
 *  @brief This function initializes the private structure 
 *  		and dev structure for station mode
 *  
 *  @param dev     A pointer to net_device structure
 *  @param priv    A pointer to moal_private structure
 *
 *  @return 	   MLAN_STATUS_SUCCESS 
 */
mlan_status
woal_init_sta_dev(struct net_device *dev, moal_private * priv)
{
    ENTER();

    /* Setup the OS Interface to our functions */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
    dev->open = woal_open;
    dev->hard_start_xmit = woal_hard_start_xmit;
    dev->stop = woal_close;
    dev->do_ioctl = woal_do_ioctl;
    dev->set_mac_address = woal_set_mac_address;
    dev->tx_timeout = woal_tx_timeout;
    dev->get_stats = woal_get_stats;
    dev->set_multicast_list = woal_set_multicast_list;
#else
    dev->netdev_ops = &woal_netdev_ops;
#endif
    dev->watchdog_timeo = MRVDRV_DEFAULT_WATCHDOG_TIMEOUT;
    dev->hard_header_len += MLAN_MIN_DATA_HEADER_LEN + sizeof(mlan_buffer);
#ifdef  WIRELESS_EXT
#if WIRELESS_EXT < 21
    dev->get_wireless_stats = woal_get_wireless_stats;
#endif
    dev->wireless_handlers = (struct iw_handler_def *) &woal_handler_def;
#endif
/** Netif dynamic alloc */
#define NETIF_F_DYNALLOC 16
    dev->features |= NETIF_F_DYNALLOC;
    dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
    netif_carrier_off(dev);
    netif_stop_queue(dev);

    /* Initialize private structure */
    init_waitqueue_head(&priv->ioctl_wait_q);
    init_waitqueue_head(&priv->cmd_wait_q);
    init_waitqueue_head(&priv->proc_wait_q);
    init_waitqueue_head(&priv->w_stats_wait_q);
    priv->current_key_index = 0;
    priv->rate_index = AUTO_RATE;
    priv->media_connected = MFALSE;
    priv->is_adhoc_link_sensed = MFALSE;
    memset(&priv->current_addr, 0, sizeof(priv->current_addr));
    memset(&priv->nick_name, 0, sizeof(priv->nick_name));
    priv->num_tx_timeout = 0;
    woal_request_get_fw_info(priv, MOAL_CMD_WAIT);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}
#endif /* STA_SUPPORT */

#ifdef UAP_SUPPORT
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
/** Network device handlers */
static const struct net_device_ops woal_uap_netdev_ops = {
    .ndo_open = woal_open,
    .ndo_start_xmit = woal_hard_start_xmit,
    .ndo_stop = woal_close,
    .ndo_do_ioctl = woal_uap_do_ioctl,
    .ndo_set_mac_address = woal_set_mac_address,
    .ndo_tx_timeout = woal_tx_timeout,
    .ndo_get_stats = woal_get_stats,
    .ndo_set_multicast_list = woal_uap_set_multicast_list,
};
#endif

/**
 *  @brief This function initializes the private structure 
 *  		and dev structure for uap mode
 *  
 *  @param dev     A pointer to net_device structure
 *  @param priv    A pointer to moal_private structure
 *
 *  @return 	   MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
mlan_status
woal_init_uap_dev(struct net_device *dev, moal_private * priv)
{
    mlan_status status = MLAN_STATUS_SUCCESS;

    ENTER();

    /* Setup the OS Interface to our functions */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
    dev->open = woal_open;
    dev->hard_start_xmit = woal_hard_start_xmit;
    dev->stop = woal_close;
    dev->set_mac_address = woal_set_mac_address;
    dev->tx_timeout = woal_tx_timeout;
    dev->get_stats = woal_get_stats;
    dev->do_ioctl = woal_uap_do_ioctl;
    dev->set_multicast_list = woal_uap_set_multicast_list;
#else
    dev->netdev_ops = &woal_uap_netdev_ops;
#endif
    dev->watchdog_timeo = MRVDRV_DEFAULT_WATCHDOG_TIMEOUT;
    dev->hard_header_len += MLAN_MIN_DATA_HEADER_LEN + sizeof(mlan_buffer);
#ifdef  WIRELESS_EXT
#if WIRELESS_EXT < 21
    dev->get_wireless_stats = woal_get_uap_wireless_stats;
#endif
    dev->wireless_handlers = (struct iw_handler_def *) &woal_uap_handler_def;
#endif /* WIRELESS_EXT */
/** Netif dynamic alloc */
#define NETIF_F_DYNALLOC 16
    dev->features |= NETIF_F_DYNALLOC;
    dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
    netif_carrier_off(dev);
    netif_stop_queue(dev);

    /* Initialize private structure */
    init_waitqueue_head(&priv->ioctl_wait_q);
    init_waitqueue_head(&priv->cmd_wait_q);
    init_waitqueue_head(&priv->proc_wait_q);
    priv->media_connected = MFALSE;
    memset(&priv->current_addr, 0, sizeof(priv->current_addr));
    woal_request_get_fw_info(priv, MOAL_CMD_WAIT);

    LEAVE();
    return status;
}
#endif /* UAP_SUPPORT */

/**
 * @brief This function adds a new interface. It will
 * 		allocate, initialize and register the device.
 *  
 *  @param handle    A pointer to moal_handle structure
 *  @param bss_num   BSS number (0-7)
 *  @param bss_type  BSS type
 *
 *  @return          A pointer to the new priv structure
 */
moal_private *
woal_add_interface(moal_handle * handle, t_u8 bss_num, t_u8 bss_type)
{
    struct net_device *dev = NULL;
    moal_private *priv = NULL;

    ENTER();

    /* Allocate an Ethernet device */
    if (!(dev = alloc_etherdev(sizeof(moal_private)))) {
        PRINTM(MFATAL, "Init virtual ethernet device failed!\n");
        goto error;
    }
#ifdef STA_SUPPORT
    /* Allocate device name */
    if ((bss_type == MLAN_BSS_TYPE_STA) && (dev_alloc_name(dev, "mlan%d") < 0)) {
        PRINTM(MERROR, "Could not allocate device name!\n");
        goto error;
    }
#endif
#ifdef UAP_SUPPORT
    if ((bss_type == MLAN_BSS_TYPE_UAP) && (dev_alloc_name(dev, "uap%d") < 0)) {
        PRINTM(MERROR, "Could not allocate device name!\n");
        goto error;
    }
#endif
    priv = (moal_private *) netdev_priv(dev);
    /* Save the priv to handle */
    bss_num &= BSS_NUM_MASK;
    handle->priv[bss_num] = priv;

    /* Use the same handle structure */
    priv->phandle = handle;
    priv->netdev = dev;
    priv->bss_index = bss_num;
    priv->bss_type = bss_type;
    if (bss_type == MLAN_BSS_TYPE_STA)
        priv->bss_role = MLAN_BSS_ROLE_STA;
    else if (bss_type == MLAN_BSS_TYPE_UAP)
        priv->bss_role = MLAN_BSS_ROLE_UAP;

#ifdef STA_SUPPORT
    MOAL_INIT_SEMAPHORE(&priv->async_sem);
    priv->scan_pending_on_block = MFALSE;
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
    SET_MODULE_OWNER(dev);
#endif
#ifdef STA_SUPPORT
    if (bss_type == MLAN_BSS_TYPE_STA)
        woal_init_sta_dev(dev, priv);
#endif
#ifdef UAP_SUPPORT
    if (bss_type == MLAN_BSS_TYPE_UAP) {
        if (MLAN_STATUS_SUCCESS != woal_init_uap_dev(dev, priv))
            goto error;
    }
#endif

    /* Register network device */
    if (register_netdev(dev)) {
        PRINTM(MERROR, "Cannot register virtual network device!\n");
        goto error;
    }

    PRINTM(MINFO, "%s: Marvell 802.11 Adapter\n", dev->name);

    /* Set MAC address from the insmod command line */
    if (handle->set_mac_addr) {
        memset(priv->current_addr, 0, ETH_ALEN);
        memcpy(priv->current_addr, handle->mac_addr, ETH_ALEN);
        if (MLAN_STATUS_SUCCESS != woal_request_set_mac_address(priv)) {
            PRINTM(MERROR, "Set MAC address failed\n");
            goto error;
        }
        memcpy(dev->dev_addr, priv->current_addr, ETH_ALEN);
    }
#ifdef CONFIG_PROC_FS
    woal_create_proc_entry(priv);
#ifdef PROC_DEBUG
    woal_debug_entry(priv);
#endif /* PROC_DEBUG */
#endif /* CONFIG_PROC_FS */

    LEAVE();
    return priv;
  error:
    if (dev)
        free_netdev(dev);
    LEAVE();
    return NULL;
}

/** 
 *  @brief This function removes an interface.
 *  
 *  @param handle   A pointer to the moal_handle structure
 *  @param bss_num  BSS number
 *
 *  @return        N/A
 */
void
woal_remove_interface(moal_handle * handle, t_u8 bss_num)
{
    struct net_device *dev = NULL;
    moal_private *priv = handle->priv[bss_num];
    union iwreq_data wrqu;

    ENTER();
    if (!priv)
        goto error;
    dev = priv->netdev;

    if (priv->media_connected == MTRUE) {
        priv->media_connected = MFALSE;
        if (GET_BSS_ROLE(priv) == MLAN_BSS_ROLE_STA) {
            memset(wrqu.ap_addr.sa_data, 0x00, ETH_ALEN);
            wrqu.ap_addr.sa_family = ARPHRD_ETHER;
            wireless_send_event(priv->netdev, SIOCGIWAP, &wrqu, NULL);
        }
    }
#ifdef CONFIG_PROC_FS
#ifdef PROC_DEBUG
    /* Remove proc debug */
    woal_debug_remove(priv);
#endif /* PROC_DEBUG */
    woal_proc_remove(priv);
#endif /* CONFIG_PROC_FS */
    /* Last reference is our one */
    PRINTM(MINFO, "refcnt = %d\n", atomic_read(&dev->refcnt));

    PRINTM(MINFO, "netdev_finish_unregister: %s%s\n", dev->name,
           (dev->features & NETIF_F_DYNALLOC) ? "" : ", old style");

    if (dev->reg_state == NETREG_REGISTERED)
        unregister_netdev(dev);

    /* Clear the priv in handle */
    priv->phandle->priv[priv->bss_index] = NULL;
    priv->phandle = NULL;
    priv->netdev = NULL;
    free_netdev(dev);
  error:
    LEAVE();
    return;
}

/** 
 *  @brief Send FW shutdown command to MLAN
 *   
 *  @param priv          A pointer to moal_private structure
 *  @param wait_option   Wait option
 *
 *  @return              MLAN_STATUS_SUCCESS -- success, otherwise fail
 */
mlan_status
woal_shutdown_fw(moal_private * priv, t_u8 wait_option)
{
    mlan_ioctl_req *req = NULL;
    mlan_ds_misc_cfg *misc = NULL;
    mlan_status status;

    ENTER();

    /* Allocate an IOCTL request buffer */
    req =
        (mlan_ioctl_req *) woal_alloc_mlan_ioctl_req(sizeof(mlan_ds_misc_cfg));
    if (req == NULL) {
        status = MLAN_STATUS_FAILURE;
        goto done;
    }

    /* Fill request buffer */
    misc = (mlan_ds_misc_cfg *) req->pbuf;
    misc->sub_command = MLAN_OID_MISC_INIT_SHUTDOWN;
    misc->param.func_init_shutdown = MLAN_FUNC_SHUTDOWN;
    req->req_id = MLAN_IOCTL_MISC_CFG;
    req->action = MLAN_ACT_SET;

    /* Send IOCTL request to MLAN */
    status = woal_request_ioctl(priv, req, wait_option);

  done:
    if (req)
        kfree(req);
    LEAVE();
    return status;
}

/********************************************************
		Global Functions
********************************************************/
/** 
 *  @brief Convert ascii string to Hex integer
 *     
 *  @param d                    A pointer to integer buf
 *  @param s			A pointer to ascii string 
 *  @param dlen			The length o fascii string
 *
 *  @return 	   	        Number of integer  
 */
int
woal_ascii2hex(t_u8 * d, char *s, t_u32 dlen)
{
    unsigned int i;
    t_u8 n;

    ENTER();

    memset(d, 0x00, dlen);

    for (i = 0; i < dlen * 2; i++) {
        if ((s[i] >= 48) && (s[i] <= 57))
            n = s[i] - 48;
        else if ((s[i] >= 65) && (s[i] <= 70))
            n = s[i] - 55;
        else if ((s[i] >= 97) && (s[i] <= 102))
            n = s[i] - 87;
        else
            break;
        if (!(i % 2))
            n = n * 16;
        d[i / 2] += n;
    }

    LEAVE();
    return i;
}

/** 
 *  @brief Return hex value of a give character
 *
 *  @param chr	    Character to be converted
 *
 *  @return 	    The converted character if chr is a valid hex, else 0
 */
int
woal_hexval(char chr)
{
    ENTER();

    if (chr >= '0' && chr <= '9')
        return chr - '0';
    if (chr >= 'A' && chr <= 'F')
        return chr - 'A' + 10;
    if (chr >= 'a' && chr <= 'f')
        return chr - 'a' + 10;

    LEAVE();
    return 0;
}

/**
 *  @brief Return hex value of a given ascii string
 *
 *  @param a	    String to be converted to ascii
 *
 *  @return 	    The converted character if a is a valid hex, else 0
 */
int
woal_atox(char *a)
{
    int i = 0;

    ENTER();

    while (isxdigit(*a))
        i = i * 16 + woal_hexval(*a++);

    LEAVE();
    return i;
}

/** 
 *  @brief Extension of strsep lib command. This function will also take care
 *	   escape character
 *
 *  @param s         A pointer to array of chars to process
 *  @param delim     The delimiter character to end the string
 *  @param esc       The escape character to ignore for delimiter
 *
 *  @return          Pointer to the separated string if delim found, else NULL
 */
char *
woal_strsep(char **s, char delim, char esc)
{
    char *se = *s, *sb;

    ENTER();

    if (!(*s) || (*se == '\0')) {
        LEAVE();
        return NULL;
    }

    for (sb = *s; *sb != '\0'; ++sb) {
        if (*sb == esc && *(sb + 1) == esc) {
            /* 
             * We get a esc + esc seq then keep the one esc
             * and chop off the other esc character
             */
            memmove(sb, sb + 1, strlen(sb));
            continue;
        }
        if (*sb == esc && *(sb + 1) == delim) {
            /* 
             * We get a delim + esc seq then keep the delim
             * and chop off the esc character
             */
            memmove(sb, sb + 1, strlen(sb));
            continue;
        }
        if (*sb == delim)
            break;
    }

    if (*sb == '\0')
        sb = NULL;
    else
        *sb++ = '\0';

    *s = sb;

    LEAVE();
    return se;
}

/**
 *  @brief Convert mac address from string to t_u8 buffer.
 *
 *  @param mac_addr The buffer to store the mac address in.	    
 *  @param buf      The source of mac address which is a string.	    
 *
 *  @return 	    N/A
 */
void
woal_mac2u8(t_u8 * mac_addr, char *buf)
{
    char *begin = buf, *end;
    int i;

    ENTER();

    for (i = 0; i < ETH_ALEN; ++i) {
        end = woal_strsep(&begin, ':', '/');
        if (end)
            mac_addr[i] = woal_atox(end);
    }

    LEAVE();
}

/**
 *  @brief This function initializes the private structure
 *  		and set default value to the member of moal_private.
 *  
 *  @param priv             A pointer to moal_private structure
 *  @param wait_option      Wait option  
 *
 *  @return 	   N/A
 */
void
woal_init_priv(moal_private * priv, t_u8 wait_option)
{
    ENTER();
#ifdef STA_SUPPORT
    if (GET_BSS_ROLE(priv) == MLAN_BSS_ROLE_STA) {
        priv->current_key_index = 0;
        priv->rate_index = AUTO_RATE;
        priv->is_adhoc_link_sensed = MFALSE;
        memset(&priv->nick_name, 0, sizeof(priv->nick_name));
        priv->num_tx_timeout = 0;
    }
#endif
#ifdef UAP_SUPPORT
    if (GET_BSS_ROLE(priv) == MLAN_BSS_ROLE_UAP) {
        priv->bss_started = MFALSE;
    }
#endif
    priv->media_connected = MFALSE;
    woal_request_get_fw_info(priv, wait_option);
    LEAVE();
    return;
}

/** 
 *  @brief This function return the point to structure moal_private 
 *  
 *  @param handle   Pointer to structure moal_handle
 *  @param bss_num  BSS number
 *
 *  @return         moal_private pointer or NULL
 */
moal_private *
woal_bss_num_to_priv(moal_handle * handle, t_u8 bss_num)
{
    ENTER();
    if (!handle || (bss_num >= MLAN_MAX_BSS_NUM)) {
        LEAVE();
        return NULL;
    }
    LEAVE();
    return handle->priv[bss_num];
}

/** 
 *  @brief This function alloc mlan_buffer.
 *  @param handle  A pointer to moal_handle structure 
 *  @param size	   buffer size to allocate
 *
 *  @return        mlan_buffer pointer or NULL
 */
pmlan_buffer
woal_alloc_mlan_buffer(moal_handle * handle, int size)
{
    mlan_buffer *pmbuf = NULL;
    struct sk_buff *skb;

    ENTER();
    if (!(pmbuf = kzalloc(sizeof(mlan_buffer), GFP_ATOMIC))) {
        PRINTM(MERROR, "%s: Fail to alloc mlan buffer", __FUNCTION__);
        return NULL;
    }
    if (!(skb = dev_alloc_skb(size))) {
        kfree(pmbuf);
        return NULL;
    }
    pmbuf->pdesc = (t_void *) skb;
    pmbuf->pbuf = (t_u8 *) skb->tail;
    handle->mbufalloc_count++;
    LEAVE();
    return pmbuf;
}

/** 
 *  @brief This function alloc mlan_ioctl_req.
 *
 *  @param size	   buffer size to allocate
 *
 *  @return        mlan_ioctl_req pointer or NULL
 */
pmlan_ioctl_req
woal_alloc_mlan_ioctl_req(int size)
{
    mlan_ioctl_req *req = NULL;

    ENTER();

    if (!
        (req =
         (mlan_ioctl_req *)
         kzalloc((sizeof(mlan_ioctl_req) + size + sizeof(int) +
                  sizeof(wait_queue)), GFP_ATOMIC))) {
        PRINTM(MERROR, "%s: Fail to alloc ioctl buffer", __FUNCTION__);
        LEAVE();
        return NULL;
    }
    req->pbuf = (t_u8 *) req + sizeof(mlan_ioctl_req);
    req->buf_len = (t_u32) size;
    req->reserved_1 =
        ALIGN_ADDR((t_u8 *) req + sizeof(mlan_ioctl_req) + size, sizeof(int));

    LEAVE();
    return req;
}

/** 
 *  @brief This function frees mlan_buffer.
 *  @param handle  A pointer to moal_handle structure 
 *  @param pmbuf   Pointer to mlan_buffer
 *
 *  @return        N/A
 */
void
woal_free_mlan_buffer(moal_handle * handle, pmlan_buffer pmbuf)
{
    ENTER();
    if (!pmbuf)
        return;
    if (pmbuf->pdesc)
        dev_kfree_skb_any((struct sk_buff *) pmbuf->pdesc);
    kfree(pmbuf);
    handle->mbufalloc_count--;
    LEAVE();
    return;
}

/** 
 *  @brief This function handles events generated by firmware
 *  
 *  @param priv    A pointer to moal_private structure
 *  @param payload A pointer to payload buffer
 *  @param len	   Length of the payload
 *  @return 	   MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
mlan_status
woal_broadcast_event(moal_private * priv, t_u8 * payload, t_u32 len)
{
    mlan_status ret = MLAN_STATUS_SUCCESS;
    struct sk_buff *skb = NULL;
    struct nlmsghdr *nlh = NULL;
    moal_handle *handle = priv->phandle;
    struct sock *sk = handle->nl_sk;

    ENTER();
    if (len > NL_MAX_PAYLOAD) {
        PRINTM(MERROR, "event size is too big!!! len=%d\n", (int) len);
        ret = MLAN_STATUS_FAILURE;
        goto done;
    }
    if (sk) {
        /* Allocate skb */
        if (!(skb = alloc_skb(NLMSG_SPACE(NL_MAX_PAYLOAD), GFP_ATOMIC))) {
            PRINTM(MERROR, "Could not allocate skb for netlink.\n");
            ret = MLAN_STATUS_FAILURE;
            goto done;
        }
        nlh = (struct nlmsghdr *) skb->data;
        nlh->nlmsg_len = NLMSG_SPACE(len);

        /* From kernel */
        nlh->nlmsg_pid = 0;
        nlh->nlmsg_flags = 0;

        /* Data */
        skb_put(skb, nlh->nlmsg_len);
        memcpy(NLMSG_DATA(nlh), payload, len);

        /* From Kernel */
        NETLINK_CB(skb).pid = 0;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20)
        /* Multicast message */
        NETLINK_CB(skb).dst_pid = 0;
#endif

        /* Multicast group number */
        NETLINK_CB(skb).dst_group = NL_MULTICAST_GROUP;

        /* Send message */
        netlink_broadcast(sk, skb, 0, NL_MULTICAST_GROUP, GFP_ATOMIC);

        ret = MLAN_STATUS_SUCCESS;
    } else {
        PRINTM(MERROR, "Could not send event through NETLINK. Link down.\n");
        ret = MLAN_STATUS_FAILURE;
    }
  done:
    LEAVE();
    return ret;
}

#ifdef REASSOCIATION
/**
 *  @brief This function handles re-association. it is triggered
 *  by re-assoc timer.
 *
 *  @param data    A pointer to wlan_thread structure
 *  @return        MLAN_STATUS_SUCCESS
 */
int
woal_reassociation_thread(void *data)
{
    moal_thread *pmoal_thread = data;
    moal_private *priv = NULL;
    moal_handle *handle = (moal_handle *) pmoal_thread->handle;
    wait_queue_t wait;
    int i;
    BOOLEAN reassoc_timer_req;
    mlan_802_11_ssid req_ssid;
    mlan_ssid_bssid ssid_bssid;
    mlan_status status;
    mlan_bss_info bss_info;

    ENTER();

    woal_activate_thread(pmoal_thread);
    init_waitqueue_entry(&wait, current);

    current->flags |= PF_NOFREEZE;

    for (;;) {
        add_wait_queue(&pmoal_thread->wait_q, &wait);
        set_current_state(TASK_INTERRUPTIBLE);

        schedule();

        set_current_state(TASK_RUNNING);
        remove_wait_queue(&pmoal_thread->wait_q, &wait);

        /* Cancel re-association timer */
        if (handle->is_reassoc_timer_set == MTRUE) {
            woal_cancel_timer(&handle->reassoc_timer);
            handle->is_reassoc_timer_set = MFALSE;
        }

        if (handle->surprise_removed)
            break;
        if (kthread_should_stop())
            break;

        if (handle->hardware_status != HardwareStatusReady) {
            PRINTM(MINFO, "Reassoc: Hardware status is not correct\n");
            continue;
        }
        PRINTM(MINFO, "Reassoc: Thread waking up...\n");
        reassoc_timer_req = MFALSE;

        for (i = 0; i < handle->priv_num && (priv = handle->priv[i]); i++) {
            if (priv->reassoc_required == MFALSE)
                continue;
            memset(&bss_info, 0, sizeof(bss_info));
            if (MLAN_STATUS_SUCCESS !=
                woal_get_bss_info(priv, MOAL_CMD_WAIT, &bss_info)) {
                PRINTM(MINFO, "Ressoc: Fail to get bss info\n");
                priv->reassoc_required = MFALSE;
                continue;
            }
            if (bss_info.bss_mode != MLAN_BSS_MODE_INFRA ||
                priv->media_connected != MFALSE) {
                PRINTM(MINFO, "Reassoc: ad-hoc mode or media connected\n");
                priv->reassoc_required = MFALSE;
                continue;
            }

            /* The semaphore is used to avoid reassociation thread and
               wlan_set_scan/wlan_set_essid interrupting each other.
               Reassociation should be disabled completely by application if
               wlan_set_user_scan_ioctl/wlan_set_wap is used. */
            if (MOAL_ACQ_SEMAPHORE_BLOCK(&handle->reassoc_sem)) {
                PRINTM(MERROR,
                       "Acquire semaphore error, reassociation thread\n");
                reassoc_timer_req = MTRUE;
                break;
            }
            PRINTM(MINFO, "Reassoc: Required ESSID: %s\n",
                   priv->prev_ssid_bssid.ssid.ssid);
            PRINTM(MINFO, "Reassoc: Performing Active Scan\n");

            memset(&req_ssid, 0, sizeof(mlan_802_11_ssid));
            memcpy(&req_ssid,
                   &priv->prev_ssid_bssid.ssid, sizeof(mlan_802_11_ssid));

            /* Do specific SSID scanning */
            if (MLAN_STATUS_SUCCESS !=
                woal_request_scan(priv, MOAL_CMD_WAIT, &req_ssid)) {
                PRINTM(MERROR, "Reassoc: Fail to do specific scan\n");
                reassoc_timer_req = MTRUE;
                MOAL_REL_SEMAPHORE(&handle->reassoc_sem);
                break;
            }

            if (handle->surprise_removed) {
                MOAL_REL_SEMAPHORE(&handle->reassoc_sem);
                break;
            }

            /* Search AP by BSSID first */
            PRINTM(MINFO, "Reassoc: Search AP by BSSID first\n");
            memset(&ssid_bssid, 0, sizeof(mlan_ssid_bssid));
            memcpy(&ssid_bssid.bssid,
                   &priv->prev_ssid_bssid.bssid, MLAN_MAC_ADDR_LENGTH);
            status = woal_find_best_network(priv, MOAL_CMD_WAIT, &ssid_bssid);

            if (MLAN_STATUS_SUCCESS != status) {
                PRINTM(MINFO, "Reassoc: AP not found in scan list\n");
                PRINTM(MINFO, "Reassoc: Search AP by SSID\n");
                /* Search AP by SSID */
                memset(&ssid_bssid, 0, sizeof(mlan_ssid_bssid));
                memcpy(&ssid_bssid.ssid,
                       &priv->prev_ssid_bssid.ssid, sizeof(mlan_802_11_ssid));
                status = woal_find_best_network(priv,
                                                MOAL_CMD_WAIT, &ssid_bssid);
            }

            if (status == MLAN_STATUS_SUCCESS) {
                /* set the wep key */
                if (bss_info.wep_status)
                    woal_enable_wep_key(priv, MOAL_CMD_WAIT);
                /* Zero SSID implies use BSSID to connect */
                memset(&ssid_bssid.ssid, 0, sizeof(mlan_802_11_ssid));
                status = woal_bss_start(priv, MOAL_CMD_WAIT, &ssid_bssid);
            }

            if (priv->media_connected == MFALSE)
                reassoc_timer_req = MTRUE;
            else {
                mlan_ds_rate *rate = NULL;
                mlan_ioctl_req *req = NULL;

                reassoc_timer_req = MFALSE;

                if (priv->rate_index != AUTO_RATE) {
                    req = woal_alloc_mlan_ioctl_req(sizeof(mlan_ds_rate));

                    if (req == NULL) {
                        LEAVE();
                        return MLAN_STATUS_FAILURE;
                    }

                    rate = (mlan_ds_rate *) req->pbuf;
                    rate->param.rate_cfg.rate_type = MLAN_RATE_INDEX;
                    rate->sub_command = MLAN_OID_RATE_CFG;
                    req->req_id = MLAN_IOCTL_RATE;

                    req->action = MLAN_ACT_SET;

                    rate->param.rate_cfg.rate = priv->rate_index;

                    if (MLAN_STATUS_SUCCESS !=
                        woal_request_ioctl(priv, req, MOAL_CMD_WAIT)) {
                        kfree(req);
                        LEAVE();
                        return MLAN_STATUS_FAILURE;
                    }
                    if (req)
                        kfree(req);
                }
            }
            MOAL_REL_SEMAPHORE(&handle->reassoc_sem);
        }
        if (handle->surprise_removed)
            break;
        if (reassoc_timer_req == MTRUE) {
            PRINTM(MINFO,
                   "Reassoc: No AP found or assoc failed. Restarting re-assoc Timer.\n");
            handle->is_reassoc_timer_set = MTRUE;
            woal_mod_timer(&handle->reassoc_timer, MOAL_TIMER_10S);
        }
    }
    woal_deactivate_thread(pmoal_thread);

    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function triggers re-association by waking up
 *  re-assoc thread.
 *  
 *  @param context	A pointer to context
 *  @return		n/a
 */
void
woal_reassoc_timer_func(void *context)
{
    moal_handle *handle = (moal_handle *) context;

    ENTER();

    PRINTM(MINFO, "reassoc_timer fired.\n");
    handle->is_reassoc_timer_set = MFALSE;

    PRINTM(MINFO, "Waking Up the Reassoc Thread\n");
    wake_up_interruptible(&handle->reassoc_thread.wait_q);

    LEAVE();
    return;
}
#endif /* REASSOCIATION */

/**
 *  @brief This workqueue function handles main_process
 *  
 *  @param work    A pointer to work_struct
 *
 *  @return        N/A
 */
t_void
woal_main_work_queue(struct work_struct * work)
{
    moal_handle *handle = container_of(work, moal_handle, main_work);

    ENTER();

    if (handle->surprise_removed == MTRUE) {
        LEAVE();
        return;
    }
    sdio_claim_host(((struct sdio_mmc_card *) handle->card)->func);
    /* Call MLAN main process */
    mlan_main_process(handle->pmlan_adapter);
    sdio_release_host(((struct sdio_mmc_card *) handle->card)->func);

    LEAVE();
}

/**
 *  @brief This function cancel all works in the queue
 *  and destroy the main workqueue.
 *  
 *  @param handle    A pointer to moal_handle
 *
 *  @return        N/A
 */
static void
woal_terminate_workqueue(moal_handle * handle)
{
    ENTER();

    flush_workqueue(handle->workqueue);
    destroy_workqueue(handle->workqueue);
    handle->workqueue = NULL;

    LEAVE();
}

void
woal_interrupt(moal_handle * handle)
{
    ENTER();

    PRINTM(MINTR, "*\n");
    if (handle->surprise_removed == MTRUE) {
        LEAVE();
        return;
    }
    /* call mlan_interrupt to read int status */
    mlan_interrupt(handle->pmlan_adapter);
    queue_work(handle->workqueue, &handle->main_work);
    LEAVE();
}

/**
 * @brief This function adds the card. it will probe the
 * 		card, allocate the mlan_private and initialize the device. 
 *  
 *  @param card    A pointer to card
 *
 *  @return        A pointer to moal_handle structure
 */
moal_handle *
woal_add_card(void *card)
{
    moal_handle *handle = NULL;
    mlan_status status = MLAN_STATUS_SUCCESS;
    int i;
    int netlink_num = NETLINK_MARVELL;
    int index = 0;

    ENTER();

    if (down_interruptible(&AddRemoveCardSem))
        goto exit_sem_err;

    /* Allocate buffer for moal_handle */
    if (!(handle = kmalloc(sizeof(moal_handle), GFP_ATOMIC))) {
        PRINTM(MERROR, "Allocate buffer for moal_handle failed!\n");
        goto err_handle;
    }

    /* Init moal_handle */
    memset(handle, 0, sizeof(moal_handle));
    handle->card = card;
    /* Save the handle */
    for (index = 0; index < MAX_MLAN_ADAPTER; index++) {
        if (m_handle[index] == NULL)
            break;
    }
    if (index < MAX_MLAN_ADAPTER) {
        m_handle[index] = handle;
        handle->handle_idx = index;
    } else {
        PRINTM(MERROR, "Exceeded maximum cards supported!\n");
        goto err_kmalloc;
    }

    if (mac_addr) {
        t_u8 temp[20];
        t_u8 len = strlen(mac_addr) + 1;
        if (len < sizeof(temp)) {
            memcpy(temp, mac_addr, len);
            handle->set_mac_addr = 1;
            /* note: the following function overwrites the temp buffer */
            woal_mac2u8(handle->mac_addr, temp);
        }
    }

    ((struct sdio_mmc_card *) card)->handle = handle;

    /* Init SW */
    if (MLAN_STATUS_SUCCESS != woal_init_sw(handle)) {
        PRINTM(MFATAL, "Software Init Failed\n");
        goto err_kmalloc;
    }

    do {
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
        handle->nl_sk =
            netlink_kernel_create(netlink_num, NL_MULTICAST_GROUP, NULL,
                                  THIS_MODULE);
#else
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
        handle->nl_sk =
            netlink_kernel_create(netlink_num, NL_MULTICAST_GROUP, NULL, NULL,
                                  THIS_MODULE);
#else
        handle->nl_sk =
            netlink_kernel_create(&init_net, netlink_num, NL_MULTICAST_GROUP,
                                  NULL, NULL, THIS_MODULE);
#endif
#endif
        if (handle->nl_sk) {
            PRINTM(MINFO, "Netlink number = %d\n", netlink_num);
            handle->netlink_num = netlink_num;
            break;
        }
        netlink_num--;
    } while (netlink_num > 0);

    if (handle->nl_sk == NULL) {
        PRINTM(MERROR,
               "Could not initialize netlink event passing mechanism!\n");
        goto err_kmalloc;
    }

    /** Create workqueue */
    handle->workqueue = create_workqueue("MOAL_WORK_QUEUE");
    if (!handle->workqueue)
        goto err_kmalloc;

    MLAN_INIT_WORK(&handle->main_work, woal_main_work_queue);

#ifdef REASSOCIATION
    PRINTM(MINFO, "Starting re-association thread...\n");
    handle->reassoc_thread.handle = handle;
    woal_create_thread(woal_reassociation_thread,
                       &handle->reassoc_thread, "woal_reassoc_service");

    while (!handle->reassoc_thread.pid) {
        woal_sched_timeout(2);
    }
#endif /* REASSOCIATION */

    /* Register the device. Fill up the private data structure with relevant
       information from the card and request for the required IRQ. */
    if (woal_register_dev(handle) != MLAN_STATUS_SUCCESS) {
        PRINTM(MFATAL, "Failed to register wlan device!\n");
        goto err_registerdev;
    }

    /* Init FW and HW */
    if (MLAN_STATUS_SUCCESS != woal_init_fw(handle)) {
        PRINTM(MFATAL, "Firmware Init Failed\n");
        goto err_init_fw;
    }

#ifdef CONFIG_PROC_FS
    /* Initialize proc fs */
    woal_proc_init(handle);
#endif /* CONFIG_PROC_FS */
    /* Add interfaces */
    for (i = 0; i < handle->drv_mode->intf_num; i++) {
        if (!woal_add_interface
            (handle, handle->priv_num,
             handle->drv_mode->bss_attr[i].bss_type)) {
            status = MLAN_STATUS_FAILURE;
            break;
        }
        handle->priv_num++;
    }
    if (status != MLAN_STATUS_SUCCESS)
        goto err_add_intf;
    up(&AddRemoveCardSem);
    LEAVE();
    return handle;
  err_add_intf:
    for (i = 0; i < handle->priv_num; i++)
        woal_remove_interface(handle, i);
#ifdef CONFIG_PROC_FS
    woal_proc_exit(handle);
#endif
  err_init_fw:
    /* Unregister device */
    PRINTM(MINFO, "unregister device\n");
    woal_unregister_dev(handle);
  err_registerdev:
    handle->surprise_removed = MTRUE;
    woal_terminate_workqueue(handle);
#ifdef REASSOCIATION
    if (handle->reassoc_thread.pid) {
        wake_up_interruptible(&handle->reassoc_thread.wait_q);
    }
    /* waiting for main thread quit */
    while (handle->reassoc_thread.pid) {
        woal_sched_timeout(2);
    }
#endif /* REASSOCIATION */
  err_kmalloc:
    if ((handle->hardware_status == HardwareStatusFwReady) ||
        (handle->hardware_status == HardwareStatusReady)) {
        PRINTM(MINFO, "shutdown mlan\n");
        handle->init_wait_q_woken = MFALSE;
        status = mlan_shutdown_fw(handle->pmlan_adapter);
        if (status == MLAN_STATUS_PENDING)
            wait_event_interruptible(handle->init_wait_q,
                                     handle->init_wait_q_woken);
    }
    woal_free_moal_handle(handle);
    if (index < MAX_MLAN_ADAPTER) {
        m_handle[index] = NULL;
    }
    ((struct sdio_mmc_card *) card)->handle = NULL;
  err_handle:
    up(&AddRemoveCardSem);
  exit_sem_err:
    LEAVE();
    return NULL;
}

/** 
 *  @brief This function removes the card.
 *  
 *  @param card    A pointer to card
 *
 *  @return        MLAN_STATUS_SUCCESS
 */
mlan_status
woal_remove_card(void *card)
{
    moal_handle *handle = NULL;
    moal_private *priv = NULL;
    mlan_status status;
    int i;
    int index = 0;

    ENTER();

    if (down_interruptible(&AddRemoveCardSem))
        goto exit_sem_err;
    /* Find the correct handle */
    for (index = 0; index < MAX_MLAN_ADAPTER; index++) {
        if (m_handle[index] && (m_handle[index]->card == card)) {
            handle = m_handle[index];
            break;
        }
    }
    if (!handle)
        goto exit_remove;
    handle->surprise_removed = MTRUE;

    /* Stop data */
    for (i = 0; i < handle->priv_num; i++) {
        if ((priv = handle->priv[i])) {
            if (!netif_queue_stopped(priv->netdev))
                netif_stop_queue(priv->netdev);
            if (netif_carrier_ok(priv->netdev))
                netif_carrier_off(priv->netdev);
        }
    }

    if ((handle->hardware_status == HardwareStatusFwReady) ||
        (handle->hardware_status == HardwareStatusReady)) {
        /* Shutdown firmware */
        PRINTM(MIOCTL, "mlan_shutdown_fw.....\n");
        handle->init_wait_q_woken = MFALSE;

        status = mlan_shutdown_fw(handle->pmlan_adapter);
        if (status == MLAN_STATUS_PENDING)
            wait_event_interruptible(handle->init_wait_q,
                                     handle->init_wait_q_woken);
        PRINTM(MIOCTL, "mlan_shutdown_fw done!\n");
    }
    if (atomic_read(&handle->rx_pending) || atomic_read(&handle->tx_pending) ||
        atomic_read(&handle->ioctl_pending)) {
        PRINTM(MERROR, "ERR: rx_pending=%d,tx_pending=%d,ioctl_pending=%d\n",
               atomic_read(&handle->rx_pending),
               atomic_read(&handle->tx_pending),
               atomic_read(&handle->ioctl_pending));
    }

    /* Remove interface */
    for (i = 0; i < handle->priv_num; i++)
        woal_remove_interface(handle, i);

    woal_terminate_workqueue(handle);

#ifdef REASSOCIATION
    PRINTM(MINFO, "Free reassoc_timer\n");
    if (handle->is_reassoc_timer_set) {
        woal_cancel_timer(&handle->reassoc_timer);
        handle->is_reassoc_timer_set = MFALSE;
    }
    if (handle->reassoc_thread.pid)
        wake_up_interruptible(&handle->reassoc_thread.wait_q);

    /* waiting for main thread quit */
    while (handle->reassoc_thread.pid) {
        woal_sched_timeout(2);
    }
#endif /* REASSOCIATION */

#ifdef CONFIG_PROC_FS
    woal_proc_exit(handle);
#endif
    /* Unregister device */
    PRINTM(MINFO, "unregister device\n");
    woal_unregister_dev(handle);
    /* Free adapter structure */
    PRINTM(MINFO, "Free Adapter\n");
    woal_free_moal_handle(handle);

    for (index = 0; index < MAX_MLAN_ADAPTER; index++) {
        if (m_handle[index] == handle) {
            m_handle[index] = NULL;
            break;
        }
    }
  exit_remove:
    up(&AddRemoveCardSem);
  exit_sem_err:
    LEAVE();
    return MLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function switch the drv_mode
 *  
 *  @param handle    A pointer to moal_handle structure
 *  @param mode     new drv_mode to switch.
 *
 *  @return        MLAN_STATUS_SUCCESS /MLAN_STATUS_FAILURE
 */
mlan_status
woal_switch_drv_mode(moal_handle * handle, t_u32 mode)
{
    unsigned int i;
    mlan_status status = MLAN_STATUS_SUCCESS;
    ENTER();
    if (down_interruptible(&AddRemoveCardSem))
        goto exit_sem_err;
    for (i = 0; i < (sizeof(drv_mode_tbl) / sizeof(drv_mode_tbl[0])); i++) {
        if (drv_mode_tbl[i].drv_mode == mode) {
            break;
        }
    }
    if (i >= (sizeof(drv_mode_tbl) / sizeof(drv_mode_tbl[0]))) {
        PRINTM(MERROR, "Invalid drv_mode=%d\n", (int) mode);
        status = MLAN_STATUS_FAILURE;
        goto exit;
    }
    status = woal_request_soft_reset(handle);
    if (status != MLAN_STATUS_SUCCESS) {
        PRINTM(MERROR, "soft_reset fail!\n");
        goto exit;
    }
    /* Shutdown firmware */
    PRINTM(MIOCTL, "mlan_shutdown_fw.....\n");
    handle->init_wait_q_woken = MFALSE;
    status = mlan_shutdown_fw(handle->pmlan_adapter);
    if (status == MLAN_STATUS_PENDING)
        wait_event_interruptible(handle->init_wait_q,
                                 handle->init_wait_q_woken);
    PRINTM(MIOCTL, "mlan_shutdown_fw done!\n");
    if (atomic_read(&handle->rx_pending) || atomic_read(&handle->tx_pending) ||
        atomic_read(&handle->ioctl_pending)) {
        PRINTM(MERROR, "ERR: rx_pending=%d,tx_pending=%d,ioctl_pending=%d\n",
               atomic_read(&handle->rx_pending),
               atomic_read(&handle->tx_pending),
               atomic_read(&handle->ioctl_pending));
    }
    /* Remove interface */
    for (i = 0; i < handle->priv_num; i++)
        woal_remove_interface(handle, i);

    /* Unregister mlan */
    if (handle->pmlan_adapter) {
        mlan_unregister(handle->pmlan_adapter);
        if (handle->malloc_count || handle->lock_count) {
            PRINTM(MERROR,
                   "mlan has memory leak: malloc_count=%lu lock_count=%lu\n",
                   handle->malloc_count, handle->lock_count);
        }
        handle->pmlan_adapter = NULL;
    }

    handle->priv_num = 0;
    drv_mode = mode;
    /* Init SW */
    if (woal_init_sw(handle)) {
        PRINTM(MFATAL, "Software Init Failed\n");
        goto exit;
    }
    /* Init FW and HW */
    if (woal_init_fw(handle)) {
        PRINTM(MFATAL, "Firmware Init Failed\n");
        goto exit;
    }
    /* Add interfaces */
    for (i = 0; i < handle->drv_mode->intf_num; i++) {
        if (!woal_add_interface
            (handle, handle->priv_num,
             handle->drv_mode->bss_attr[i].bss_type)) {
            status = MLAN_STATUS_FAILURE;
            break;
        }
        handle->priv_num++;
    }
  exit:
    up(&AddRemoveCardSem);
  exit_sem_err:
    LEAVE();
    return status;
}

/** 
 *  @brief This function initializes module.
 *  
 *  @return        MLAN_STATUS_SUCCESS or MLAN_STATUS_FAILURE
 */
static int
woal_init_module(void)
{
    int ret = (int) MLAN_STATUS_SUCCESS;
    unsigned int i = 0;
    int index = 0;

    ENTER();

    /* Init the wlan_private pointer array first 首先初始化WLAN自身的指针数组 m_handle */
    for (index = 0; index < MAX_MLAN_ADAPTER; index++) {
        m_handle[index] = NULL;
    }
    /* Replace default fw image name for specific drv_mode 把默认的固件镜像替换为指定的 drv_mode*/
    if (fw_name) {
        for (i = 0; i < (sizeof(drv_mode_tbl) / sizeof(drv_mode_tbl[0])); i++) {
            if (drv_mode_tbl[i].drv_mode == drv_mode) {
                drv_mode_tbl[i].fw_name = fw_name;
                break;
            }
        }
    }
    /* Init mutex初始化一个信号量作为互斥信号 */
    init_MUTEX(&AddRemoveCardSem);

    /* Register with bus 把模块注册到总线上 */
    ret = woal_bus_register();

    LEAVE();
    return ret;
}

/** 
 *  @brief This function cleans module
 *  
 *  @return        N/A
 */
static void
woal_cleanup_module(void)
{
    moal_handle *handle = NULL;
    int index = 0;
    int i;

    ENTER();

    if (down_interruptible(&AddRemoveCardSem))
        goto exit_sem_err;
    for (index = 0; index < MAX_MLAN_ADAPTER; index++) {
        handle = m_handle[index];
        if (!handle)
            continue;
        if (!handle->priv_num)
            goto exit;
#ifdef SDIO_SUSPEND_RESUME
#ifdef MMC_PM_KEEP_POWER
        if (handle->is_suspended == MTRUE) {
            woal_sdio_resume(&(((struct sdio_mmc_card *) handle->card)->func)->
                             dev);
        }
#endif
#endif /* SDIO_SUSPEND_RESUME */

        for (i = 0; i < handle->priv_num; i++) {
#ifdef STA_SUPPORT
            if ((GET_BSS_ROLE(handle->priv[i]) == MLAN_BSS_ROLE_STA) &&
                (handle->priv[i]->media_connected == MTRUE)) {
                woal_disconnect(handle->priv[i], MOAL_CMD_WAIT, NULL);
            }
#endif
#ifdef UAP_SUPPORT
            if (GET_BSS_ROLE(handle->priv[i]) == MLAN_BSS_ROLE_UAP) {
#ifdef MFG_CMD_SUPPORT
                if (mfg_mode != MLAN_INIT_PARA_ENABLED)
#endif
                    woal_disconnect(handle->priv[i], MOAL_CMD_WAIT, NULL);
            }
#endif
        }

#ifdef MFG_CMD_SUPPORT
        if (mfg_mode != MLAN_INIT_PARA_ENABLED)
#endif
            woal_shutdown_fw(woal_get_priv(handle, MLAN_BSS_ROLE_ANY),
                             MOAL_CMD_WAIT);
    }
  exit:
    up(&AddRemoveCardSem);
  exit_sem_err:
    /* Unregister from bus */
    woal_bus_unregister();
    LEAVE();
}

module_init(woal_init_module);
module_exit(woal_cleanup_module);

module_param(fw_name, charp, 0);
MODULE_PARM_DESC(fw_name, "Firmware name");
module_param(mac_addr, charp, 0);
MODULE_PARM_DESC(mac_addr, "MAC address");
#ifdef MFG_CMD_SUPPORT
module_param(mfg_mode, int, 0);
MODULE_PARM_DESC(mfg_mode,//如果mfg_mode的值为0则下载普通版的firmware，如果值为1则下载MFGfirmware
                 "0: Download normal firmware; 1: Download MFG firmware");
#endif /* MFG_CMD_SUPPORT */
module_param(drv_mode, int, 0);
MODULE_PARM_DESC(drv_mode, "1: STA; 2: UAP; 3: STA+UAP");//设置模式
#ifdef DEBUG_LEVEL1
module_param(drvdbg, ulong, 0);
MODULE_PARM_DESC(drvdbg, "Driver debug");
#endif /* DEBUG_LEVEL1 */
module_param(auto_ds, int, 0);
MODULE_PARM_DESC(auto_ds,//auto_ds=0就是MLAN默认的模式，auto_ds=1可进入深度睡眠模式， auto_ds=2禁止进入深度睡眠模式
                 "0: MLAN default; 1: Enable auto deep sleep; 2: Disable auto deep sleep");
module_param(ps_mode, int, 0);
MODULE_PARM_DESC(ps_mode,//ps_mode=0为MALN的默认模式ps_mode=1打开IEEE PS ps_mode =2为关闭IEEE PS（PS 可能代表的是物理时隙）
                 "0: MLAN default; 1: Enable IEEE PS mode; 2: Disable IEEE PS mode");
module_param(max_tx_buf, int, 0);//发送最大缓冲区间大小max_tx_buf的值可以是2048或4096或8192
MODULE_PARM_DESC(max_tx_buf, "Maximum Tx buffer size (2048/4096/8192)");
#ifdef SDIO_SUSPEND_RESUME
module_param(pm_keep_power, int, 1);//电源管理pm_keep_power=1能管理，0失去管理能力
MODULE_PARM_DESC(pm_keep_power, "1: PM keep power; 0: PM no power");
#endif
#if defined(STA_SUPPORT)
module_param(cfg_11d, int, 0);
MODULE_PARM_DESC(cfg_11d,//cfg_11d=0代表MLAN默认的模式，cfg_11d=1代表打开802.11d，cfg_11d=2代表关闭802.11b
                 "0: MLAN default; 1: Enable 802.11d; 2: Disable 802.11d");
#endif
MODULE_DESCRIPTION("M-WLAN Driver");
MODULE_AUTHOR("Marvell International Ltd.");
MODULE_VERSION(MLAN_RELEASE_VERSION);
MODULE_LICENSE("GPL");
/*
module_init(woal_init_module);
	->  ret = woal_bus_register();
		-> sdio_register_driver(&wlan_sdio)) 
			-> static struct sdio_driver wlan_sdio = {
   			 .name = "wlan_sdio",
   			 .id_table = wlan_ids,
    			 .probe = woal_sdio_probe,
    			 	-> sdio_claim_host(func);
    			 	-> ret = sdio_enable_func(func);
    			 	-> sdio_release_host(func);
    			 	->  if (NULL == (handle = woal_add_card(card))) {
    			 		-> if (MLAN_STATUS_SUCCESS != woal_init_sw(handle)) {
    			 		->  MLAN_INIT_WORK(&handle->main_work, woal_main_work_queue);
    			 			-> mlan_main_process(handle->pmlan_adapter);
    			 				-> 
    			 		-> woal_create_thread(woal_reassociation_thread,
   			 .remove = woal_sdio_remove,
   			 .drv = {.pm = &wlan_sdio_pm_ops,}

  */

