#ifndef DEVAN_YAHTZEE_EXCEPTIONS_ROLL_H
#define DEVAN_YAHTZEE_EXCEPTIONS_ROLL_H

#include <exception>

namespace devan_yahtzee::exceptions{

	struct roll_position_out_of_range : public std::out_of_range{
		explicit roll_position_out_of_range(const std::string& arg) : std::out_of_range(arg) {};
	};

	struct roll_infeasible_error : public std::range_error{
		explicit roll_infeasible_error(const std::string& arg) : std::range_error(arg) {};
	};

}

#endif //DEVAN_YAHTZEE_EXCEPTIONS_ROLL_H
