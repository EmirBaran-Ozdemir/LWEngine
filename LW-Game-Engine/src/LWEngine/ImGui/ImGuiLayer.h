#pragma once

#include "LWEngine/Core/Layer.h"
#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/Events/KeyEvent.h"
#include "LWEngine/Events/MouseEvent.h"

namespace LWEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		virtual void OnImGuiRender(Timestep ts) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}
