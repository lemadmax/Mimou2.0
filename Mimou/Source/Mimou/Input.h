#pragma once
#include "mepch.h"
#include "Core.h"
#include "Event/KeyCodes.h"
#include "Event/MouseButtonCodes.h"

namespace Mimou
{
	class ME_API Input
	{
	public:
		inline static bool IsKeyPressed(INT32 KeyCode) { return s_Instance->bInputEnabled && s_Instance->IsKeyPressed_Implement(KeyCode); }
		inline static bool IsMouseButtonPressed(INT32 Button) { return s_Instance->bInputEnabled && s_Instance->IsMouseButtonPressed_Implement(Button); }
		inline static bool IsMouseButtonReleased(INT32 Button) { return s_Instance->bInputEnabled && s_Instance->IsMouseButtonReleased_Implement(Button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePosition_Implement(); }

		inline static void EnableInput(bool bEnabled) { s_Instance->EnableInput_Implement(bEnabled); }

	protected:
		virtual bool IsKeyPressed_Implement(INT32 KeyCode) = 0;
		virtual bool IsMouseButtonPressed_Implement(INT32 Button) = 0;
		virtual bool IsMouseButtonReleased_Implement(INT32 Button) = 0;
		virtual std::pair<float, float> GetMousePosition_Implement() = 0;

		void EnableInput_Implement(bool bEnabled) { bInputEnabled = bEnabled; }
		
	private:
		static Input* s_Instance;

	public:
		bool bInputEnabled = true;
	};
}