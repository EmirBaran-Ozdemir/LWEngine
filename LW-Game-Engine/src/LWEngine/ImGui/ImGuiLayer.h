#pragma once

#include "LWEngine/Core/Layer.h"
#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/Events/KeyEvent.h"
#include "LWEngine/Events/MouseEvent.h"

namespace LWEngine {

	class LWE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender(Timestep ts) override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}