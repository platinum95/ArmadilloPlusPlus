#pragma once

class IDisposable
{
public:
	virtual void Dispose() = 0;

	virtual ~IDisposable() { }
};