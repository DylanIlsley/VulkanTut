#version 330 core
out vec4 FragColor;

uniform vec3 lightColour = vec3(1.0f);
void main()
{
    FragColor = vec4(lightColour, 1.0f);  // set to colour of light so we can tell current colour
}