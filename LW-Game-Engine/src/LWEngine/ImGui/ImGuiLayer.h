#pragma once

#include "LWEngine/Core/Layer.h"
#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/Events/KeyEvent.h"
#include "LWEngine/Events/MouseEvent.h"

namespace LWEngine {

	enum class FontFamily : int
	{
		None = 0,
		OpenSans = 0,
		PlusJakarta = 5,
		Roboto = 9,
	};

	enum class FontWeight : int
	{
		None = 0,
		Light = 0,
		Regular = 1,
		Bold = 2,
		Italic = 3,
	};

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
		static int GetFont(FontFamily family, FontWeight weight) { return static_cast<int>(family) + static_cast<int>(weight); }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}