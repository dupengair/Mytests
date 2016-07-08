#pragma once

#include <iostream>

using std::cout;
using std::endl;




namespace template_test
{




	template<int N, typename T>
	class DuoValue {
	public:
		static void get(T&) {}
		static void get(T const&) {}
	};

	template <typename A, typename B>
	class DuoValue<1, Duo<A, B> > {
	public:
		static A& get(Duo<A, B>& d) {
			return d.v1();
		}

		static A const& get(Duo<A, B> const& d) {
			return d.v1();
		}
	};

	template <typename A, typename B>
	class DuoValue<2, Duo<A, B> > {
	public:
		static B& get(Duo<A, B>& d) {
			return d.v2();
		}

		static B const& get(Duo<A, B> const& d) {
			return d.v2();
		}
	};

	template<int N, typename A, typename B, typename C>
	struct DuoValue<N, Duo<A, Duo<B, C> > > {
		static typename TypeOp<typename DuoT<N-1, Duo<B, C> >::ResultT>::RefT get(Duo<A, Duo<B, C> >& d) {
			return DuoValue<N-1, Duo<B, C> >::get(d.v2());
		}

		static typename TypeOp<typename DuoT<N-1, Duo<B, C> >::ResultT>::RefConstT get(Duo<A, Duo<B, C> >const& d) {
			return DuoValue<N-1, Duo<B, C> >::get(d.v2());
		}
	};

	template<typename A, typename B, typename C>
	class DuoValue<1, Duo<A, Duo<B, C> > > {
	public:
		static A& get(Duo<A, Duo<B, C> >& d) {
			return d.v1();
		}

		static A const& get(Duo<A, Duo<B, C> >const& d) {
			return d.v1();
		}
	};

	template<typename A, typename B, typename C>
	class DuoValue<2, Duo<A, Duo<B, C> > > {
	public:
		static B& get(Duo<A, Duo<B, C> >& d) {
			return d.v2().v1();
		}

		static B const& get(Duo<A, Duo<B, C> >const& d) {
			return d.v2().v1();
		}
	};


	template<int N, typename A, typename B>
	inline typename TypeOp<typename DuoT<N, Duo<A, B> >::ResultT>::RefT val(Duo<A, B>& d) {
		return DuoValue<N, Duo<A, B> >::get(d);
	}

	template<int N, typename A, typename B>
	inline typename TypeOp<typename DuoT<N, Duo<A, B> >::ResultT>::RefConstT val(Duo<A, B> const& d) {
		return DuoValue<N, Duo<A, B> >::get(d);
	}


}

