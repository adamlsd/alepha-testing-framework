#include <vector>

namespace Alepha
{
	namespace Testing
	{
		template< typename T > class Generator;

		template<>
		class Generator< int >
		{
			private:
				static const std::vector< int > universalSpecialCases=
						{
							0,
							1, -1,
							2, -2,
							5, -5,
							std::numeric_limits< int >::min(), std::numeric_limits< int >::max(),
							std::numeric_limits< int >::min() + 1, std::numeric_limits< int >::max() - 1
						};

				const std::vector< int > specialCases;
				const std::size_t maxRuns;

				static inline const
				buildSpecialCases( std::vector< int > userSpecialCases )
				{
					userSpecialCases.insert( begin( userSpecialCases ),
							begin( universalSpecialCases ), end( universalSpecialCases ) );
					return userSpecialCases;
				}


			public:
				explicit inline
				Generator( const std::size_t imr, std::vector< int > extraCases= {} )
						: specialCases( buildSpecialCases( std::move( extraCases ) ) ),
						  maxRuns( imr ) {}

				class const_iterator;
				using iterator= const_iterator;

				class const_iterator
				{
					private:
						const Generator *generator;
						std::vector< int >::const_iterator pos;
						std::size_t index;
						int value;

						using Invariant= Alepha::Testing::Invariant::InvariantChecker< const_iterator >;
						friend Invariant;

						inline bool
						invariant() const
						{
							return this->generator && ( this->index <= this->generator->maxRuns );
						}

						void
						advance()
						{
							if( this->pos < end( this->generator ) value= *pos++;
							else value= random();

							++index;
						}

					public:
						inline bool
						operator == ( const const_iterator &rhs ) const
						{
							Invariant checker( this );
							Invariant checker( &rhs );
							ALEPHA_TESTING_ASSERTIVE_ASSERT( this->generator == rhs.generator );

							return this->index == rhs.index;
						}

						inline bool
						operator != ( const const_iterator &rhs ) const
						{
							return !( *this == rhs );
						}

						auto operator ++() &
								-> typename std::remove_reference< decltype( *this ) >::type
						{
							Invariant checker( this );
							this->advance();
							return *this;
						}

						auto operator++ ( int ) &
								-> typename std::add_reference< decltype( *this ) >::type
						{
							Invariant checker( this );
							const auto rv= *this;

							this->advance();
							return rv;
						}

						inline const int &
						operator *() const
						{
							Invariant checker( this );

							return this->value;
						}
					};
