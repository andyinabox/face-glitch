// important to note the difference between
// `sampler2DRect` here and `sampler2D` that you see
// in many examples: `sampler2D` uses normalized texture
// coordinates between 0.0 and 0.1; while `sampler2DRect`
// uses regular pixel coordinates
uniform sampler2DRect tex0;
uniform sampler2DRect mask;

uniform float width;
uniform float height;
uniform float pixel_w;
uniform float pixel_h;

uniform float blend;


void main()
{
    // get texture coordinates
    vec2 uv = gl_TexCoord[0].xy;

    // this is what you would use to find `dx`/`dy` for
    // normalized texture coordinates
    // float dx = pixel_w * (1./width);
    // float dy = pixel_h * (1./height);
    
    // since our texture coordinates are not normalized
    // and simply in pixel values, this part is pretty easy
    float dx = pixel_w;
    float dy = pixel_h;
    
    // get the updated texture coordinates.
    vec2 coord = vec2(
        (floor(uv.x/dx) * dx) + dx/2.,
        (floor(uv.y/dy) * dy) + dy/2.
    );
    
    // get color based on new coordinate
    vec4 maskColor = texture2DRect(mask, uv);
    vec4 color = texture2DRect(tex0, coord);

    // set frag color and use `blend` for alpha
	gl_FragColor = vec4(color.rgb, maskColor.a*blend);
//	gl_FragColor = vec4(color.rgb, blend);

}