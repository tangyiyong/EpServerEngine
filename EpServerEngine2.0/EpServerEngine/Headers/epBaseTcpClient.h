/*! 
@file epBaseTcpClient.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date February 13, 2012
@brief Base TCP Client Interface
@version 1.0

@section LICENSE

Copyright (C) 2012  Woong Gyu La <juhgiyo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@section DESCRIPTION

An Interface for Base TCP Client.

*/
#ifndef __EP_BASE_TCP_CLIENT_H__
#define __EP_BASE_TCP_CLIENT_H__

#include "epServerEngine.h"
#include "epBaseClient.h"

namespace epse{

	/*! 
	@class BaseTcpClient epBaseTcpClient.h
	@brief A class for Base TCP Client.
	*/
	class EP_SERVER_ENGINE BaseTcpClient:public BaseClient{
	public:
		/*!
		Default Constructor

		Initializes the Client
		@param[in] callBackObj the call back object
		@param[in] hostName the hostname string
		@param[in] port the port string
		@param[in] waitTimeMilliSec wait time for Client Thread to terminate
		@param[in] lockPolicyType The lock policy
		*/
		BaseTcpClient(ClientCallbackInterface *callBackObj,const TCHAR * hostName=_T(DEFAULT_HOSTNAME), const TCHAR * port=_T(DEFAULT_PORT),unsigned int waitTimeMilliSec=WAITTIME_INIFINITE,epl::LockPolicy lockPolicyType=epl::EP_LOCK_POLICY);

		/*!
		Default Copy Constructor

		Initializes the BaseClient
		@param[in] b the second object
		*/
		BaseTcpClient(const BaseTcpClient& b);
		/*!
		Default Destructor

		Destroy the Client
		*/
		virtual ~BaseTcpClient();

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		BaseTcpClient & operator=(const BaseTcpClient&b);
	
		/*!
		Connect to the server
		@param[in] hostName the hostname string
		@param[in] port the port string
		@remark if argument is NULL then previously setting value is used
		*/
		virtual bool Connect(const TCHAR * hostName=NULL, const TCHAR * port=NULL)=0;

		/*!
		Disconnect from the server
		*/
		virtual void Disconnect()=0;


		/*!
		Send the packet to the server
		@param[in] packet the packet to be sent
		@param[in] waitTimeInMilliSec wait time for sending the packet in millisecond
		@return sent byte size
		@remark return -1 if error occurred
		*/
		int Send(const Packet &packet, unsigned int waitTimeInMilliSec=WAITTIME_INIFINITE);

	protected:

	

		/*!
		Receive the packet from the server
		@param[out] packet the packet received
		@return received byte size
		*/
		int receive(Packet &packet);

		/*!
		Actually processing the client thread
		*/
		virtual void execute()=0;

		/*!
		Actually Disconnect from the server
		*/
		virtual void disconnect()=0;


	protected:

		/// Temp Packet;
		Packet m_recvSizePacket;


	};
}


#endif //__EP_BASE_TCP_CLIENT_H__