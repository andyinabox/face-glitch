// important to note the difference between
// `sampler2DRect` here and `sampler2D` that you see
// in many examples: `sampler2D` uses normalized texture
// coordinates between 0.0 and 0.1; while `sampler2DRect`
// uses regular pixel coordinates
uniform sampler2DRect paint;
uniform sampler2DRect mask;

uniform int eraser;


void main()
{
    // get texture coordinates
    vec2 uv = gl_TexCoord[0].xy;

    // get color based on new coordinate
    vec4 paintColor = texture2DRect(paint, uv);
    vec4 maskColor = texture2DRect(mask, uv);

    vec4 color = maskColor;
    
    // set our color and alpha components
    if(eraser == 0) {
        color = maskColor + paintColor;
    } else {
        color = maskColor - paintColor;
    }

    // set frag color and use `blend` for alpha
	gl_FragColor = color;

}