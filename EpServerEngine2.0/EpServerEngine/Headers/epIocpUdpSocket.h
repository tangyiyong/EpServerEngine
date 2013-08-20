/*! 
@file epIocpUdpSocket.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date February 13, 2012
@brief IOCP UDP Socket Interface
@version 1.0

@section LICENSE

The MIT License (MIT)

Copyright (c) 2012-2013 Woong Gyu La <juhgiyo@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

@section DESCRIPTION

An Interface for IOCP UDP Socket.

*/
#ifndef __EP_IOCP_UDP_SOCKET_H__
#define __EP_IOCP_UDP_SOCKET_H__

#include "epServerEngine.h"
#include "epBaseUdpSocket.h"

namespace epse
{

	/*! 
	@class IocpUdpSocket epIocpUdpSocket.h
	@brief A class for IOCP UDP Socket.
	*/
	class EP_SERVER_ENGINE IocpUdpSocket:public BaseUdpSocket
	{
	public:
		/*!
		Default Constructor

		Initializes the Socket
		@param[in] callBackObj the callback object
		@param[in] waitTimeMilliSec wait time for Socket Thread to terminate
		@param[in] lockPolicyType The lock policy
		*/
		IocpUdpSocket(ServerCallbackInterface *callBackObj,unsigned int waitTimeMilliSec=WAITTIME_INIFINITE,epl::LockPolicy lockPolicyType=epl::EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Socket
		*/
		virtual ~IocpUdpSocket();

		/*!
		Check if the connection is alive
		@return true if the connection is alive otherwise false
		*/
		bool IsConnectionAlive() const;

		/*!
		Kill the connection
		*/
		void KillConnection(EventEx *completionEvent,ServerCallbackInterface *callBackObj,Priority priority);

		/*!
		Kill the connection
		*/
		void KillConnection();

		/*!
		Send the packet to the server
		@param[in] packet the packet to be sent
		@param[in] completionEvent the event for IO completion
		@param[in] callBackObj the callback object for IO completion
		@param[in] priority the priority of the send
		*/
		void Send(Packet &packet,EventEx *completionEvent=NULL,ServerCallbackInterface *callBackObj=NULL,Priority priority=PRIORITY_NORMAL);


		/*!
		Receive the packet from the client
		@param[in] completionEvent the event for IO completion
		@param[in] callBackObj the callback object for IO completion
		@param[in] priority the priority of the receive
		@return received packet
		@remark the caller must call ReleaseObj() for Packet to avoid the memory leak.
		*/
		void Receive(EventEx *completionEvent=NULL,ServerCallbackInterface *callBackObj=NULL,Priority priority=PRIORITY_NORMAL);

	private:	
		friend class IocpUdpServer;
		friend class IocpUdpProcessor;

		/*!
		Send the packet to the server
		@param[in] packet the packet to be sent
		@param[in] waitTimeInMilliSec wait time for sending the packet in millisecond
		@param[in] sendStatus the status of Send
		@return sent byte size
		@remark return -1 if error occurred
		*/
		int Send(const Packet &packet, unsigned int waitTimeInMilliSec=WAITTIME_INIFINITE,SendStatus *sendStatus=NULL);


		/*!
		Receive the packet from the client
		@param[in] waitTimeInMilliSec wait time for receiving the packet in millisecond
		@param[out] retStatus the pointer to ReceiveStatus enumerator to get receive status.
		@return received packet
		@remark the caller must call ReleaseObj() for Packet to avoid the memory leak.
		*/
		Packet *Receive(unsigned int waitTimeInMilliSec=WAITTIME_INIFINITE,ReceiveStatus *retStatus=NULL);
	

		/*!
		Actually Kill the connection
		*/
		virtual void killConnection();

		/*!
		Actually Kill the connection without Callback
		*/
		void killConnectionNoCallBack();

		/*!
		thread loop function
		*/
		virtual void execute();

		/*!
		Add new packet received from client
		@param[in] packet the new packet received from client
		*/
		virtual void addPacket(Packet *packet);

		
	private:
		/*!
		Default Copy Constructor

		Initializes the Socket
		@param[in] b the second object
		@remark Copy Constructor prohibited
		*/
		IocpUdpSocket(const IocpUdpSocket& b):BaseUdpSocket(b)
		{}

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		@remark Copy Operator prohibited
		*/
		IocpUdpSocket & operator=(const IocpUdpSocket&b){return *this;}
	
	
	private:
		/// Packet Received Event
		epl::EventEx m_packetReceivedEvent;

		/// Connection status
		bool m_isConnected;
	};

}

#endif //__EP_IOCP_UDP_SOCKET_H__