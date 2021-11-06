#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 OurColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

 void main()
 {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	OurColour = mix(vec4(aColor,0.0f),gl_Position, 0.05f);
 }
