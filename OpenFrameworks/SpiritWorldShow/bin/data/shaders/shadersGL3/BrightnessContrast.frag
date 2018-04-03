#version 150

uniform sampler2DRect tex0;
uniform float brightness = 1.0;
uniform float contrast = 1.0;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec4 texel0 = texture(tex0, texCoordVarying);
    vec3 color = brightnessContrast(texel0.rgb, brightness,contrast);

    gl_FragColor = vec4(texel0.rgb, texel0.a * texel1.a);
}