#include <vector>

namespace sio_test
{
	class NotifiedIOObject;
       class TCPListenSocket;

	class ExecutionContext
	{
	public:
		bool AddNotification(NotifiedIOObject *pIOObj);
		void RemoveNotification(NotifiedIOObject *pIOObj);
		
		// RunIOTasks
		//
		// Runs through the list of waiting IO objects and notifies which have waiting data
		// (or room to write)
		void Run();

              void TestFriend();
		
	protected: // data
		// our list of current watching IO objects
		typedef std::vector<NotifiedIOObject*> IOObjectList;
		IOObjectList m_ioList;
	};


	class NotifiedIOObject
	{
	public:
		NotifiedIOObject();
		virtual ~NotifiedIOObject();
	
	protected:	
		// The OnReadRead and WriteNotify notifications are called when the descriptor
		// has data to read or write.		
		virtual void ReadNotify(ExecutionContext &context) = 0;
		virtual void WriteNotify(ExecutionContext &context) = 0;

		void SetReadNotify(bool bReadNotify); 
		void SetWriteNotify(bool bWriteNotify);

	protected:
		bool m_bReadNotify;
		bool m_bWriteNotify;

		ExecutionContext *m_oExecContext;
		friend class ExecutionContext;
	};
	
	
	
	class TCPListenSocket : public NotifiedIOObject
	{
	public:
		TCPListenSocket(ExecutionContext &context);
		virtual ~TCPListenSocket();
	
		virtual bool Listen();
		virtual bool CancelListen();
		
		virtual bool Connect();
		virtual bool CancelConnect();
        
              void ForTest();
              
	protected:	
		// The OnRead and WriteNotify notifications are called when the descriptor
		// has data to read or write.		
		virtual void ReadNotify(ExecutionContext &context);
		virtual void WriteNotify(ExecutionContext &context);
              //void ForTest();

	protected: //data
		// Our execution context that supports notifications of read/write
		ExecutionContext &m_oContext;

       protected:
              int protectedvalue;
	};

};