#ifndef ALEPHA_ASSERTIVE_ASSERT_HEADER
#define ALEPHA_ASSERTIVE_ASSERT_HEADER

#include <type_traits>

#include <Alepha/Testing/Assertive/Asserter.h>

#define ALEPHA_TESTING_ASSERTIVE_ASSERT( expected_expression ) \
	[&] \
	{ \
		if( false ) \
		{ \
			auto \
ERROR_assertion_expression_has_side_effects_ERROR= [=] { (void) (expected_expression); }; \
			auto &&p= ERROR_assertion_expression_has_side_effects_ERROR; \
			/* static_assert( std::is_same< decltype( p ), decltype( p ) >::value, "Never should see this" ); */\
			(void) p; \
		} \
		auto behavioralCapture= [&]() -> bool { return expected_expression; }; \
		Alepha::Testing::Assertive::DefaultAsserter::check( behavioralCapture() ); \
	}()

#endif	/*** ALEPHA_ASSERTIVE_ASSERT_HEADER ***/
