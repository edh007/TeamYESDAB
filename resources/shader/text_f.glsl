#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 ParticleColor;

uniform sampler2D texture_particle;

void main()
{    
	vec4 temp = vec4(1.0, 1.0, 1.0, texture(texture_particle, TexCoords).r);
	temp = ParticleColor * temp;
	if(temp.a < 0.1)
		discard;
    FragColor = temp;
}