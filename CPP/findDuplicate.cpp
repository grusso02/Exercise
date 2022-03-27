// Given an array "nums" containing n + 1 integers where each
// integers is between 1 and n (inclusive)
// prove that at least one duplicate number exist

// Floyd's tortoise and hare

#include <iostream>

int	findDuplicate(int nums[]) {

	int	tortoise = nums[0];		// 1
	int	hare = nums[0];			// 1

	while (true) {
		tortoise = nums[tortoise];	// 3 - 4
		hare = nums[nums[hare]];	// 4 - 4
		if (tortoise == hare)
			break;
	}

	int ptr1 = nums[0];		// 1
	int ptr2 = tortoise;	// 4
	while (ptr1 != ptr2) {
		ptr1 = nums[ptr1];	// 3
		ptr2 = nums[ptr2];	// 3
	}

	return ptr1;
}

int main()
{
	int arr[] = {1, 3, 6, 4, 3, 7};

	std::cout << findDuplicate(arr) << std::endl;

	return 0;
}
