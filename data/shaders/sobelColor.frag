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
    vec4 bottom = texture2D(texture,gl_TexCoord[0].st + vec2(0,-stepy));
    vec4 tright = texture2D(texture,gl_TexCoord[0].st + vec2(stepx,stepy));
    vec4 right = texture2D(texture,gl_TexCoord[0].st + vec2(stepx,0));
    vec4 bright = texture2D(texture,gl_TexCoord[0].st + vec2(stepx,-stepy));

	vec4 x = tleft + 2.0*left + bleft - tright - 2.0*right - bright;
    vec4 y = -tleft - 2.0*top - tright + bleft + 2.0 * bottom + bright;
    vec4 sobel = sqrt((x * x) + (y * y));
    return vec3(sobel.rgb);
}

void main()
{
	gl_FragColor = vec4((sobel(1.0 / width, 1.0 / height)), 1.0);
}