#ifndef DEVAN_YAHTZEE_STATE_OBJECTS_ROLL_H
#define DEVAN_YAHTZEE_STATE_OBJECTS_ROLL_H

#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <initializer_list>

#include "../exceptions/roll.h"

#ifdef DEVAN_YAHTZEE_ROLL_UINT8_PRIMITIVE
#include "../util/char_unsigned_print.h"
using roll_int = uint8_t;
#else
using roll_int = unsigned;
#endif

namespace devan_yahtzee::state_objects{

	using devan_yahtzee::exceptions::roll_position_out_of_range;
	using devan_yahtzee::exceptions::roll_infeasible_error;

	class Roll {
		using dice_array = std::array<roll_int,6>;

		dice_array dice;
		roll_int one_norm, two_norm, inf_norm, eye_total, incr_start;

		[[nodiscard]] constexpr roll_int& at(size_t pos) {
			try{
				return dice.at(pos);
			} catch(std::out_of_range& e) {
				throw roll_position_out_of_range("Index " + std::to_string(pos) + " out of allowable range 0..5");
			}
		}

		[[nodiscard]] constexpr roll_int at(size_t pos) const {
			try{
				return dice.at(pos);
			} catch(std::out_of_range& e) {
				throw roll_position_out_of_range("Index " + std::to_string(pos) + " out of allowable range 0..5");
			}
		}

	public:
		constexpr Roll() = default;

		constexpr Roll(const Roll& r) = default;

		constexpr Roll(const Roll& r, size_t pos) : Roll(r) {
			die(pos, at(pos)+1);
		}

		constexpr roll_int die(size_t pos) const {
			return at(pos);
		}

		constexpr void die(size_t pos, roll_int new_f) {
			roll_int& die = at(pos);
			roll_int incr = new_f - die;
			if(one_norm + incr > 5)
				throw roll_infeasible_error("Setting die " + std::to_string(pos) + " of roll " + toString() + " to "
											+ std::to_string(new_f) + " results in a roll with " + std::to_string(one_norm)
											+ " dice (max 5 allowed)");
			one_norm += incr;
			two_norm += incr * (new_f + die);
			inf_norm  = std::max(new_f, inf_norm);
			eye_total += (pos+1)*incr;
			die = new_f;
			if(pos > incr_start && new_f){
				incr_start = pos;
			}else if(pos == incr_start && !new_f){
				incr_start = std::max(0l, 5 - (std::find_if(dice.rbegin()+6-pos, dice.rend(), [](const auto& x){return x>0;}) - dice.rbegin()));
			}
		}

		constexpr roll_int oneNorm() const noexcept{
			return one_norm;
		}

		constexpr roll_int twoNorm() const noexcept{
			return two_norm;
		}

		constexpr roll_int infNorm() const noexcept{
			return inf_norm;
		}

		constexpr roll_int eyeTotal() const noexcept{
			return eye_total;
		}

		constexpr roll_int incrStart() const noexcept{
			return incr_start;
		}

		constexpr bool operator==(const Roll& r) const noexcept {
			return dice == r.dice;
		}

		std::string toString() const noexcept {
			std::ostringstream oss{};
			oss << '[';
			std::for_each(dice.cbegin(), dice.cend(),[&oss](const roll_int& ri){
				oss << ri;
			});
			oss << ']';
			return oss.str();
		}

		friend std::ostream& operator<<(std::ostream& os, const Roll& r) noexcept {
			os << r.toString();
			return os;
		}
	};
}

#endif //DEVAN_YAHTZEE_STATE_OBJECTS_ROLL_H
