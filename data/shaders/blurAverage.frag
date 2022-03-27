#version 120

float step = 1.0;
uniform sampler2D texture;
uniform float width;
uniform float height;

vec3 sobel(float stepx, float stepy)
{
	vec4 tleft = texture2D(texture,gl_TexCoord[0].st + vec2(-stepx,stepy));
    vec4 left = texture2D(texture,gl_TexCoord[0].st + vec2(-stepx,0));
    vec4 bleft = texture2D(texture,gl_TexCoord[0].st + vec2(-stepx,-stepy));
    vec4 top = texture2D(texture,gl_TexCoord[0].st + vec2(0,stepy));
    vec4 mid = texture2D(texture,gl_TexCoord[0].st);
    vec4 bottom = texture2D(texture,gl_TexCoord[0].st + vec2(0,-stepy));
    vec4 tright = texture2D(texture,gl_TexCoord[0].st + vec2(stepx,stepy));
    vec4 right = texture2D(texture,gl_TexCoord[0].st + vec2(stepx,0));
    vec4 bright = texture2D(texture,gl_TexCoord[0].st + vec2(stepx,-stepy));

	vec4 sum = tleft + left + bleft + top + mid + bottom + tright + right + bright;
    vec4 blur = sum / 9.0;
    return vec3(blur.rgb);
}

void main()
{
	gl_FragColor = vec4((sobel(1.0 / width, 1.0 / height)), 1.0);
}