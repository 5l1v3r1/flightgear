// multiplaytxmgr.cxx -- routines for transmitting multiplayer data
//                       for Flightgear
//
// Written by Duncan McCreanor, started February 2003.
// duncan.mccreanor@airservicesaustralia.com
//
// Copyright (C) 2003  Airservices Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

/******************************************************************
* $Id$
*
* Description: The multiplayer tx manager provides is used
* to send data to another player or a server for an
* interactive multiplayer FlightGear simulation.
*
******************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <plib/netSocket.h>
#include <stdlib.h>
#include <Main/fg_props.hxx>
#include "multiplaytxmgr.hxx"
#include "mpmessages.hxx"
#include "mpplayer.hxx"

// These constants are provided so that the ident command can list file versions.
const char sMULTIPLAYTXMGR_BID[] = "$Id$";
const char sMULTIPLAYTXMGR_HID[] = MULTIPLAYTXMGR_HID;



/******************************************************************
* Name: FGMultiplayTxMgr
* Description: Constructor.
******************************************************************/
FGMultiplayTxMgr::FGMultiplayTxMgr() {

    int iPlayerCnt;         // Count of players in player array

    // Initialise private members
    m_bInitialised = false;
    mLocalPlayer = NULL;

}


/******************************************************************
* Name: ~FGMultiplayTxMgr
* Description: Destructor. Closes and deletes objects owned by
* this object.
******************************************************************/
FGMultiplayTxMgr::~FGMultiplayTxMgr() {

    Close();

}


/******************************************************************
* Name: init
* Description: Initialises multiplayer transmit
******************************************************************/
bool FGMultiplayTxMgr::init(void) {


    string sTxAddress;                          // Destination address
    int iTxPort;
    bool bSuccess = true;                       // Result of initialisation

    // Initialise object if not already done
    if (!m_bInitialised) {

        // Set members from property values
        string sTxAddress = fgGetString("/sim/multiplay/txhost");
        iTxPort = fgGetInt("/sim/multiplay/txport");

        cout << "FGMultiplayTxMgr::init - txaddress= " << sTxAddress << endl;
        cout << "FGMultiplayTxMgr::init - txport= " << iTxPort << endl;
        
        if (iTxPort > 0) {


            // Create and open tx socket
            mDataTxSocket = new netSocket();
            if (!mDataTxSocket->open(false)) {
                // Failed to open tx socket
                cerr << "FGMultiplayTxMgr::init - Failed to create data transmit socket" << endl;
                bSuccess = false;
            } else {
                mDataTxSocket->setBroadcast(true);
                if (mDataTxSocket->connect(sTxAddress.c_str(), iTxPort) != 0) {
                    // Failed to connect tx socket
                    cerr << "FGMultiplayTxMgr::init - Failed to connect data transmit socket" << endl;
                    bSuccess = false;
                }
            }

            // Create a player object for the local player
            if (bSuccess) {
                mLocalPlayer = new MPPlayer();
                if (!mLocalPlayer->Open(fgGetString("/sim/multiplay/rxaddress"), fgGetInt("/sim/multiplay/rxport"),
                                        fgGetString("/sim/multiplay/callsign"), fgGetString("/sim/model/path"), true)) {
                    cerr << "FGMultiplayTxMgr::init - Failed to create player object for local player" << endl;
                    bSuccess = false;
                }
            }

        // If Tx port == zero then don't initialise
        } else {

            cout << "FGMultiplayTxMgr::init - Tx Port is zero. Multiplay out disabled." << endl;
            bSuccess = false;

        }

        // Save manager state
        m_bInitialised = bSuccess;

    } else {
        cerr << "FGMultiplayTxMgr::init - Attempt to init object that is already opened" << endl;
        bSuccess = false;
    }


    /* Return true if init succeeds */
    return bSuccess;

}


/******************************************************************
* Name: Close
* Description: Closes and deletes the local player object. Closes
* and deletes the tx socket. Resets the object state to unitialised.
******************************************************************/
void FGMultiplayTxMgr::Close(void) {


    // Delete local player
    if (mLocalPlayer) {
        delete mLocalPlayer;
        mLocalPlayer = NULL;
    }

    // Delete socket
    if (mDataTxSocket) {
        mDataTxSocket->close();
        delete mDataTxSocket;
        mDataTxSocket = NULL;
    }

    m_bInitialised = false;

}


/******************************************************************
* Name: SendMyPosition
* Description: Sends the position data for the local position.
******************************************************************/
void FGMultiplayTxMgr::SendMyPosition(const sgMat4 PlayerPosMat4) {

    T_MsgHdr MsgHdr;
    T_PositionMsg PosMsg;
    char sMsg[sizeof(T_MsgHdr) + sizeof(T_PositionMsg)];

    if (m_bInitialised) {
        mLocalPlayer->SetPosition(PlayerPosMat4);
        mLocalPlayer->FillPosMsg(&MsgHdr, &PosMsg);
        memcpy(sMsg, &MsgHdr, sizeof(T_MsgHdr));
        memcpy(sMsg + sizeof(T_MsgHdr), &PosMsg, sizeof(T_PositionMsg));
        mDataTxSocket->send(sMsg, sizeof(T_MsgHdr) + sizeof(T_PositionMsg), 0);
    }


}



/******************************************************************
* Name: SendTextMessage
* Description: Sends a message to the player. The message must
* contain a valid and correctly filled out header and optional
* message body.
******************************************************************/
void FGMultiplayTxMgr::SendTextMessage(const string &sMsgText) const {

    bool bResult = false;
    T_MsgHdr MsgHdr;
    T_ChatMsg ChatMsg;
    int iNextBlockPosition = 0;
    char sMsg[sizeof(T_MsgHdr) + sizeof(T_ChatMsg)];

    if (m_bInitialised) {

        mLocalPlayer->FillMsgHdr(&MsgHdr, CHAT_MSG_ID);

        // Divide the text string into blocks that fit in the message
        // and send the blocks.
        while (iNextBlockPosition < sMsgText.length()) {
            strncpy(ChatMsg.sText, sMsgText.substr(iNextBlockPosition, MAX_CHAT_MSG_LEN - 1).c_str(), MAX_CHAT_MSG_LEN);
            ChatMsg.sText[MAX_CHAT_MSG_LEN - 1] = '\0';
            memcpy(sMsg, &MsgHdr, sizeof(T_MsgHdr));
            memcpy(sMsg + sizeof(T_MsgHdr), &ChatMsg, sizeof(T_ChatMsg));
            mDataTxSocket->send(sMsg, sizeof(T_MsgHdr) + sizeof(T_ChatMsg), 0);
            iNextBlockPosition += MAX_CHAT_MSG_LEN - 1;
        }

    }

}

