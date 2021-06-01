#include <iostream>

#include "include.h"
#include "../src/objects/roll.h"

using devan_yahtzee::objects::Roll;
using devan_yahtzee::objects::roll_position_out_of_range;
using devan_yahtzee::objects::roll_infeasible_error;

inline void require_roll_members(const Roll& r, const std::array<roll_int,6>& dice, const roll_int oneNorm,
							   const roll_int twoNorm, const roll_int infNorm, const char* repr){
	// Compare dice
	for(size_t i=0;i<6;i++)
		REQUIRE_EQ(r.die(i), dice[i]);

	// Comparing roll norms
	REQUIRE_EQ(r.oneNorm(), oneNorm);
	REQUIRE_EQ(r.twoNorm(), twoNorm);
	REQUIRE_EQ(r.infNorm(), infNorm);

	// Comparing string representation
	REQUIRE_EQ(r.toString(), repr);
}

SCENARIO("Roll Methods"){
	GIVEN("The zero-roll r1 (default ctor)"){
		Roll r1{};
		INFO("Roll r1 = ",r1);

		THEN("Default members are initialized correctly") {
			require_roll_members(r1, {0, 0, 0, 0, 0, 0},
								 0, 0, 0, "[000000]");
		}

		THEN("Getting the frequency of a dice number not 1 through 6 throws roll_position_out_of_range error") {
			// Trying to get the amount of 7s, 8s and 9s
			REQUIRE_THROWS_AS(r1.die(6), const roll_position_out_of_range&);
			REQUIRE_THROWS_AS(r1.die(7), const roll_position_out_of_range&);
			REQUIRE_THROWS_AS(r1.die(8), const roll_position_out_of_range&);
		}

		THEN("Setting the frequency of a dice number not 1 through 6 throws roll_position_out_of_range error"){
			// Trying to set the amount of 7s, 8s and 9s
			REQUIRE_THROWS_AS(r1.die(6, 0), const roll_position_out_of_range&);
			REQUIRE_THROWS_AS(r1.die(7, 0), const roll_position_out_of_range&);
			REQUIRE_THROWS_AS(r1.die(8, 0), const roll_position_out_of_range&);
		}

		THEN("Rolling six extra dice on the zero roll throws roll_infeasible_error"){
			// Trying to roll six extra 1s, 2s or 3s.
			REQUIRE_THROWS_AS(r1.die(0, 6), const roll_infeasible_error&);
			REQUIRE_THROWS_AS(r1.die(1, 6), const roll_infeasible_error&);
			REQUIRE_THROWS_AS(r1.die(2, 6), const roll_infeasible_error&);
			REQUIRE_THROWS_AS(r1.die(3, 6), const roll_infeasible_error&);
			REQUIRE_THROWS_AS(r1.die(4, 6), const roll_infeasible_error&);
			REQUIRE_THROWS_AS(r1.die(5, 6), const roll_infeasible_error&);
		}

		WHEN("Setting dice frequencies"){
			// Calling die for various valid positions. Expecting [200101]...
			r1.die(0, 2);
			r1.die(5, 1);
			r1.die(3, 1);

			THEN("Dice, norms and string rep must change accordingly") {
				require_roll_members(r1, {2, 0, 0, 1, 0, 1},
									 4, 6, 2, "[200101]");
			}

			WHEN("Copying altered roll (cctor) into a new roll r2"){
				Roll r2{r1};
				INFO("Roll r2 = ", r2);

				THEN("r1 must equal r2"){
					// Check equality for members after copy ctor";
					REQUIRE_EQ(r1, r2);
				}
			}

			WHEN("Increment-copying an altered roll r2"){
				// Validly ncrementing [200101] at position 3. Expecting [200201]
				Roll r2{r1,3};
				INFO("Roll r2 = ", r2);

				THEN("Dice, norms and string rep must change accordingly") {
					require_roll_members(r2, {2, 0, 0, 2, 0, 1},
										 5, 9, 2, "[200201]");
				}

				THEN("Rolling a die too many dice (> 5) on r2 throws roll_infeasible_error"){
					// Trying set the total amount of dice over 5.
					REQUIRE_THROWS_AS(r2.die(0, 3), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r2.die(1, 1), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r2.die(2, 1), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r2.die(3, 3), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r2.die(4, 1), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r2.die(5, 2), const roll_infeasible_error&);

					AND_THEN("Members are left unchanged"){
						require_roll_members(r2, {2, 0, 0, 2, 0, 1},
											 5, 9, 2, "[200201]");
					}
				}
			}

			WHEN("Increment-copying an altered roll r3"){
				// Validly ncrementing [200101] at position 4. Expecting [200111]
				Roll r3{r1,4};
				INFO("Roll r3 = ", r3);

				THEN("Dice, norms and string rep must change accordingly")
				require_roll_members(r3, {2,0,0,1,1,1},
									 5, 7, 2, "[200111]");

				THEN("Setting too many dice (> 5) on r3 throws roll_infeasible_error"){
					// Trying set the total amount of dice over 5.
					REQUIRE_THROWS_AS(r3.die(0, 3), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r3.die(1, 1), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r3.die(2, 1), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r3.die(3, 2), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r3.die(4, 2), const roll_infeasible_error&);
					REQUIRE_THROWS_AS(r3.die(5, 2), const roll_infeasible_error&);

					AND_THEN("Members are left unchanged"){
						require_roll_members(r3, {2,0,0,1,1,1},
											 5, 7, 2, "[200111]");
					}
				}
			}

		}
	}
}