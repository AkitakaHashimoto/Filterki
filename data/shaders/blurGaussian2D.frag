#version 330 core

#define MAX_KERNEL_SIZE 1280

uniform sampler2D texture;
// uniform int radius = 1;
uniform int radius;
uniform float width;
uniform float height;
uniform float kernel[MAX_KERNEL_SIZE];

vec3 gaussian(float stepx, float stepy)
{
    int kernelIdx = 0;
    vec4 sum = vec4(0,0,0,0);

    for (int row = -radius; row <= radius; row++)
    {
        for (int col = -radius; col <= radius; col++ )
        {
            vec4 colorTexel = texture2D(texture,gl_TexCoord[0].st + vec2(stepx * row,stepy * col));
            vec4 colorGaussian = colorTexel * kernel[kernelIdx];
            sum += colorGaussian;
            kernelIdx++;
        }
    }

    return vec3(sum.rgb);
}

void main() 
{
	gl_FragColor = vec4((gaussian(1.0 / width, 1.0 / height)), 1.0);
}