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

#include "Bluetooth.h"
#include "AS1.h"

#pragma MESSAGE DISABLE C1420 /* WARNING C1420: Result of function-call is ignored */


// TODO Finish the remaining API functions
//      Add a parsing to handle the module response and perform error checking


const char BTname[] = "EC3883-G05";
const char BTpass[] = "123456";

/**
 * @brief This sets the initial configuration for the bluetooth
 * 
 */
void InitBluetooth(void){
    BTsetName(BTname, strlen(BTname));
    BTsetPasskey(BTpass, strlen(BTpass));
    BTsetBaud(BT_115200BAUD);
    AS1_SetBaudRateMode(AS1_BM_115200BAUD);
    BTret();
};

/**
 * @brief The return from soft break command instructs the device to stop accepting commands and return
 *        to passing data wirelessly when there is an active connection.
 * 
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK
 */
byte BTret(void){
    AS1_SendBlock("ret", 3, NULL);
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set name command sets the name of the local EmbeddedBue device. This is the value that
 *        is transmitted when a remote device performs an Inquiry and then requests the device name.
 *        If you look for local Bluetooth devices from a PC or PDA, this is the value that will be
 *        displayed to the user.
 * 
 * @param name A new device name. This value can be up to 32 characters in length and
 *             may contain any valid ASCII characters except for spaces (ASCII 0x20).
 * @param size Size of the string
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK
 */
byte BTsetName(char *name, char size){
    AS1_SendBlock("set name ", 9, NULL);
    AS1_SendBlock(name, size, NULL);
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set passkey command sets the passkey that is used when establishing a connection with a
 *        new device. The passkey is set to 0000 by default, but this value can be changed to enhance
 *        security. It is recommended that you use a passkey that is 8 to 16 digits long.
 * 
 * @param pass A new passkey value that is between 1 and 16 digits long
 * @param size Size of the string
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK 
 */
byte BTsetPasskey(char *pass, char size){
    AS1_SendBlock("set passkey ", 12, NULL);
    AS1_SendBlock(pass, size, NULL);
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set visible mode command provides control over whether the local EmbeddedBlue device
 *        can be seen by other Bluetooth devices. In Bluetooth terminology, this command controls the
 *        setting for inquiry scan.
 * 
 * @param state The state to be set: ON/OFF 
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK 
 *         - ERR_NOTAVAIL - Requested value or method not available
 */
byte BTsetVisible(byte state){
    AS1_SendBlock("set visible ", 12, NULL);
    switch (state){
        case ON:
            AS1_SendBlock("on", 2, NULL);
            break;
        case OFF:
            AS1_SendBlock("off", 3, NULL);
            break;
        default:
            return ERR_NOTAVAIL;
            break;
    }
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set security command sets the current security setting of the local Bluetooth device. When
 *        security is turned off, the device will allow connections to be established with any Bluetooth
 *        device. If the remote Bluetooth device provides the proper passkey, it will be added to the trusted
 *        list. When security is turned on, only devices already on the trusted list will be allowed to connect.
 * 
 * @param state The state to be set: ON/OFF 
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK 
 *         - ERR_NOTAVAIL - Requested value or method not available
 */
byte BTsetSecurity(byte state){
    AS1_SendBlock("set security ", 13, NULL);
    switch (state){
        case ON:
            AS1_SendBlock("on", 2, NULL);
            break;
        case OFF:
            AS1_SendBlock("off", 3, NULL);
            break;
        default:
            return ERR_NOTAVAIL;
            break;
    }
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set connectable command provides control over whether the local EmbeddedBlue device will
 *        accept connections from other Bluetooth devices. In Bluetooth terminology, this command
 *        controls the setting for page scan.
 * 
 * @param state The state to be set: ON/OFF
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK
 *         - ERR_NOTAVAIL - Requested value or method not available
 */
byte BTsetConnectable(byte state){
    AS1_SendBlock("set connectable ", 16, NULL);
    switch (state){
        case ON:
            AS1_SendBlock("on", 2, NULL);
            break;
        case OFF:
            AS1_SendBlock("off", 3, NULL);
            break;
        default:
            return ERR_NOTAVAIL;
            break;
    }
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set transmit power command sets the transmit power setting of the EmbeddedBlue radio.
 *        This command provides control over how much power the local EmbeddedBlue device will draw
 *        for transmitting radio frequencies. This power setting has a correlation to Bluetooth range: a
 *        lower transmit power setting will result in a shorter achievable Bluetooth range and it will
 *        also draw less power from the power source.
 * 
 * @param txpower The power setting which is an integer between 1-10.
 *                Low values equate to a lower power setting. High values equate to a higher power setting.
 *                The default value is 10 (maximum).
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK
 *         - ERR_NOTAVAIL - Requested value or method not available
 */
byte BTsetTransmitPower(byte txpower){
    AS1_SendBlock("set txpower ", 12, NULL);
    
    switch (txpower){
        case BT_TXPOWER_1:
            AS1_SendBlock("1", 1, NULL);
            break;
        case BT_TXPOWER_2:
            AS1_SendBlock("2", 1, NULL);
            break;
        case BT_TXPOWER_3:
            AS1_SendBlock("3", 1, NULL);
            break;
        case BT_TXPOWER_4:
            AS1_SendBlock("4", 1, NULL);
            break;
        case BT_TXPOWER_5:
            AS1_SendBlock("5", 1, NULL);
            break;
        case BT_TXPOWER_6:
            AS1_SendBlock("6", 1, NULL);
            break;
        case BT_TXPOWER_7:
            AS1_SendBlock("7", 1, NULL);
            break;
        case BT_TXPOWER_8:
            AS1_SendBlock("8", 1, NULL);
            break;
        case BT_TXPOWER_9:
            AS1_SendBlock("9", 1, NULL);
            break;
        case BT_TXPOWER_10:
            AS1_SendBlock("10", 2, NULL);
            break;
        default:
            return ERR_NOTAVAIL;
            break;
    }
    AS1_SendChar(BT_CR);
    return ERR_OK;
};

/**
 * @brief The set baud rate command sets the baud rate for communications with the local
 *        EmbeddedBluedevice.
 * @param rate The new baud rate
 * @return byte Return value: Error code, posible codes:
 *         - ERR_OK - OK
 *         - ERR_NOTAVAIL - Requested value or method not available
 */
byte BTsetBaud(byte rate){
    AS1_SendBlock("set baud ", 9, NULL);
    switch (rate){
        case BT_1200BAUD:
            AS1_SendBlock("1200", 4, NULL);
            break;
        case BT_2400BAUD:
            AS1_SendBlock("2400", 4, NULL);
            break;
        case BT_4800BAUD:
            AS1_SendBlock("4800", 4, NULL);
            break;
        case BT_9600BAUD:
            AS1_SendBlock("9600", 4, NULL);
            break;
        case BT_19200BAUD:
            AS1_SendBlock("19200", 5, NULL);
            break;
        case BT_38400BAUD:
            AS1_SendBlock("38400", 5, NULL);
            break;
        case BT_57600BAUD:
            AS1_SendBlock("57600", 5, NULL);
            break;
        case BT_115200BAUD:
            AS1_SendBlock("115200", 6, NULL);
            break;
        case BT_230400BAUD:
            AS1_SendBlock("230400", 6, NULL);
            break;
        case BT_460800BAUD:
            AS1_SendBlock("460800", 6, NULL);
            break;
        default:
            return ERR_NOTAVAIL;
            break;
    }
    AS1_SendChar(BT_CR);
    return ERR_OK;
};
