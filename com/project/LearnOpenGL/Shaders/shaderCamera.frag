#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float faceAlpha;

void main()
{
  FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), faceAlpha);
    //FragColor = texture(texture1, TexCoord);
}