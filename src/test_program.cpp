#include <test_program.hpp>
#include <darwin_connection.hpp>
#include <HDS.hpp>

int main()
{
	HDS hds = HDS("/dev/ttyUSB0");

	hds.init();
	
	hds.shouldersUp();
	hds.elbowsUp();

	for (size_t i = 0; i < 5; i++)
	{
		hds.shouldersInward();
		hds.shouldersOutward();
	}

	hds.elbowsDown();
	hds.shouldersDown();

	return 0;
}
