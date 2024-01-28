@vertex
#version 410 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextCoords;
layout(location = 3) in float aTextUnit;

out vec4 vColor;
out vec2 vTextCoords;
out float vTextUnit;

uniform mat4 uProj;
uniform mat4 uView;

void main() {
    gl_Position = uProj * uView * vec4(aPosition, 0.0, 1.0);
    vColor = vec4(aColor, 1.0);
    vTextCoords = aTextCoords;
    vTextUnit = aTextUnit;
}


@fragment
#version 410 core

layout(location = 0) out vec4 fragColor;

in vec4 vColor;
in vec2 vTextCoords;
in float vTextUnit;

uniform sampler2D uTextures[32];

void main() {
    int index = int(vTextUnit);
    fragColor = texture(uTextures[index], vTextCoords) * vColor;
    //fragColor = vec4(vTextUnit, vTextUnit, vTextUnit, 1.0);
}