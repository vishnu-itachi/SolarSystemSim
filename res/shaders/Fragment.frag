#version 430 core

precision mediump float;
in vec2 val;
out vec4 out_color;

// #define LINE_THICCNESS 2
// #define LINE_LENGTH 2000
// #define POINT_RADIUS 5

void main() { 
    // out_color = vec4(gl_FragCoord.xy/400, 0.0, 1.0);
	float R = 1.00; 
    // float R2 = 0.5; 
    // vec2 transformed = (gl_FragCoord.xy / 800) - 0.5;
    // float dist = sqrt(dot(transformed, transformed)) * 4;
    float dist = sqrt(dot(val, val));
    if (dist >= R) {
		discard;
	}
    float sm = smoothstep(R, R - 0.1, dist);
    float alpha = sm;
    
    // out_color = vec4(76.0 / 255, 114.0 / 255, 176.0 / 255, alpha);
    out_color = vec4(gl_FragCoord.xy/400, 0.0, alpha);
}
