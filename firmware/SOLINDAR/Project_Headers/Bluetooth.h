/**
 * @file Bluetooth.c
 * @author Anderson Contreras
 * @brief This is an API for the Bluetooth modules eb100-SER, eb500-SER, and eb501-SER to be used with
 *        the MCS09S08QE128 microcontroller.
 *        Based on the "Firmware Reference Manual (ebSerial version 2.1) March 26, 2007"
 * 
 *        This API is INCOMPLETE and does not handle the response of the module,
 *        so no error checking is performed
 * @version 0.1
 * @date 2019-10-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <string.h>
#include "PE_Types.h"
#include "PE_Error.h"

// General states
#define ON   1
#define OFF  0

// Terminal characters
#define BT_PROMPT   '>'
#define BT_ACK     "ACK"
#define BT_NAK     "NAK"
#define BT_ERR     "Err"
#define BT_CR      0x0D

// Transmit Power
#define BT_TXPOWER_1    1
#define BT_TXPOWER_2    2
#define BT_TXPOWER_3    3
#define BT_TXPOWER_4    4
#define BT_TXPOWER_5    5
#define BT_TXPOWER_6    6
#define BT_TXPOWER_7    7
#define BT_TXPOWER_8    8
#define BT_TXPOWER_9    9
#define BT_TXPOWER_10   10

// Baud rates
#define BT_1200BAUD    0
#define BT_2400BAUD    1
#define BT_4800BAUD    2
#define BT_9600BAUD    3
#define BT_19200BAUD   4
#define BT_38400BAUD   5
#define BT_57600BAUD   6
#define BT_115200BAUD  7
#define BT_230400BAUD  8
#define BT_460800BAUD  9


// Error Codes
#define E_GEN_CONN_FAIL                 1
#define E_CONN_ATTEMPT_FAIL             2
#define E_CMD_NOT_VALID_WHILE_ACTIVE    3
#define E_CMD_ONLY_VALID_WHILE_ACTIVE   4
#define E_UNEXPEC_REQUEST_OCURR         5
#define E_CONN_FAIL_TIMEOUT             6
#define E_CONN_REFUSED                  7
#define E_REMOTE_NOT_SUPPORT_SPP        8
#define E_DELETING_TRUSTED_DEVICE       9
#define E_UNABLE_ADD_TRUSTED_DEVICE     10
#define E_TRUSTED_DEVICE_NOT_FOUND      11
#define E_CMD_NOT_VALID_STARTUP         12


extern void InitBluetooth(void);
extern byte BTret(void);
extern byte BTsetName(char *, char);
extern byte BTsetPasskey(char *, char);
extern byte BTsetVisible(byte);
extern byte BTsetSecurity(byte);
extern byte BTsetConnectable(byte);
extern byte BTsetTransmitPower(byte);
extern byte BTsetBaud(byte);


#endif /* BLUETOOTH_H_ */
