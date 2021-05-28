#include <iostream>

#include "include.h"
#include "../devan-yahtzee/src/objects/roll.h"

void logOK(){
	std::clog << " OK!" << '\n';
}

TEST_CASE("Roll Methods"){
	std::clog << "Creating zero-roll (default ctor). Expecting [000000]...";
	devan_yahtzee::objects::Roll r{};
	INFO("Roll r = ",r); logOK();

	REQUIRE_EQ(r.toString().compare("[000000]"),0);

	std::clog << "Checking all dice equal to 0... ";
	for(int i=0;i<6;i++){
		std::clog << i;
		REQUIRE_EQ(r.die(i), 0);
	}
	logOK();

	std::clog << "Checking norms initialization...";
	REQUIRE_EQ(r.oneNorm(), 0);
	REQUIRE_EQ(r.twoNorm(), 0);
	REQUIRE_EQ(r.infNorm(), 0);
	logOK();

	SUBCASE("Getting invalid die throws roll_position_out_of_range"){
		REQUIRE_THROWS_AS(r.die(6), const devan_yahtzee::objects::roll_position_out_of_range&);
		REQUIRE_THROWS_AS(r.die(7), const devan_yahtzee::objects::roll_position_out_of_range&);
		REQUIRE_THROWS_AS(r.die(8), const devan_yahtzee::objects::roll_position_out_of_range&);
	}

	SUBCASE("Setting dice frequencies"){
		std::clog << "Calling setDie for various valid positions. Expecting [200101]...";
		r.setDie(0, 2);
		r.setDie(5, 1);
		r.setDie(3,1);
		INFO("Changed r to ", r);
		REQUIRE_EQ(r.toString().compare("[200101]"), 0);
		logOK();

		std::clog << "Checking mutated dice and norms...";
		REQUIRE_EQ(r.die(0), 2);
		REQUIRE_EQ(r.die(5), 1);
		REQUIRE_EQ(r.die(3), 1);
		REQUIRE_EQ(r.oneNorm(), 4);
		REQUIRE_EQ(r.twoNorm(), 6);
		REQUIRE_EQ(r.infNorm(), 2);
		logOK();

		SUBCASE("Copy ctor"){
			std::clog << "check equality for members after copy";
			devan_yahtzee::objects::Roll r2{r};
			for(int i=0;i<6;i++)
				REQUIRE_EQ(r.die(i), r2.die(i));
			REQUIRE_EQ(r.oneNorm(), r2.oneNorm());
			REQUIRE_EQ(r.twoNorm(), r2.twoNorm());
			REQUIRE_EQ(r.infNorm(), r2.infNorm());
			logOK();
		}

		SUBCASE("Creating incremented roll from existing roll"){
			std::clog << "Validly ncrementing [200101] at position 3. Expecting [200201]...";
			devan_yahtzee::objects::Roll r2{r,3};
			REQUIRE_EQ(r2.toString().compare("[200201]"), 0);
			logOK();

			std::clog << "Checking mutated dice and norms...";
			REQUIRE_EQ(r2.die(3), 2);
			REQUIRE_EQ(r2.oneNorm(), 5);
			REQUIRE_EQ(r2.twoNorm(), 9);
			REQUIRE_EQ(r2.infNorm(), 2);
			logOK();

			std::clog << "Validly ncrementing [200101] at position 4. Expecting [200111]...";
			devan_yahtzee::objects::Roll r3{r,4};
			REQUIRE_EQ(r3.toString().compare("[200111]"), 0);
			logOK();

			std::clog << "Checking mutated dice and norms...";
			REQUIRE_EQ(r3.die(4), 1);
			REQUIRE_EQ(r3.oneNorm(), 5);
			REQUIRE_EQ(r3.twoNorm(), 7);
			REQUIRE_EQ(r3.infNorm(), 2);
			logOK();
		}

	}
}