/*! 
@file epAsyncUdpSocket.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date February 13, 2012
@brief Asynchronous UDP Socket Interface
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

An Interface for Asynchronous UDP Socket.

*/
#ifndef __EP_ASYNC_UDP_SOCKET_H__
#define __EP_ASYNC_UDP_SOCKET_H__

#include "epServerEngine.h"
#include "epBaseUdpSocket.h"

namespace epse
{
	class AsynUdpServer;
	/*! 
	@class AsyncUdpSocket epAsyncUdpSocket.h
	@brief A class for Asynchronous UDP Socket.
	*/
	class EP_SERVER_ENGINE AsyncUdpSocket:public BaseUdpSocket
	{
		friend class AsyncUdpServer;
	public:
		/*!
		Default Constructor

		Initializes the Socket
		@param[in] callBackObj the callback object
		@param[in] isAsynchronousReceive the flag for Asynchronous Receive
		@param[in] waitTimeMilliSec wait time for Socket Thread to terminate
		@param[in] maximumProcessorCount the maximum number of processor
		@param[in] lockPolicyType The lock policy
		*/
		AsyncUdpSocket(ServerCallbackInterface *callBackObj,bool isAsynchronousReceive=true,unsigned int waitTimeMilliSec=WAITTIME_INIFINITE,unsigned int maximumProcessorCount=PROCESSOR_LIMIT_INFINITE,epl::LockPolicy lockPolicyType=epl::EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Socket
		*/
		virtual ~AsyncUdpSocket();
		
			
		/*!
		Kill the connection
		*/
		void KillConnection();
	

		/*!
		Set the Maximum Processor Count for the Socket.
		@param[in] maxProcessorCount The Maximum Processor Count to set.
		@remark 0 means there is no limit
		*/
		void SetMaximumProcessorCount(unsigned int maxProcessorCount);

		/*!
		Get the Maximum Processor Count of the Socket
		@return The Maximum Processor Count
		@remark 0 means there is no limit
		*/
		unsigned int GetMaximumProcessorCount() const;

		/*!
		Get the asynchronous receive flag for the Socket.
		@return The flag whether to receive asynchronously.
		*/
		bool GetIsAsynchronousReceive() const;

		/*!
		Set the asynchronous receive flag for the Socket.
		@param[in] isASynchronousReceive The flag whether to receive asynchronously.
		*/
		void SetIsAsynchronousReceive(bool isASynchronousReceive);

		/*!
		Set the wait time for the thread termination
		@param[in] milliSec the time for waiting in millisecond
		*/
		void SetWaitTime(unsigned int milliSec);

	private:	
		friend class BaseServerUDP;

		/*!
		Actually Kill the connection
		*/
		virtual void killConnection();

		
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

		Initializes the AsyncUdpSocket
		@param[in] b the second object
		*/
		AsyncUdpSocket(const AsyncUdpSocket& b):BaseUdpSocket(b)
		{}


		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		AsyncUdpSocket & operator=(const AsyncUdpSocket&b){return *this;}
	private:

		/// Thread Stop Event
		/// @remark if this is raised, the thread should quickly stop.
		epl::EventEx m_threadStopEvent;

		/// processor thread list
		ServerObjectList m_processorList;

		/// Maximum Processor Count
		unsigned int m_maxProcessorCount;

		/// Flag for Asynchronous Receive
		bool m_isAsynchronousReceive;

	};

}

#endif //__EP_ASYNC_UDP_SOCKET_H__