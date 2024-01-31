#include <gtest/gtest.h>

#include "ClosedGL/Core/Timestep.h"

#include <thread>

using namespace std::chrono_literals;

//TEST(TestGTest, Ok) {
//	Clock clock;
//	clock.reset();
//	std::this_thread::sleep_for(1s);
//	std::cout << clock.tick() << std::endl;
//}

TEST(ClockTests, True) {
	
	Clock clock;
	clock.reset();
	
	std::this_thread::sleep_for(1s);

	std::cout << "Start: \t\t" << clock.startTime() << "s\n";
	std::cout << "Elapsed:\t" << clock.elapsedTime() << "\n";
	std::cout << "Tick: \t\t" << clock.tick() << "\n";

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}