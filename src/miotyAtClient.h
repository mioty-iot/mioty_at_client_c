/**
 * \copyright    Copyright 2019 - 2022 Fraunhofer Institute for Integrated Circuits IIS, Erlangen Germany
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
/**
 * \file
 * \version     0.0.1
 * \brief       Client side of communication with a MIOTY™ modem via AT protocol v2.x.x
 */

#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef _AT_CLIENT_H
#define _AT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum miotyAtClient_returnCode {
    MIOTYATCLIENT_RETURN_CODE_OK,
    MIOTYATCLIENT_RETURN_CODE_MacError,
    MIOTYATCLIENT_RETURN_CODE_MacFramingError, // 2
    MIOTYATCLIENT_RETURN_CODE_ArgumentSizeMismatch,
    MIOTYATCLIENT_RETURN_CODE_ArgumentOOR, // 4
    MIOTYATCLIENT_RETURN_CODE_BufferSizeInsufficient,
    MIOTYATCLIENT_RETURN_CODE_MacNodeNotAttached, // 6
    MIOTYATCLIENT_RETURN_CODE_MacNetworkKeyNotSet,
    MIOTYATCLIENT_RETURN_CODE_MacAlreadyAttached,//8
    MIOTYATCLIENT_RETURN_CODE_ERR, //not in protocol
    MIOTYATCLIENT_RETURN_CODE_MacDownlinkNotAvailable, // 10
    MIOTYATCLIENT_RETURN_CODE_UplinkPackingErr,
    MIOTYATCLIENT_RETURN_CODE_MacNoDownlinkReceived, // 12
    MIOTYATCLIENT_RETURN_CODE_MacOptionNotAllowed,
    MIOTYATCLIENT_RETURN_CODE_MacDownlinkErr, // 14
    MIOTYATCLIENT_RETURN_CODE_MacDefaultsNotSet,
    MIOTYATCLIENT_RETURN_CODE_ATErr, // 16 generic AT error not found
    MIOTYATCLIENT_RETURN_CODE_ATgenericErr, // 17 generic AT error
    MIOTYATCLIENT_RETURN_CODE_ATCommandNotKnown,
    MIOTYATCLIENT_RETURN_CODE_ATParamOOB, //parameter out of bounds
    MIOTYATCLIENT_RETURN_CODE_ATDataSizeMismatch, // 20
    MIOTYATCLIENT_RETURN_CODE_ATUnexpectedChar,
    MIOTYATCLIENT_RETURN_CODE_ATArgInvalid, // 22
    MIOTYATCLIENT_RETURN_CODE_ATReadFailed,
} miotyAtClient_returnCode;

void miotyAtClientWrite(uint8_t *, uint16_t);
bool miotyAtClientRead(uint8_t *, uint8_t *);


/**
 * @brief Soft reset of the MIOTY™ modem. Persistent fields shall keep their current value.
 *
 * @return 
 */
miotyAtClient_returnCode miotyAtClient_reset(void); //AT-RST
/**
 * @brief Reset the MIOTY™ modem to its factory defaults
 *
 * @return 
 */
miotyAtClient_returnCode miotyAtClient_factoryReset(void); //ATZ

/**
 * @brief Set Factory Defaults of the MITOY™ modem (only usable if factory defaults are not set) (AT-DEF)
 *
 * @param eui64             8-byte long EUI
 * @param ipv6              8-byte IPv6 Subnet Mask
 * @param nwKey             16-byte Network Key
 * @param shortAdress       2-byte Short Adress
 * @param appCryptoKey      16-byte Application Crypto Key
 * @param ulProfile         uplink Profile (0-3/EU0-US0)
 * @param ulMode            uplink Mode (0-2)
 * @param ulSyncBurst       uplink Syncronization Burst enable (0/1)
 * @param appCryptoMode     Application Crypto Mode (0/1)
 * @param attached1stBoot   Node attached on first Boot (0/1)
 *
 * @return 
 */
miotyAtClient_returnCode miotyAtClient_setDefaults(uint8_t * eui64, uint8_t * ipv6, uint8_t * nwKey, uint8_t * shortAdress, uint8_t * appCryptoKey, uint8_t ulProfile, uint8_t ulMode, uint8_t ulSyncBurst, uint8_t appCryptoMode, uint8_t attached1stBoot);

/**
 * @brief Send AT command to set the network key (AT-MNWK)
 *
 * @param[in]   nwKey           Pointer to a buffer containing the 16 byte long network key
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution

 */
miotyAtClient_returnCode miotyAtClient_setNetworkKey(uint8_t * nwKey);

/**
 * @brief Get/Set IPv6 subnet mask (AT-IPV6)
 *
 * @param[in,out]   ipv6            If set=true ipv6 contains the 8 byte value to be set as subnet mask, else ipv6 is a buffer where the value can be stored
 * @param[in]       set             If true the subnet mask will be set to ipv6, else it will be read from device and written to ipv6.
 *
 * @return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution

 */
miotyAtClient_returnCode miotyAtClient_getOrSetIPv6SubnetMask(uint8_t * ipv6, bool set);

/**
 * @brief Get/Set EUI mask (AT-MEUI)
 *
 * @param[in,out]   eui             If set=true eui contains the 8 byte value to be set as EUI, else eui is a buffer where the value can be stored
 * @param[in]       set             If true the subnet mask will be set to eui, else it will be read from device and written to eui.
 *
 * @return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution

 */
miotyAtClient_returnCode miotyAtClient_getOrSetEui(uint8_t * eui64, bool set);

/**
 * @brief Get/Set short Adress (AT-MSAD)
 *
 * @param[in,out]   shortAdress     Either a 2 byte array containing the new short Adress or a 2 byte buffer to store the current short Adress
 * @param[in]       set             If true short Adress will be set, otherwise it will be written to shortAdress
 *
 * @return 
 */
miotyAtClient_returnCode miotyAtClient_getOrSetShortAdress(uint8_t * shortAdress, bool set);

/**
 * @brief Get/Set Uplink transmit power (AT-UTPL)
 *
 * @param[in,out]   txPower         Pointer to the transmit Power level needs to be in {10,...100}
 * @param[in]       set             If true transmit power will be set to *txPower otherwise it will be written to *txPower
 *
 * @return 
 */
miotyAtClient_returnCode miotyAtClient_getOrSetTransmitPower(uint32_t * txPower, bool set);

/**
 * @brief Get/Set modem Baudrate (AT+IPR)
 *
 * @param[in,out]   baud            Pointer to baudrate
 * @param[in]       set             If true baudrate will be set to *baud otherwise it will be written to *baud
 *
 * @return 
 */
miotyAtClient_returnCode miotyAtClient_getOrSetBaudrate(uint32_t * baud, bool set);

/**
 * @brief Send AT command to get the current packet counter (AT-MPCT)
 *
 * @param[out]   counter         Pointer to store the packet counter
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution

 */
miotyAtClient_returnCode miotyAtClient_getPacketCounter(uint32_t * counter);

/**
 * @brief Get/Set uplink Mode (AT-UM)
 *
 * @param[in,out] ulMode    uplink Mode to set or get from the MIOTY modem
 * @param[in]     set       If true the uplink Mode of the MIOTY modem will be set to ulMode, else it will be read from the modem and written to ulMode
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_uplinkMode(uint32_t * ulMode, bool set);

/**
 * @brief Get/Set uplink SyncBurst (AT-US)
 *
 * @param[in,out] ulSyncBurst   uplink SyncBurst to set or get from the MIOTY modem
 * @param[in]     set           If true the uplink SyncBurst of the MIOTY modem will be set to ulSyncBurst, else it will be read from the modem and written to ulSyncBurst
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_uplinkSyncBurst(uint32_t * ulSyncBurst, bool set);

/**
 * @brief Get/Set uplink Profile (AT-UP)
 *
 * @param[in,out] ulProfile    uplink Profile to set or get from the MIOTY modem
 * @param[in]     set          If true the uplink Profile of the MIOTY modem will be set to ulProfile, else it will be read from the modem and written to ulProfile
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_uplinkProfile(uint32_t * ulProfile, bool set);

/**
 * @brief Get/Set application Crypto Mode (AT-ACM)
 *
 * @param[in,out] appCyrptoMode    application Crypto Mode to set or get from the MIOTY modem
 * @param[in]     set              If true the application Crypto Mode of the MIOTY modem will be set to appCyrptoMode, else it will be read from the modem and written to appCyrptoMode
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_appCryptoMode(uint32_t * appCyrptoMode, bool set);

/**
 * @brief Set the application crypto key (AT-ACK)
 *
 * @param[in,out] appCryptoKey  Pointer to a buffer containing the 16 byte long application crypto key
 *
 * @return      miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_setAppCryptoKey(uint8_t * appCryptoKey);

/*!
 * \brief Send uni-directional message (AT-UMPF)
 *
 * \param[in]       msg             Pointer to message to be send (including MPF field)
 * \param[in]       sizemsg         Size of msg
 * \param[out]      packetCounter   packet Counter after successful transmission
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_sendMessageUniMPF(uint8_t * msg, uint8_t sizeMsg, uint32_t * packetCounter);

/*!
 * \brief Send uni-directional message (AT-U)
 *
 * \param[in]       msg             Pointer to message to be send
 * \param[in]       sizemsg         Size of msg
 * \param[out]      packetCounter   packet Counter after successful transmission
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_sendMessageUni(uint8_t * msg, uint8_t sizeMsg, uint32_t * packetCounter);

/*!
 * \brief Send bi-directional message (AT-BMPF)
 *
 * \param[in]       msg             Pointer to message to be send (including MPF field)
 * \param[in]       sizemsg         Size of msg
 * \param[out]      data            Pointer to a buffer, where data returned by AT_cmd will be stored
 * \param[out]      size_data       Size of the Buffer, will be set to size of data returned by AT_cmd
 * \param[out]      packetCounter   packet Counter after successful transmission
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_sendMessageBidiMPF(uint8_t * msg, uint8_t sizeMsg, uint8_t * data, uint8_t * size_data, uint32_t * packetCounter);

/*!
 * \brief Send bi-directional message (AT-B)
 *
 * \param[in]       msg             Pointer to message to be send
 * \param[in]       sizemsg         Size of msg
 * \param[out]      data            Pointer to a buffer, where data returned by AT_cmd will be stored
 * \param[out]      size_data       Size of the Buffer, will be set to size of data returned by AT_cmd
 * \param[out]      packetCounter   packet Counter after successful transmission
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_sendMessageBidi(uint8_t * msg, uint8_t sizeMsg, uint8_t * data, uint8_t * size_data, uint32_t * packetCounter);

/*!
 * \brief Send uni-directional message without MAC (AT-TU)
 *
 * \param[in]       msg             Pointer to message to be send
 * \param[in]       sizemsg         Size of msg
 * \param[out]      packetCounter   packet Counter after successful transmission
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_sendMessageUniTransparent(uint8_t * msg, uint8_t sizeMsg, uint32_t * packetCounter);

/*!
 * \brief Send bi-directional message without MAC (AT-TB)
 *
 * \param[in]       msg             Pointer to message to be send
 * \param[in]       sizemsg         Size of msg
 * \param[out]      data            Pointer to a buffer, where data returned by AT_cmd will be stored
 * \param[out]      size_data       Size of the Buffer, will be set to size of data returned by AT_cmd
 * \param[out]      packetCounter   packet Counter after successful transmission
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_sendMessageBidiTransparent(uint8_t * msg, uint8_t sizeMsg, uint8_t * data, uint8_t * size_data, uint32_t * packetCounter);

/*!
 * \brief Mac attach (AT-MAOA)
 *
 * \param[in]       msg     Pointer to NONCE data (length 4 required)
 * \param[out]      MSTA    MAC state as returned by the AT-Command
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_macAttach(uint8_t * data, uint8_t * MSTA);

/*!
 * \brief Mac dettach (AT-MDOA)
 *
 * \param[in]       data        Pointer to data that will be sent to base station
 * \param[in]       sizeData    Size of data
 * \param[out]      MSTA        MAC state as returned by the AT-Command
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_macDetach(uint8_t * data, uint8_t sizeData, uint8_t * MSTA);

/**
 * @brief Local Mac Attach (AT-MALO)
 *
 * @param[out]      MSTA            Mac State as returned by the MIOTY modem
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_macAttachLocal(uint8_t * MSTA);

/**
 * @brief Local Mac Detach (AT-MDLO)
 *
 * @param[out]      MSTA            Mac State as returned by the MIOTY modem
 *
 * \return          miotyAtClient_returnCode    indicating success/error of AT_cmd execution
 */
miotyAtClient_returnCode miotyAtClient_macDetachLocal(uint8_t * MSTA);

#ifdef __cplusplus
}
#endif

#endif
