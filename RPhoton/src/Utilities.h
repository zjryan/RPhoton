#ifndef ZJR_UTILITIES
#define ZJR_UTILITIES

namespace Memory
{
	template<typename T>
	inline void SafeDelete(T *t)
	{
		if(t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	template<typename T>
	inline void SafeDeleteArray(T *t)
	{
		if(t != nullptr)
		{
			delete[] t;
			t = nullptr;
		}
	}

	template<typename T>
	inline void SafeRelease(T *t)
	{
		if(t != nullptr)
		{
			t->Release();
			t = nullptr;
		}
	}
}

#endif
