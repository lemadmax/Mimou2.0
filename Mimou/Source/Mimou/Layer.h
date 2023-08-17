#pragma once
#include "Mimou/Core.h"
#include "Mimou/Event/EventBase.h"
#include "Mimou/Timestep.h"

namespace Mimou
{
	class ME_API Layer
	{
	public:
		Layer(const std::string& DebugName = "Layer")
			: m_DebugName(DebugName) {}
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep Ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(EventBase& Event) {}

	protected:
		std::string m_DebugName;
	};
}