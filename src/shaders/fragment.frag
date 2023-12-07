#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTexCoord;

out vec4 screenColor;

uniform sampler2D material; // 0
uniform sampler2D mask;     // 1

void main()
{
    vec3 baseColor = texture(material, fragmentTexCoord).rgb;
    float alpha = texture(mask, fragmentTexCoord).r;
    screenColor = vec4(baseColor, alpha);
}
