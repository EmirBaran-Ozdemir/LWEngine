#pragma once

#include "LWEngine/Core/Core.h"
#include "LWEngine/Events/Event.h"
#include "LWEngine/Core/Timestep.h"

namespace LWEngine {
	
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(Timestep ts){}
		virtual void OnImGuiRender(Timestep ts){}
		virtual void OnEvent(Event& event){}
		
		//! Layers has no name normally. Just for debugging
		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}
