@vertex
#version 450 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

out vec4 vColor;

uniform mat4 uProj;
uniform mat4 uView;

void main() {
    gl_Position = uProj * uView * vec4(aPosition, 0.0, 1.0);
    vColor = vec4(aColor, 1.0);
}


@fragment
#version 450 core

layout(location = 0) out vec4 fragColor;

in vec4 vColor;

void main() {
    fragColor = vColor;
}