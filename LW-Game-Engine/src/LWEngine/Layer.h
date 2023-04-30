#pragma once

#include "LWEngine/Core.h"
#include "LWEngine/Events/Event.h"

namespace LWEngine {
	
	class LWE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event){}
		
		//! Layers has no name normally. Just for debugging
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}


