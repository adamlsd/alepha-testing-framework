#ifndef ALEPHA_TESTING_ASSERTIVE_ASSERTER_HEADER
#define ALEPHA_TESTING_ASSERTIVE_ASSERTER_HEADER

#include <cstdlib>

#include <iostream>

namespace Alepha
{
	namespace Testing
	{
		namespace Assertive
		{
			namespace detail
			{
				template< typename Impl >
				struct ActiveAsserterCore
				{
					static inline void check( const bool condition )
					{
						if( !condition ) Impl::fail();
					}
				};

				template< typename Impl >
				struct InactiveAsserterCore
				{
					static inline void check( const bool ) noexcept {}
				};
			}

			struct NullAsserter
			{
				static inline void fail() noexcept {}
			};

			struct BasicAsserter
			{
				static inline void fail()
				{
					std::cerr << "Assertion failed!" << std::endl;
					abort();
				}
			};

			struct DebugAsserter
			{
				static inline void
				fail()
				{
					// TODO: invoke a compiler breakpoint.
				}
			};

			#ifndef ALEPHA_ASSERTIVE_USE_ASSERTER
			#define ALEPHA_ASSERTIVE_USE_ASSERTER BasicAsserter
			#endif

			#ifndef ALEPHA_ASSERTIVE_DISABLE_ASSERTIONS
			template< typename Asserter >
			using DefaultAsserterImpl= detail::ActiveAsserterCore< Asserter >;
			#else
			template< typename Asserter >
			using DefaultAsserterImpl= detail::InactiveAsserterCore< Asserter >;
			#endif


			using DefaultAsserter= DefaultAsserterImpl< ALEPHA_ASSERTIVE_USE_ASSERTER >;
		}
	}
}

#endif	/*** ALEPHA_TESTING_ASSERTIVE_ASSERTER_HEADER ***/
