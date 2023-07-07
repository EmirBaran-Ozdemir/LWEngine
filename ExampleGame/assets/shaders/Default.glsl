#type vertex
#version 450 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec2 v_ScreenPos;			
out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	v_ScreenPos = gl_Position.xy;
}

#type fragment
#version 450 core
			
layout(location = 0) out vec4 color;
			
in vec2 v_TexCoord;
in vec2 v_ScreenPos;
in vec4 v_Color;
in float v_TexIndex;
in float v_TilingFactor;

uniform vec4 u_Color;
uniform float u_TilingFactor = 1.0f;
uniform sampler2D u_Textures[32];

void main()
{
	float dist = 1.0f - distance(v_ScreenPos * 0.8f, vec2(0.0f));
	dist = clamp(dist, 0.0f, 1.0f);
	dist = sqrt(dist);
	color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color ;
}