#version 120

float step = 1.0;
uniform sampler2D texture;
uniform float width;
uniform float height;

float grayScale(vec4 color)
{
	return (color.r + color.g + color.b) / 3;
}

vec3 sobel(float stepx, float stepy)
{
	float tleft = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(-stepx,stepy)));
    float left = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(-stepx,0)));
    float bleft = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(-stepx,-stepy)));
    float top = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(0,stepy)));
    float bottom = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(0,-stepy)));
    float tright = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(stepx,stepy)));
    float right = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(stepx,0)));
    float bright = grayScale(texture2D(texture,gl_TexCoord[0].st + vec2(stepx,-stepy)));

	float x = tleft + 2.0*left + bleft - tright - 2.0*right - bright;
    float y = -tleft - 2.0*top - tright + bleft + 2.0 * bottom + bright;
    float sobel = sqrt((x * x) + (y * y));
    return vec3(sobel, sobel, sobel);
}

void main()
{
	gl_FragColor = vec4((sobel(1.0 / width, 1.0 / height)), 1.0);
}