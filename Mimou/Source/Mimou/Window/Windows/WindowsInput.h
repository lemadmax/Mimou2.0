#pragma once
#include "Mimou/Input.h"

namespace Mimou
{
	class ME_API WindowsInput : public Input
	{
	public:
		virtual bool IsKeyPressed_Implement(INT32 KeyCode) override;

		virtual bool IsMouseButtonPressed_Implement(INT32 Button) override;
		virtual bool IsMouseButtonReleased_Implement(INT32 Button) override;
		virtual std::pair<float, float> GetMousePosition_Implement() override;
	};
}