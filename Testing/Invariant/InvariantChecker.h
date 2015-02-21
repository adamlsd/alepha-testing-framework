#ifndef ALEPHA_INVARIANT_INVARIANT_CHECKER
#define ALEPHA_INVARIANT_INVARIANT_CHECKER

//#include <boost/noncopyable.hpp>

#include <Alepha/Testing/Assertive/assert.h>

namespace Alepha
{
	namespace Invariant
	{
		template< typename Class, typename Argument= void > class InvariantChecker;

		template< typename Class, typename Argument >
		class InvariantChecker
		{
			private:
				const Class *const class_;

				inline void
				checkInvariant() const
				{
					ALEPHA_TESTING_ASSERTIVE_ASSERT( this->class_->invariant( Argument() ) );
				}

			public:
				explicit inline
				InvariantChecker( const Class *const cp )
						: class_( cp )
				{
					this->checkInvariant();
				}

				inline
				~InvariantChecker()
				{
					this->checkInvariant();
				}
		};

		template< typename Class >
		class InvariantChecker< Class, void >
		{
			private:
				const Class *const class_;

				inline void
				checkInvariant() const
				{
					ALEPHA_TESTING_ASSERTIVE_ASSERT( this->class_->invariant() );
				}

			public:
				explicit inline
				InvariantChecker( const Class *const cp )
						: class_( cp )
				{
					this->checkInvariant();
				}

				inline
				~InvariantChecker()
				{
					this->checkInvariant();
				}
		};

	}
}

#endif	/*** ALEPHA_INVARIANT_INVARIANT_CHECKER ***/
