uniform sampler2D texture;
uniform float frameId;
uniform float numberFrames;

void main()
{
	vec4 texCoord = gl_TexCoord[0];
	texCoord.x += frameId / numberFrames;
	
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, texCoord.xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}
