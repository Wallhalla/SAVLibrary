#pragma once

template <typename T>
class AlgorithmCallbackContainer
{
public:
	// Declaration of Delegates
	typedef void(T::*ElementsToCompareDelegate)(int index1, int index2);
	typedef void(T::*PostComparisonDelegate)(int index1, int index2);
	typedef void(T::*PostPermutationDelegate)();

	// ctor
	AlgorithmCallbackContainer<T>(T* Object, ElementsToCompareDelegate func1, PostComparisonDelegate func2, PostPermutationDelegate func3)
		: target_Object(Object)
		, target_FuncPreComparison(func1)
		, target_FuncPostComparison(func2)
		, target_FuncPostPermutation(func3)
	{}

	// Executables
	void Execute_PreComparison(int index1, int index2) const
	{
		(target_Object->*target_FuncPreComparison)(index1, index2);
	}
	void Execute_PostComparison(int index1, int index2) const
	{
		(target_Object->*target_FuncPostComparison)(index1, index2);
	}
	void Execute_PostPermutation() const
	{
		(target_Object->*target_FuncPostPermutation)();
	}

	void CleanUp()
	{
		target_Object = nullptr;
		target_FuncPreComparison = nullptr;
		target_FuncPostComparison = nullptr;
		target_FuncPostPermutation = nullptr;
	}

private:
	// The instance to call the delegated functions
	T* target_Object;

	/**
	* The Delegate which returns the indices in Array which will be compared
	* @param: the index which currently stores the iterator index
	* @param: the index which will be compared with iterator index next
	* * NOTE: You can be sure that after this call there will be a Comparison (Comp++)
	*/
	ElementsToCompareDelegate target_FuncPreComparison;

	/**
	* The Delegate which returns the indices in Array after comparison
	* @param: the index which currently stores the iterator index
	* @param: the index which currently stores the lowest value in array	
	*/
	PostComparisonDelegate target_FuncPostComparison;

	/**
	* The Delegate which notifies the swap of indices in Array after permutation
	* @see: latest output from PostComparisonDelegate
	* NOTE: Permutation++
	*/
	PostPermutationDelegate target_FuncPostPermutation;

};

