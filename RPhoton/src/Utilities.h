#ifndef ZJR_UTILITIES
#define ZJR_UTILITIES

namespace Memory
{
	template<typename T>
	inline void safeDelete(T *t)
	{
		if(t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	template<typename T>
	inline void safeDeleteArray(T *t)
	{
		if(t != nullptr)
		{
			delete[] t;
			t = nullptr;
		}
	}

	template<typename T>
	inline void safeRelease(T *t)
	{
		if(t != nullptr)
		{
			t->Release();
			t = nullptr;
		}
	}
}

#endif
