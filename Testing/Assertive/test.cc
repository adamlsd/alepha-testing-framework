#include <vector>

#define ALEPHA_ASSERTIVE_USE_ASSERTER DebugAsserter
#include <Alepha/Testing/Assertive/assert.h>

#include <Alepha/Testing/Invariant/InvariantChecker.h>


#define assume ALEPHA_TESTING_ASSERTIVE_ASSERT

template< typename T >
class CopyChecker
{
	protected:
		CopyChecker()= default;

		explicit inline
		CopyChecker( const CopyChecker &copy )
		{
			Alepha::Invariant::InvariantChecker< T > checker( &static_cast< const T & >( copy ) );
		}
};

class PairedList : private CopyChecker< PairedList >
{
	private:
		using Invariant= Alepha::Invariant::InvariantChecker< PairedList >;
		friend Invariant;

		std::vector< int > data;

		inline bool
		invariant() const
		{
			return !( data.size() % 2 );
		}

	public:
		explicit inline
		PairedList()
		{
			Invariant checker( this );
		}

		void
		add_two( const int a, const int b )
		{
			Invariant checker( this );

			data.push_back( a );
			data.push_back( b );
		}

		void
		add_one( const int x )
		{
			Invariant checker( this );

			data.push_back( x );
		}
};



int
main()
{
	assume( 4 );
	int x;
	//assume( x = 4 );

	PairedList p;

	p.add_two( 2, 4 );

	p.add_one( 4 );
}
