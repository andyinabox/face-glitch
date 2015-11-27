uniform sampler2DRect tex0;

uniform float blend;

void main()
{
    vec4 color = texture2DRect(tex0, gl_TexCoord[0].xy);
    
    vec3 inverted = vec3(1.0) - color.rgb;

//	gl_FragColor = vec4(inverted, color.a);
	gl_FragColor = vec4(inverted, blend);
}