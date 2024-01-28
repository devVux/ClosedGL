@vertex
#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
	gl_Position = uProj * uView * uModel * vec4(aPosition, 1.0);
	vColor = aColor;
}

@fragment
#version 410 core

out vec4 fragColor;

in vec3 vColor;

void main() {
	fragColor = vec4(vColor, 1.0);
}