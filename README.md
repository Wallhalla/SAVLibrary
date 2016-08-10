
# Project SAV (Sorting Algorithm Visualizer)

### Version: 1.1.0
### Publisher: Fabian Sonczeck, Germany

Written language: c++


# Table of Contents

1. Module Description
2. Installation    
3. Usage - Configuration options
4. Extension - How to extend the module with new Algorithms
	1. Things to know, what each Algorithm Class needs to do
	2. Add a new Algorithm
5. Reference




################################################################
# 1. Module Description
################################################################

This module gives the opportunity to run various sorting algorithms, regardless if they are implemented iterative or by a divide-conquer principle.
The special about this module is, that it can break within an algorithm and returns information to the user whats currently happening.
This gives the opportunity f.e. to a gui to visualize whats happening within the algorithm and running an algorithm stepwise.




################################################################
# 2. Installation
################################################################

There is no installation or anything needed for this module. The only things you need to do are the following:

- Add the 2 Folders "Private" and "Public" to your Project.
- In the File from where you want to use this module add the include line: #include "%ProjectPath%/Public/AlgorithmModule.h to your file.
- you don´t need to include the "Private" folder




################################################################
# 3. Usage
################################################################

In order to use the module within your code project, you need 3 steps to do:

<b>
STEP 1: Create an algorithm instance by doing...
</b>

<i>
NOTE: MyClass is not a part of the Module, it represents a class out of your own project, which wishes to use this module.
</i>

	class MyClass
	{
		//[...]

		// Get an Algorithm Instance
		ISortAlgorithm* myInstance = AlgorithmModule<MyClass>::CreateSortInstanceOf(EAlgorithm::(...)SORT);
	}


<b>
STEP 2: Give your algorithm instance a field it can sort. It expects a vector<int>
</b>

	myInstance->Initialize(myVector);


<b>
STEP 3: Let the algorithm run
</b>
	myInstance->Perform();

	NOTE: Perform() returns a vector<vector><int>>, so you can get the sorted vector if wished.


<b>
STEP 4 (optional) : Register function which fires within an algorithm
</b>	

	AlgorithmModule<MyClass>::RegisterDelegates(myClassInstance, &MyClass::Func1, &MyClass::Func2, &MyClass::Func3);
	

You can register 3 function with the following pattern:


## void Func1(int,int)

This function will fire when the next comparison is expected, 
it returns the 2 indices of the vector which will be compared next


## void Func2(int,int)

This function will fire after a comparison were performed,
it returns the 2 compared indices of the vector, where the second int param is the bigger one.


## void Func3(int,int)

This function notice the user that the int params aka indices were permutated.



* see 5. Reference for the enum entries

################################################################
# 4. Extension - How to extend the module
################################################################


To implement a new sorting algorithm you will need to open the Algorithms.h in the "Private" folder.


you can use the following template to copy into the file, and replace "MySortAlgorithm" with the name your Algorithm



	template <typename T>
	class MySortAlgorithm : public ISortAlgorithm
	{
	public:
		MySortAlgorithm <T>() {}
		~MySortAlgorithm <T>(){}
		
		// Interface
		virtual void Initialize(vector<int> Input) override
		{
			vObjects.clear();
			vObjects = Input;
		}


		virtual const vector<vector<int>> Perform() override
		{
			vector<vector<int>> Output;
			
			/**
 			 * paste your algorithm logic here
			 */
			
			return Output;
		}


		virtual const std::string GetName() const override
		{
			return "MySortAlgorithm ";
		}
		// END Interface
	}

- Prepare the algorithm, that it will add the sorted vector to the declared vector<vector<int>> Output

- Add the Callback calls to you algorithm logic, copy and paste the following inside your code and modify the index params to the iterators of
  your algorithm.


		// Callback before a comparison
		if (AlgorithmModule<T>::HasRegisteredCallbacks())
		{
			AlgorithmModule<T>::GetCallbackContainer()->Execute_PreComparison(i, j);
		}
					

		// Callback after comparison, the second index should have the greater value stored
		if (AlgorithmModule<T>::HasRegisteredCallbacks())
		{
			AlgorithmModule<T>::GetCallbackContainer()->Execute_PostComparison(i, j);
		}
				

		// Callback after a permutation
		if (AlgorithmModule<T>::HasRegisteredCallbacks())
		{
			AlgorithmModule<T>::GetCallbackContainer()->Execute_PostPermutation();
		}


- the last thing to do is, add your algorithm to the enum ESortAlgorithm inside AlgorithmModule.h

		


################################################################
# 5. Reference
################################################################


EAlgorithm currently has:

- SELECTIONSORT
- INSERTSORT
- BUBBLESORT
- MERGESORT
- QUICKSORT






### Date 2015-05-20, all rights reserved by Fabian Sonczeck