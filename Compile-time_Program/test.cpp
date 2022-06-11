#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;

constexpr int pow(int x, int n){
    int sum = 1;

    for (int i = 0; i < n; ++i){
        sum *= x;
    }

    return sum;
}

template <class... Targs>
constexpr int func(int x, const Targs& ...args)
{
    int Args[] {args...};
    int sum = 0, i = 0;

    for (auto &p: Args){
        sum += p * pow(x, i);
        ++i;
    }

    return sum;
}


TEST(TestName, SubTest_1){
	EXPECT_EQ(0, func(1));
}

class myTestFixture1: public ::testing::Test { 
public: 
	myTestFixture1() {} 

	bool moreThanZero(int num) { 
		return num > 0;
	}

	~myTestFixture1() {} 
};

TEST_F (myTestFixture1, SubTest_2) { 
   int i = 1, j = 0, k = 0, x = 0, y = 0;
   for (; i < 100; ++i){
   		j++;
   		k++;
   		x++;
   		y++;

   		EXPECT_EQ(moreThanZero(func(i, j, k, x, y)), 1);
   }
}

class myTestFixture2: public ::testing::Test { 
public: 
	myTestFixture2() {} 

	bool moreThanPrev(int num1, int num2) { 
		return num2 > num1;
	}

	~myTestFixture2() {}
};

TEST_F (myTestFixture2, SubTest_3) { 
   int i = 1, j = 1, k = 1, x = 1, y = 1;
   for (; i < 100; ++i){
   		j++;
   		k++;
   		x++;
   		y++;

   		EXPECT_EQ(moreThanPrev(func(i - 1, j - 1, k - 1, x - 1, y - 1), func(i, j, k, x, y)), 1);
   }
}

int main(int argc, char **argv){

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
