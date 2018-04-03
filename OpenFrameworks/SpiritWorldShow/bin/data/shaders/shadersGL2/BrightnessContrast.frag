#version 120

uniform sampler2DRect tex0;
uniform float brightness = 1.0;
uniform float contrast = 1.0;

varying vec2 texCoordVarying;

vec3 brightnessContrast(vec3 value, float brightness, float contrast)
{
    return (value - 0.5) * contrast + 0.5;
}

void main()
{
    vec4 texel0 = texture2DRect(tex0, texCoordVarying);
    //vec3 colorContrasted = (texel0.rgb) * contrast;

    vec3 color = brightnessContrast(texel0.rgb, brightness,contrast);
	gl_FragColor = vec4(color, texel0.a);
}