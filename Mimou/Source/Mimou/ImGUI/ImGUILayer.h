#pragma once
#include "Mimou/Layer.h"

#include "Mimou/Event/EventBase.h"

namespace Mimou
{
	class ME_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer() : Layer("ImGUILayer") {}
		~ImGUILayer() {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(EventBase& Event) override;
		virtual void OnImGUIRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.f;
		bool m_EventBlocked = false;
	};
}