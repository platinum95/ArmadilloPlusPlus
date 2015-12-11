#pragma once

class Mutex
{
private:
	void* Value;
	void* Saved;
	bool lock;
public:

	template<class Type>
	Mutex(Type t)
	{
		this->Value = (void *)t;
	}

	void Lock()
	{
		this->lock = true;
		this->Saved = this->Value;
	}

	void Unlock()
	{
		this->lock = false;
	}

	bool IsLocked()
	{
		return this->lock;
	}

	template<class ReturnType>
	ReturnType Get()
	{
		return this->lock ? (ReturnType)this->Saved : (ReturnType)this->Value;
	}

	template<class Type>
	bool Set(Type t)
	{
		if (!this->lock)
			this->Value = (void *)t;
		return this->lock;
	}
};
