#version 330 core

out vec4 FragColor; 

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float ratio;

void main(){
    FragColor = mix(texture(tex1, TexCoord), texture(tex2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}
