#version 430 core

precision mediump float;

void main(void)
{
    gl_Position = vec4(
        2 * (gl_VertexID / 2) - 1,
        2 * (gl_VertexID % 2) - 1,
        0.0,
        1.0);
}