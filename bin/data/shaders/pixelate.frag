// important to note the difference between
// `sampler2DRect` here and `sampler2D` that you see
// in many examples: `sampler2D` uses normalized texture
// coordinates between 0.0 and 0.1; while `sampler2DRect`
// uses regular pixel coordinates
uniform sampler2DRect src;
uniform sampler2DRect mask;

uniform float width;
uniform float height;
uniform float t;

uniform float pixel_w;
uniform float pixel_h;

uniform int animation;
uniform float animSpeed;

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


    float x_pos = dx/2.;
    float y_pos = dy/2.;
    
//    float th = mod(t, 1000.);
    if(animation == 1) {
        x_pos = sin(t/animSpeed)*dx/2. + x_pos;
        y_pos = cos(t/animSpeed)*dy/2. + y_pos;
    }

    
    // get the updated texture coordinates.
    vec2 coord = vec2(
        (floor(uv.x/dx) * dx) + x_pos,
        (floor(uv.y/dy) * dy) + y_pos
    );
    
    // get color based on new coordinate
    vec4 srcColor = texture2DRect(src, uv);
    vec4 pixColor = texture2DRect(src, coord);
    vec4 maskColor = texture2DRect(mask, coord);

    // set our color and alpha components
    vec3 color = mix(srcColor, pixColor, blend).rgb;
    float alpha = maskColor.a;

    // set frag color and use `blend` for alpha
	gl_FragColor = vec4(color, alpha);

}