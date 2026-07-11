/*
 * EM_MAX_TXD: Maximum number of Transmit Descriptors
 * Valid Range: 80-256 for 82542 and 82543-based adapters
 *              80-4096 for others
 * Default Value: 256
 *   This value is the number of transmit descriptors allocated by the driver.
 *   Increasing this value allows the driver to queue more transmits. Each
 *   descriptor is 16 bytes.
 */
#define EM_MAX_TXD                      256

/*
 * EM_MAX_RXD - Maximum number of receive Descriptors
 * Valid Range: 80-256 for 82542 and 82543-based adapters
 *              80-4096 for others
 * Default Value: 256
 *   This value is the number of receive descriptors allocated by the driver.
 *   Increasing this value allows the driver to buffer more incoming packets.
 *   Each descriptor is 16 bytes.  A receive buffer is also allocated for each
 *   descriptor. The maximum MTU size is 16110.
 *
 */
#define EM_MAX_RXD                      256

/*
 * EM_TIDV - Transmit Interrupt Delay Value 
 * Valid Range: 0-65535 (0=off)
 * Default Value: 64
 *   This value delays the generation of transmit interrupts in units of
 *   1.024 microseconds. Transmit interrupt reduction can improve CPU
 *   efficiency if properly tuned for specific network traffic. If the
 *   system is reporting dropped transmits, this value may be set too high
 *   causing the driver to run out of available transmit descriptors.
 */
#define EM_TIDV                         64

/*
 * EM_TADV - Transmit Absolute Interrupt Delay Value (Not valid for 82542/82543/82544)
 * Valid Range: 0-65535 (0=off)
 * Default Value: 64
 *   This value, in units of 1.024 microseconds, limits the delay in which a
 *   transmit interrupt is generated. Useful only if EM_TIDV is non-zero,
 *   this value ensures that an interrupt is generated after the initial
 *   packet is sent on the wire within the set amount of time.  Proper tuning,
 *   along with EM_TIDV, may improve traffic throughput in specific
 *   network conditions.
 */
#define EM_TADV                         64

/*
 * EM_RDTR - Receive Interrupt Delay Timer (Packet Timer) 
 * Valid Range: 0-65535 (0=off)
 * Default Value: 0
 *   This value delays the generation of receive interrupts in units of 1.024
 *   microseconds.  Receive interrupt reduction can improve CPU efficiency if
 *   properly tuned for specific network traffic. Increasing this value adds
 *   extra latency to frame reception and can end up decreasing the throughput
 *   of TCP traffic. If the system is reporting dropped receives, this value
 *   may be set too high, causing the driver to run out of available receive
 *   descriptors.
 *
 *   CAUTION: When setting EM_RDTR to a value other than 0, adapters
 *            may hang (stop transmitting) under certain network conditions.
 *            If this occurs a WATCHDOG message is logged in the system event log.
 *            In addition, the controller is automatically reset, restoring the
 *            network connection. To eliminate the potential for the hang
 *            ensure that EM_RDTR is set to 0.
 */
#define EM_RDTR                         0

/*
 * Receive Interrupt Absolute Delay Timer (Not valid for 82542/82543/82544)
 * Valid Range: 0-65535 (0=off)
 * Default Value: 64
 *   This value, in units of 1.024 microseconds, limits the delay in which a
 *   receive interrupt is generated. Useful only if EM_RDTR is non-zero,
 *   this value ensures that an interrupt is generated after the initial
 *   packet is received within the set amount of time.  Proper tuning,
 *   along with EM_RDTR, may improve traffic throughput in specific network
 *   conditions.
 */
#define EM_RADV                         64


/*
 * This parameter controls the maximum no of times the driver will loop
 * in the isr.
 *           Minimum Value = 1
 */
#define EM_MAX_INTR                     3

/*
 * Inform the stack about transmit checksum offload capabilities.
 */
#define EM_CHECKSUM_FEATURES            (CSUM_TCP | CSUM_UDP)

/*
 * This parameter controls the duration of transmit watchdog timer.
 */
#define EM_TX_TIMEOUT                   5    /* set to 5 seconds */

/*
 * This parameter controls when the driver calls the routine to reclaim
 * transmit descriptors.
 */
#define EM_TX_CLEANUP_THRESHOLD         EM_MAX_TXD / 8

/*
 * This parameter controls whether or not autonegotation is enabled.
 *              0 - Disable autonegotiation
 *              1 - Enable  autonegotiation
 */
#define DO_AUTO_NEG                     1

/*
 * This parameter control whether or not the driver will wait for
 * autonegotiation to complete.
 *              1 - Wait for autonegotiation to complete
 *              0 - Don't wait for autonegotiation to complete
 */
#define WAIT_FOR_AUTO_NEG_DEFAULT       0

/*
 * EM_MASTER_SLAVE is only defined to enable a workaround for a known compatibility issue
 * with 82541/82547 devices and some switches.  See the "Known Limitations" section of 
 * the README file for a complete description and a list of affected switches.
 *     
 *              0 = Hardware default
 *              1 = Master mode
 *              2 = Slave mode
 *              3 = Auto master/slave
 */ 
/* #define EM_MASTER_SLAVE	2 */
