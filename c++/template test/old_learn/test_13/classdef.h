#pragma once

#include <iostream>

using std::cout;
using std::endl;



namespace template_test
{
	
	size_t* alloc_counter()
	{
		return ::new size_t;
	}
	
	void dealloc_counter(size_t* ptr)
	{
		::delete ptr;
	}

	class SimpleReferenceCount {
	private:
		size_t* counter;
	public:
		SimpleReferenceCount() { counter = NULL; }

	public:
		template<typename T>
		void init(T*) {
			counter = alloc_counter();
			*counter = 1;
		}

		template<typename T>
		void dispose(T*) {
			dealloc_counter(counter);
		}

		template<typename T>
		void increment(T*) {
			++*counter;
		}

		template<typename T>
		void decrement(T*) {
			--*counter;
		}

		template<typename T>
		bool is_zero(T*) {
			return *counter == 0;
		}
		
	};

	template<typename ObjectT, typename CountT, CountT ObjectT::*CountP>
	class MemberReferenceCount {
	public:
		void init(ObjectT* object) {
			object->*CountP = 1;
		}

		void dispose(ObjectT*) {}
		void increment(ObjectT* object) {
			++object->*CountP;
		}

		void decrement(ObjectT* object) {
			--object->*CountP;
		}

		template<typename T> 
		bool is_zero(ObjectT* object) {
			return object->*CountP == 0;
		}
		
	};


	class StandardObjectPolicy {
	public:
		template<typename T> 
		void dispose (T* object) {
			delete object;
		}
	};

	

	template<typename T, 
			  typename CounterPolicy = SimpleReferenceCount,
			  typename ObjectPolicy = StandardObjectPolicy>
	class CountPtr: private CounterPolicy, private ObjectPolicy {
	private:
		typedef CounterPolicy CP;
		typedef ObjectPolicy OP;

		T* object_pointed_to;

	public:
		CountPtr() { object_pointed_to = NULL; }
		explicit CountPtr(T* p) { init(p); }
		CountPtr(CountPtr<T, CP, OP> const& cp): CP((CP const&)cp), OP((OP const&)cp) { attach(cp); }

		~CountPtr() { dettach(); }

		CountPtr<T, CP, OP>& operator= (T* p) {
			dettach();
			init(p);
			return *this;
		}

		CountPtr<T, CP, OP>& operator= (CountPtr<T, CP, OP> const& cp) {
			if(object_pointed_to != cp->object_pointed_to) {
				dettach();

				CP::operator=((CP const&)cp);
				OP::operator=((OP const&)cp);
				attach(cp);
			}

			return *this;
		}

		T* operator-> () const {
			return object_pointed_to;
		}

		T& operator* () const {
			return object_pointed_to;
		}

		operator bool() const {
			return object_pointed_to != (T*)0;
		}

		friend bool operator==(CountPtr<T, CP, OP> const& cp, T const* p) {
			return cp == p;
		}
			
		friend bool operator==(T const* p, CountPtr<T, CP, OP> const& cp) {
				return p == cp;
		}
			

	private:
		void init(T* p) {
			if (p != NULL)
				CounterPolicy::init(p);
			object_pointed_to = p;
		}

		void attach(CountPtr<T, CP, OP> const& cp) {
			object_pointed_to = cp.object_pointed_to;
			if(cp.object_pointed_to != NULL)
				CounterPolicy::increment(cp.object_pointed_to);
		}

		void dettach() {
			if(object_pointed_to != NULL) {
				CounterPolicy::decrement(object_pointed_to);
				if(CounterPolicy::is_zero(object_pointed_to)) {
					CounterPolicy::dispose(object_pointed_to);
					ObjectPolicy::dispose(object_pointed_to);
				}
			}
		}
		
	};

	template<typename T1, typename T2, typename CP, typename OP>
	bool operator== (CountPtr<T1, CP, OP> const& cp1, CountPtr<T2, CP, OP> const& cp2) {
		return cp1.operator->() == cp2.operator->();
	}
    
};
