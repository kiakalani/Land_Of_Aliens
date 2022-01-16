// Illumination using the physically-based model

#version 130

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec3 light_pos;
in vec2 uv_interp;

// General constants
float pi = 3.1415926535897932;

// Material attributes (constants)

// Blue plastic
vec3 diffuse_color = vec3(0.0, 0.0, 0.5);
vec3 specular_color = vec3(0.1, 0.1, 0.1);
vec3 ambient_color = vec3(0.0, 0.0, 0.0);

float roughness = 0.5;
float light_intensity = 1.0*pi;

uniform sampler2D texture_map;


void main() 
{
    // Physically-based shading model

    vec3 N, // Interpolated normal for fragment
         L, // Light-source direction
         V, // View direction
         H; // Half-way vector

    // Initialize input quantities
    N = normalize(normal_interp);

    L = (light_pos - position_interp);
    L = normalize(L);

    // V = (eye_position - position_interp);
    V = - position_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

    //H = 0.5*(V + L); // Halfway vector
    H = (V + L); // Halfway vector
    H = normalize(H);

    // Compute useful quantities
    float NH = max(dot(N, H), 0.0);
    float LH = max(dot(L, H), 0.0);
    float NL = max(dot(N, L), 0.0);

    // Compute shading model
    // Diffuse term (subsurface scattering)
    vec3 diffuse = diffuse_color / pi;

    // Microfacet geometry
    // Fresnel term
    vec3 pixel = texture(texture_map, uv_interp).xyz;
    vec3 fresnel = pixel + (vec3(1.0, 1.0, 1.0) - pixel)*pow(1 - LH, 5.0);
    // GGX distribution function
    float denom = NH*NH*(roughness*roughness - 1.0) + 1.0;
    float ndist = roughness / (pi*denom*denom);
    // Microfacet term: assume implicit geometry function
    vec3 mfacet = fresnel * (ndist / 4.0);

    // Full illumination
    vec3 illum = pixel * 0.5 + (diffuse + mfacet)*light_intensity*NL;

    // Assign illumination to the fragment
    gl_FragColor = vec4(illum, 1.0);
}