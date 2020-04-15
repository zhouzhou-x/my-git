#include <stdio.h>
	if (numsSize > 1){
		void insretSort(int* nums, int numsSize){
			for (int i = 0; i < numsSize - 1; i++){
				int end = i;
				int key = nums[end + 1];
				while (end >= 0 && nums[end] > key){
					nums[end + 1] = nums[end];
					--end;
				}
				nums[end + 1] = key;
			}
		}
		int x = nums[0];
		for (int i = 1; i < numsSize; i++){
			if (x < nums[i]){
				x = nums[i];
				continue;
			}
			else{
				return true;
			}
		}
		return false;
	}
	else
		return false;
}