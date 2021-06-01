#ifndef DEVAN_YAHTZEE_OBJECTS_SCORECARD_H
#define DEVAN_YAHTZEE_OBJECTS_SCORECARD_H

#include <bitset>

#ifdef DEVAN_YAHTZEE_SCORECARD_UINT8_PRIMITIVE
#include "../util/char_unsigned_print.h"
using scorecard_int = uint8_t;
#else
using scorecard_int = unsigned;
#endif

namespace devan_yahtzee::objects::scorecard{

	class Scorecard {
		std::bitset<13> crossedItems;
		scorecard_int upperSection;
		bool achievedYahtzee;
	public:
		constexpr Scorecard() = default;
		constexpr Scorecard(const Scorecard& in) = default;
	};
}

#endif //DEVAN_YAHTZEE_OBJECTS_SCORECARD_H
