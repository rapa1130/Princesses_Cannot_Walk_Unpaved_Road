#pragma once
namespace Bisang
{
	class IPickable
	{
		virtual void PutOn() = 0;
		virtual void PutDown() = 0;
	};
}