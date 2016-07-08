#pragma once

#include <iostream>

using std::cout;
using std::endl;



namespace template_test
{

	template <typename T1, typename T2>
	class Duo {
	public:
		typedef T1 Type1;
		typedef T2 Type2;
		enum { N = 2 };

	private:
		T1 value1;
		T2 value2;

	public:
		Duo(): value1(), value2() {}
		Duo(T1 const& a, T2 const& b): value1(a), value2(b) {}

		template <typename U1, typename U2>
		Duo(Duo<U1, U2> const& d): value1(d.v1()), value2(d.v2()) {}

		template<typename U1, typename U2>
		Duo<T1, T2>& operator= (Duo<U1, U2> const& d) {
			value1 = d.value1;
			value2 = d.value2;
			return *this;
		}

		T1& v1() { return value1; }
		T1 const& v1() const { return value1; }
		T2& v2() { return value2; }
		T2 const& v2() const { return value2; }

	};

	template<typename T1, typename T2, typename U1, typename U2>
	inline bool operator == (Duo<T1, T2> const& d1, Duo<U1, U2> const& d2) {
		return d1.v1() == d2.v1() && d1.v2() == d2.v2();
	}

	template<typename T1, typename T2, typename U1, typename U2>
	inline bool operator != (Duo<T1, T2> const& d1, Duo<U1, U2> const& d2) {
		return !(d1 == d2);
	}

	template<typename T1, typename T2>
	inline Duo<T1, T2> make_duo(T1 const& a, T2 const& b) {
		return Duo<T1, T2>(a, b);
	}
	

	template <typename A, typename B, typename C>
	class Duo<A, Duo<B, C> > {
	public:
		typedef A T1;
		typedef Duo<B, C> T2;
		enum { N = Duo<B, C>::N + 1 };

	private:
		T1 value1;
		T2 value2;

	public:
		Duo(): value1(), value2() {}
		Duo(T1 const& a, T2 const& b): value1(a), value2(b) {}

		template <typename U1, typename U2>
		Duo(Duo<U1, U2> const& d): value1(d.v1()), value2(d.v2()) {}

		template<typename U1, typename U2>
		Duo<T1, T2>& operator= (Duo<U1, U2> const& d) {
			value1 = d.value1;
			value2 = d.value2;
			return *this;
		}

		T1& v1() { return value1; }
		T1 const& v1() const { return value1; }
		T2& v2() { return value2; }
		T2 const& v2() const { return value2; }	
	};

	template<typename A>
	struct Duo<A, void> {
	public:
		typedef A T1;
		typedef void T2;
		enum { N = 1 };

	private:
		T1 value1;

	public:
		Duo():value1() {}
		Duo(T1 const& a):value1(a) {}

		T1& v1() { return value1; }
		T1 const& v1() const { return value1; }
		void v2() {}
		void v2() const {}	
	};

}

