uniform sampler2D texture;
uniform float frameId;

void main()
{
	gl_TexCoord[0].x += frameId * 0.25;
	
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}