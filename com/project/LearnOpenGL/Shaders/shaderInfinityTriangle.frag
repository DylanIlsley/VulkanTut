#version 330 core
out vec4 FragColor;

in vec4 OurColour;

uniform float faceAlpha;

void main()
{
  FragColor = OurColour;
    //FragColor = texture(texture1, TexCoord);
}