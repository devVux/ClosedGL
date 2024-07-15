@vertex
#version 450 core
#extension GL_ARB_bindless_texture: require

layout(location = 0) in mat4 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextCoords;
layout(location = 3) in float aTextIndex;

out vec4 vColor;
out vec2 vTextCoords;
flat out int vTextIndex;

uniform mat4 uProj;
uniform mat4 uView;

void main() {
    gl_Position = uProj * uView * vec4(aPosition, 0.0, 1.0);
    vColor = vec4(aColor, 1.0);
    vTextCoords = aTextCoords;
    vTextIndex = int(aTextIndex);
}


@fragment
#version 450 core
#extension GL_ARB_bindless_texture: require
#extension GL_NV_uniform_buffer_std430_layout: enable

layout(location = 0) out vec4 fragColor;

in vec4 vColor;
in vec2 vTextCoords;
flat in int vTextIndex;

layout(binding = 6, std430) readonly buffer ssbo3 {
    sampler2D textures[];
};

void main() {
    //fragColor = vec4(vTextIndex, vTextIndex, vTextIndex, 1.0); 
    fragColor = texture(textures[vTextIndex], vTextCoords) * vColor;
}