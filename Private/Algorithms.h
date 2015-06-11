#pragma once
#include "../Public/AlgorithmModule.h"

#include <vector>

using namespace std;

/**
* Class Collection of Sortingalgorithms
*/
namespace Algorithms
{
	// =============================================
	// ====== Primitive Iterative Algorithms =======
	// =============================================

	template <typename T>
	class SelectionSort : public ISortAlgorithm
	{
	public:
		SelectionSort<T>() /*: ISortAlgorithm(EAlgorithm::SELECTIONSORT)*/ {}
		~SelectionSort<T>(){}
		
		// Interface
		virtual void Initialize(vector<int> Input) override
		{
			vObjects.clear();
			vObjects = Input;
		}
		virtual const vector<int>* Perform() override
		{
			vector<int>* Output;

			if (vObjects.empty())
			{
				return Output;
			}
			
			// Copied from: http://codereview.stackexchange.com/questions/4582/sorting-algorithms-implemented-in-c
			int length = vObjects.size();

			for (int i = 0; i < length; ++i)
			{
				// inits min as the first index in vector 
				int min = i;

				// look for an index which has a smaller one than min´s index
				for (int j = i + 1; j < length; ++j)
				{

					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(i, j);
					}

					// check for a smaller value in array
					if (vObjects[j] < vObjects[min])
					{
						min = j;
					}

					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(i, min);
					}
				}

				if (min != i)
				{
					// switch places if the indices differ						
					int temp = vObjects[i];
					vObjects[i] = vObjects[min];
					vObjects[min] = temp;

					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
					}
				}
			}

			// add modified array to list
			Output.push_back(vObjects);

			// return list
			return Output;
		}
		virtual const std::string GetName() const override
		{
			return "SelectionSort";
		}
		// END Interface		
	};

	template <typename T>
	class InsertSort : public ISortAlgorithm
	{
	public:
		InsertSort<T>() /*: ISortAlgorithm(EAlgorithm::INSERTSORT)*/{}
		~InsertSort<T>(){}

		// Interface
		virtual void Initialize(vector<int> Input) override
		{
			vObjects.clear();

			vObjects = Input;
		}
		virtual const vector<vector<int>> Perform() override
		{
			vector<vector<int>> Output;
			if (vObjects.empty())
			{
				return Output;
			}

			// Copied from: http://codereview.stackexchange.com/questions/4582/sorting-algorithms-implemented-in-c
			int length = vObjects.size();

			for (int i = 1; i < length; ++i)
			{
				bool inplace = true;
				int j = 0;
				for (; j < i; ++j)
				{
					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(i, j);
					}

					if (vObjects[i] < vObjects[j])
					{
						// Callback!
						if (AlgorithmModule<T>::HasRegisteredCallbacks())
						{
							AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(i, j);
						}

						inplace = false;
						break;
					}
				}

				if (!inplace)
				{
					int save = vObjects[i];
					for (int k = i; k > j; --k)
					{
						vObjects[k] = vObjects[k - 1];

						// Callback!
						if (AlgorithmModule<T>::HasRegisteredCallbacks())
						{
							AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
						}
					}
					vObjects[j] = save;
				}
			}

			// add modified array to list
			Output.push_back(vObjects);

			return Output;
		}
		virtual const std::string GetName() const override
		{
			return "InsertSort";
		}
		// END Interface
	};

	template <typename T>
	class BubbleSort : public ISortAlgorithm
	{
	public:
		BubbleSort<T>() /*: ISortAlgorithm(EAlgorithm::BUBBLESORT)*/{}
		~BubbleSort<T>(){}

		// Interface
		virtual void Initialize(vector<int> Input) override
		{
			vObjects.clear();
			vObjects = Input;
		}
		virtual const vector<vector<int>> Perform() override
		{
			vector<vector<int>> Output;
			if (vObjects.empty())
			{
				return Output;
			}

			// Copied from: http://codereview.stackexchange.com/questions/4582/sorting-algorithms-implemented-in-c
			int length = vObjects.size();

			for (int i = 0; i < length; ++i)
			{
				bool swapped = false;
				for (int j = 0; j < length - (i + 1); ++j)
				{
					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(j, j + 1);
					}

					if (vObjects[j] > vObjects[j + 1])
					{
						// Callback!
						if (AlgorithmModule<T>::HasRegisteredCallbacks())
						{
							AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(j, j + 1);
						}
						
						//vector<int>::swap(vObjects, j, j + 1);

						//swap
						int temp = vObjects[j];
						vObjects[j] = vObjects[j+1];
						vObjects[j+1] = j;

						// Callback!
						if (AlgorithmModule<T>::HasRegisteredCallbacks())
						{
							AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
						}

						swapped = true;
					}
				}

				if (!swapped) break;
			}

			// add modified array to list
			Output.push_back(vObjects);

			return Output;
		}
		virtual const std::string GetName() const override
		{
			return "BubbleSort";
		}
		// END Interface
	};

	// =============================================
	// ====== Divide and Conquer Algorithms ========
	// =============================================
		
	template <typename T>
	class QuickSort : public ISortAlgorithm
	{
	public:
		QuickSort<T>() /*: ISortAlgorithm(EAlgorithm::QUICKSORT)*/{}
		~QuickSort<T>(){}

		// Interface
		virtual void Initialize(vector<int> Input) override
		{
			vObjects.clear();
			vObjects = Input;			
		}
		virtual const vector<vector<int>> Perform() override
		{
			int lastIndex = vObjects.size() - 1;
			quickSort(vObjects, 0, lastIndex);

			vector<vector<int>> Output;
			// add modified array to list
			Output.push_back(vObjects);
			// return list
			return Output;
		}
		virtual const std::string GetName() const override
		{
			return "QuickSort";
		}
		// END Interface
	
	private:

		// copied from: http://stackoverflow.com/questions/3640544/visual-studio-keyboard-shortcut-to-display-intellisense modified with vector
		void quickSort(vector<int>& arr, int left, int right)
		{
			int i = left, j = right;
			int tmp;
			int pivot = arr[(left + right) / 2];

			/* partition */
			while (i <= j)
			{
				while (arr[i] < pivot)
				{					
					i++;
				}

				while (arr[j] > pivot)
				{
					j--;
				}
				
				// Callback!
				if (AlgorithmModule<T>::HasRegisteredCallbacks())
				{
					AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(i, j);
				}

				if (i <= j)
				{
					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(i, j);
					}

					tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					i++;
					j--;

					// Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
					}
				}
			};

			/* recursion */
			if (left < j)
			{
				quickSort(arr, left, j);
			}

			if (i < right)
			{
				quickSort(arr, i, right);
			}
		}
	};

	template <typename T>
	class MergeSort : public ISortAlgorithm
	{
	public:
		MergeSort<T>() /*: ISortAlgorithm(EAlgorithm::MERGESORT)*/{}
		~MergeSort<T>(){}

		// Interface
		virtual void Initialize(vector<int> Input) override
		{
			vObjects.clear();
			vObjects = Input;

			ArraySize = vObjects.size();
		}
		virtual const vector<vector<int>> Perform() override
		{			
			merge_sort(vObjects, ArraySize);
			
			vector<vector<int>> Output;

			// add modified array to list
			Output.push_back(vObjects);

			// return list
			return Output;			
		}
		virtual const std::string GetName() const override
		{
			return "MergeSort";
		}
		// END Interface

		
	private:
		int ArraySize = 0;
		// '@' symbolize own comments

		// Copied from: http://stackoverflow.com/questions/18141065/merge-sort-implementation modified to vector
		void merge_sort(vector<int>& SubList, int size)
		{
			vector<int> temp;
			int mid;

			// @ no division of array, iff array only has one element left
			if (size < 2) 
			{
				return;
			}
			else 
			{
				// @ divide array with in two halfs
				mid = size / 2;
				vector<int> Sub1;
				vector<int> Sub2;

				for (int i = 0; i < mid; i++)
				{
					Sub1.push_back(SubList[i]);
				}

				for (int i = 0; i + mid < size; i++)
				{
					Sub2.push_back(SubList[mid + i]);
				}
				// @ repeat division with 2 sub arrays, one with 0 - mid elements, ...
				merge_sort(Sub1, mid);
				
				// @ ... one with with size - mid elements
				merge_sort(Sub2, size - mid);

				// @ no further division possible, merge the sub arrays and 
				merge(Sub1, mid, Sub2, size - mid, temp);
			}
			
			SubList.clear();
			for (int i = 0; i < size; i++)
			{
				SubList.push_back(temp[i]);
			}
		}

		// Copied from: http://stackoverflow.com/questions/18141065/merge-sort-implementation
		/** 
		 * @ list1 and list2 are two sublists defined through the division earlier, 
		 *   list3 is a temp array which will be the merged list of list1 and list2
		 */
		int merge(vector<int> list1, int size1, vector<int> list2, int size2, vector<int>& list3)
		{
			int i1, i2;

			// @ return, iff the addition of two arrays would be greater than original size
			if (size1 + size2 > ArraySize) {
				return 0;
			}

			i1 = 0; i2 = 0; 
			/* while both lists are non-empty */
			while (i1 < size1 && i2 < size2) 
			{
				// @ Callback!
				if (AlgorithmModule<T>::HasRegisteredCallbacks())
				{
					AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(i1, i2);
				}

				if (list1[i1] < list2[i2]) 
				{
					list3.push_back(list1[i1]);
					i1++;
					// @ Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(i1, i2);
					}

					// @ Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
					}
				}
				else 
				{
					list3.push_back(list2[i2]);
					i2++;
					// @ Callback!
					if (AlgorithmModule<T>::HasRegisteredCallbacks())
					{
						AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(-1, i2);
					}
				}

			
			}
			while (i1 < size1) 
			{
				/* copy remainder of list1 */
				list3.push_back(list1[i1]);
				i1++;

				// @ Callback!
				if (AlgorithmModule<T>::HasRegisteredCallbacks())
				{
					AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
				}
			}
			while (i2 < size2) 
			{
				/* copy remainder of list2 */
				list3.push_back(list2[i2]);
				i2++;

				// @ Callback!
				if (AlgorithmModule<T>::HasRegisteredCallbacks())
				{
					AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
				}
			}	

			return 1;
		}		
	};
}

/*

copy paste the callback calls

// Callback!
if (AlgorithmModule<T>::HasRegisteredCallbacks())
{
AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(i, j);
}

// Callback!
if (AlgorithmModule<T>::HasRegisteredCallbacks())
{
AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(i, min);
}

// Callback!
if (AlgorithmModule<T>::HasRegisteredCallbacks())
{
AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
}
*/