#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 aColor;
uniform float alpha;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 vertexColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = vec4(aColor, alpha);
}
