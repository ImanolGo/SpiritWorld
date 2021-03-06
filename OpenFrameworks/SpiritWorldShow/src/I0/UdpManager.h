/*
 *  UdpManager.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 04/04/18.
 *
 */


#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "Manager.h"

//========================== class UdpManager =======================================
//==============================================================================
/** \class UdpManager UdpManager.h
 *	\brief class for managing the udp connection
 *	\details It writes and send udp data
 */


class UdpManager: public Manager
{

    struct udp_header {
        Byte f1;
        Byte f2;
        Byte f3;
        short size;
        Byte  channel;
    };
    
public:
    //! Constructor
    UdpManager();

    //! Destructor
    virtual ~UdpManager();

    //! setups the udp manager
    void setup();
    
    //! updates the udp manager
    void update();
    
    void setUdp2Sending(bool value);


private:
    
    void setupUdp();
    
    void setupHeader();
    
    void sendBlackUdp2();
    
private:
    
    ofxUDPManager m_udpConnection;
    ofxUDPManager m_udpConnection2;
    udp_header    m_header;
    bool          m_isUdp2Sending;
    
};

