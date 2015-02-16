#include <gtest/gtest.h>
#include <rai/node.hpp>

#include <fstream>

TEST (landing, serialization)
{
	rai::landing_store store1 (0, 1, 2, 3);
	auto file (rai::unique_path ());
	{
		std::ofstream stream;
		stream.open (file.string ());
		ASSERT_FALSE (stream.fail ());
		store1.serialize (stream);
	}
	std::ifstream stream;
	stream.open (file.string ());
	ASSERT_FALSE (stream.fail ());
	bool error;
	rai::landing_store store2 (error, stream);
	ASSERT_FALSE (error);
	ASSERT_EQ (store1, store2);
}

TEST (landing, overwrite)
{
	rai::landing_store store1 (0, 1, 2, 3);
	auto file (rai::unique_path ());
	for (auto i (0); i < 10; ++i)
	{
		store1.last += i;
		{
			std::ofstream stream;
			stream.open (file.string ());
			ASSERT_FALSE (stream.fail ());
			store1.serialize (stream);
		}
		{
			std::ifstream stream;
			stream.open (file.string ());
			ASSERT_FALSE (stream.fail ());
			bool error;
			rai::landing_store store2 (error, stream);
			ASSERT_FALSE (error);
			ASSERT_EQ (store1, store2);
		}
	}
}

TEST (landing, start)
{
	rai::system system (24000, 1);
	
}