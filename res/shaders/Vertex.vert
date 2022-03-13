#version 430 core

// in vec4 position;

precision mediump float;
in vec2 value;
in vec4 vertex;
out vec2 val;

// void main(void)
// {
//     // gl_Position = vec4(
//     //     2 * (gl_VertexID / 2) - 1,
//     //     2 * (gl_VertexID % 2) - 1,
//     //     0.0,
//     //     1.0);
//     gl_Position = position;
//     // gl_Position = gl_Vertex;
    
// }


// uniform mat4 viewMatrix; 
// uniform mat4 projectionMatrix;

void main() { 
    val = value;
    // gl_Position = projectionMatrix*viewMatrix*vertex; 
    gl_Position = vertex; 
}
