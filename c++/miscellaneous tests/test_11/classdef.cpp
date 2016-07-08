#include <iostream>
#include "classdef.h"

using  std::cout;
using  std::endl;


namespace sio_test
{
	//class ExecutionContext
	bool ExecutionContext::AddNotification(NotifiedIOObject *pIOObj)
	{

		if(pIOObj->m_oExecContext == NULL)
		{

			pIOObj->m_oExecContext = this;
			m_ioList.push_back(pIOObj);
			return true;
		}
		return false;
	}

	void ExecutionContext::RemoveNotification(NotifiedIOObject *pIOObj)
	{
		if(pIOObj->m_oExecContext == this)
		{

			pIOObj->m_oExecContext = NULL;
			
			// we might be in the middle of running through our list of IO objects,
			// and we do not want to shrink the list (complicates the other code).
			// here we simply null out the pointer. The list is compressed in the 
			// RunIOTasks function
			for(size_t i = 0, size = m_ioList.size(); i < size; i++)
			{
				if(m_ioList[i] == pIOObj)
				{
					m_ioList[i] = NULL;
				}
			}
		}		
	}
	
	void ExecutionContext::Run()
	{
	       static int callcount;
		size_t idx, size;

              cout << "the " << callcount++ << " time to call" << endl;

		// build up a new list of file descriptors for the select call and compress
		// the list if we have any deleted entries at this time
		for(idx = 0, size = m_ioList.size(); idx < size; /*empty intentionally*/)
		{
			NotifiedIOObject *pIOObj = m_ioList[idx];
			if(pIOObj)
			{
				if(pIOObj->m_bReadNotify)
				{
					pIOObj->ReadNotify(*this);
                                   pIOObj->SetReadNotify(false);
				}
				if(pIOObj->m_bWriteNotify)
				{
					pIOObj->WriteNotify(*this);
                                   pIOObj->SetWriteNotify(false);
				}
				idx++;
			}
			else
			{
				// found a null IO object entry, compress the list by copying the 
				// last element to the current slot and re-processing (idx is not incremented)
				m_ioList[idx] = m_ioList[size-1];
				size = size - 1;
			}
		}

		if(size != m_ioList.size())
		{
			m_ioList.resize(size);
		}		
	}

    	void ExecutionContext::TestFriend()
	{
  		size_t idx, size;

              
		// build up a new list of file descriptors for the select call and compress
		// the list if we have any deleted entries at this time
		for(idx = 0, size = m_ioList.size(); idx < size; /*empty intentionally*/)
		{
			NotifiedIOObject *pIOObj = m_ioList[idx];
			if(pIOObj)
			{         
			    TCPListenSocket *pTCP = dynamic_cast<TCPListenSocket *>(pIOObj);
			    pTCP->ForTest();
                         cout << "m_bReadNotify = " << pTCP->m_bReadNotify << endl; 
                         //cout << "protectedvalue = " << pTCP->protectedvalue << endl; 
                     }

               idx++;
               }
       }
        
	
	//class NotifiedIOObject
	NotifiedIOObject::NotifiedIOObject()
	{
		m_oExecContext = NULL;
		m_bReadNotify = false;
		m_bWriteNotify = false;
	}

	NotifiedIOObject::~NotifiedIOObject()
	{
		if(m_oExecContext != NULL)
		{
			m_oExecContext->RemoveNotification(this);
		}
	}
	
	
	void NotifiedIOObject::SetReadNotify(bool bReadNotify) 
	{ 
		if(bReadNotify != m_bReadNotify)
		{
			m_bReadNotify = bReadNotify; 
		}
	}
	void NotifiedIOObject::SetWriteNotify(bool bWriteNotify) 
	{ 
		if(bWriteNotify != m_bWriteNotify)
		{
			m_bWriteNotify = bWriteNotify; 
		}
	}

	//class TCPListenSocket
	TCPListenSocket::TCPListenSocket(ExecutionContext &context)
		: m_oContext(context)
	{
		m_oContext.AddNotification(this);
              protectedvalue = 10;
	}
	
	TCPListenSocket::~TCPListenSocket()
	{
		m_oContext.RemoveNotification(this);
	}
		
	bool TCPListenSocket::Listen()
	{
		SetReadNotify(true);			
		return true;
	}
	
	bool TCPListenSocket::CancelListen()
	{
		SetReadNotify(false);			
		return true;
	}
	
	bool TCPListenSocket::Connect()
	{
		SetWriteNotify(true);			
		return true;
	}
	
	bool TCPListenSocket::CancelConnect()
	{
		SetWriteNotify(false);			
		return true;
	}
	
	void TCPListenSocket::ReadNotify(ExecutionContext &context)
	{
		cout << "ReadNotify from TCPListenSocket" << endl;
	}
	
	void TCPListenSocket::WriteNotify(ExecutionContext &context)
	{
		cout << "WriteNotify from TCPListenSocket" << endl;
	}

	void TCPListenSocket::ForTest()
	{
		cout << "ForTest from TCPListenSocket" << endl;
	}

}