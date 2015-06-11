#pragma once
#include "..\Private\Registry.h"
#include "..\Private\Algorithms.h"

#include <iostream>
#include <vector>


enum EAlgorithm
{
	SELECTIONSORT,
	INSERTSORT,
	BUBBLESORT,
	MERGESORT,
	QUICKSORT
};

/**
 * Interface class for Sortingalgorithms
 */
class ISortAlgorithm
{
public:
	//ISortAlgorithm(EAlgorithm ESort){}
	~ISortAlgorithm(){}

	/* Prepare Data, to perform algorithm steps */
	virtual void Initialize(vector<int> Input) = 0;

	/**
	* Instead of running an algorithm we run each algorithm stepwise, so
	* we can update the GUI Data after each step
	*/
	virtual const vector<vector<int>> Perform() = 0;

	/* Returns the Name of this Algorithm as string */
	virtual const std::string GetName() const = 0;

protected:
	/* The copy variable of the incoming input */
	vector<int> vObjects;
};

template <typename UserClass>
class AlgorithmModule
{
public:	
	~AlgorithmModule<UserClass>()
	{
		CallbackContainer->CleanUp();
		delete CallbackContainer;
	}

	/* Returns the Callback Container, iff registered*/
	static const AlgorithmCallbackContainer<UserClass>* GetCallbackContainer()
	{
		if(CallbackContainer)
		{
			return CallbackContainer;
		}

		/* no valid Callbackcontainer was found*/
		return nullptr;
	}

	/* Returns true, if any Delegates are registered, else false */
	static bool HasRegisteredCallbacks()
	{
		return bCallbacksRegistered;
	}

	// Registration of Delegates
	/** 
	 * Registers the Callbackfunction of the calling class
	 * @param: the pointer to the caller and its class
	 * @param: the Delegate which returns the indices in Array which will be compared
	 * @param: the Delegate which returns the indices in Array after a 'true' comparison
	 * @param: the Delegate which notifies the swap of indices in Array after a permutation
	 */
	static void RegisterDelegates(UserClass* CallingInstance, void(UserClass::*PreCompDel)(int, int), void(UserClass::*PostCompDel)(int, int), void(UserClass::*PostPermDel)(int,int))
	{
		CallbackContainer = new AlgorithmCallbackContainer<UserClass>(CallingInstance, PreCompDel, PostCompDel, PostPermDel);

		bCallbacksRegistered = true;
	}
	
	/* Unregisters Delegates */
	static void UnregisterDelegates()
	{
		CallbackContainer->CleanUp();
		delete CallbackContainer;

		bCallbacksRegistered = false;
	}

	// Sortalgorithm Factory
	static ISortAlgorithm* CreateSortInstanceOf(EAlgorithm AlgorithmEnum)
	{
		ISortAlgorithm* SortAlgorithm;
		switch (AlgorithmEnum)
		{
		case (EAlgorithm::INSERTSORT) :
			return SortAlgorithm = new Algorithms::InsertSort<UserClass>();			

		case (EAlgorithm::SELECTIONSORT) :
			return SortAlgorithm = new Algorithms::SelectionSort<UserClass>();			

		case (EAlgorithm::BUBBLESORT) :
			return SortAlgorithm = new Algorithms::BubbleSort<UserClass>();			

		case (EAlgorithm::MERGESORT) :
			return SortAlgorithm = new Algorithms::MergeSort<UserClass>();;

		case (EAlgorithm::QUICKSORT) :
			return SortAlgorithm = new Algorithms::QuickSort<UserClass>();;

		default :
			return SortAlgorithm = nullptr;
		}
		/*ISortAlgorithm* SortAlgorithm = new ISortAlgorithm(AlgorithmEnum);
		return SortAlgorithm;*/
	}

private:
	static AlgorithmCallbackContainer<UserClass>* CallbackContainer;

	static bool bCallbacksRegistered;
};

// Initialize static member
template <typename T >
AlgorithmCallbackContainer<T>* AlgorithmModule<T>::CallbackContainer = 0;
template <typename T >
bool AlgorithmModule<T>::bCallbacksRegistered = false;