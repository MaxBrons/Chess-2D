#version 450 core

out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()							
{
	vec4 texColor = texture(u_Texture, v_TexCoord);						
	o_Color = texColor;				
}