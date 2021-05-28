//
// Created by JLANDA91 on 19/05/2021.
//

#ifndef DEVAN_YAHTZEE_ROLL_H
#define DEVAN_YAHTZEE_ROLL_H

#include <iostream>
//#include <stringstream>
#include <array>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <initializer_list>

#ifdef DEVAN_YAHTZEE_ROLL_PRIMITIVE_CHAR
	using roll_int = uint8_t;

	std::ostream& operator<<(std::ostream& os, const uint8_t& x){
		os << (unsigned)x;
		return os;
	}
#else
	using roll_int = unsigned;
#endif

namespace devan_yahtzee::objects{

	using dice_array = std::array<roll_int,6>;

	struct roll_position_out_of_range : public std::out_of_range{
		explicit roll_position_out_of_range(const std::string& arg) : std::out_of_range(arg) {};
	};

	struct roll_infeasible_error : public std::range_error{
		explicit roll_infeasible_error(const std::string& arg) : std::range_error(arg) {};
	};

	class Roll {
		dice_array dice;
		roll_int one_norm, two_norm, inf_norm;

		[[nodiscard]] constexpr roll_int& at(size_t pos) {
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
			setDie(pos, at(pos)+1);
		}

		constexpr void setDie(size_t pos, roll_int new_f) {
			roll_int& die = at(pos);
			one_norm += new_f - die;
			if(one_norm > 5)
				throw roll_infeasible_error("Setting die " + std::to_string(pos) + " of roll " + toString() + " to "
											+ std::to_string(new_f) + " results in a roll with " + std::to_string(one_norm)
											+ " dice (max 5 allowed)");
			two_norm += (new_f - die) * (new_f + die);
			inf_norm  = std::max(new_f, inf_norm);
			die = new_f;
		}

		[[nodiscard]] constexpr roll_int oneNorm() const noexcept{
			return one_norm;
		}

		[[nodiscard]] constexpr roll_int twoNorm() const noexcept{
			return two_norm;
		}

		[[nodiscard]] constexpr roll_int infNorm() const noexcept{
			return inf_norm;
		}

		[[nodiscard]] constexpr roll_int die(size_t pos) {
			return at(pos);
		}

		[[nodiscard]] std::string toString() const noexcept {
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

#endif //DEVAN_YAHTZEE_ROLL_H
