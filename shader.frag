#version 150

const int number_of_targets = 360;

uniform float time;
uniform vec2 resolution;
uniform vec2 targets[number_of_targets];
uniform vec3 colors[number_of_targets];

out vec4 outputColor;

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
  vec3 color = vec3(0.937);
  for(int i = 0; i < number_of_targets; i++){

    vec2 t = vec2(targets[i].x, -targets[i].y) / min(resolution.x, resolution.y) * 2.0;
    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);

    float v = 0.008 / length(p - t);
	float r = v * colors[i].x;
	float g = v * colors[i].y;
	float b = v * colors[i].z;
    vec3 c = vec3(smoothstep(0.05, 1.0, r), smoothstep(0.05, 1.0, g), smoothstep(0.05, 1.0, b));
    color -= c;
  }

  outputColor = vec4(color, 1.0);
}