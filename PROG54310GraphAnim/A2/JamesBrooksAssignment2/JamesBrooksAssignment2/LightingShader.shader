#version 330


// Lighting

struct Light {

    vec3 colour;
    vec3 position;
    vec3 direction;

    float ambient_str;
    float specular_str;

    int specular_size;
};

uniform Light light[3];
uniform int num_lights_used;


// Camera location

uniform vec3 vec3_cam_pos;


// Object

in vec3 frag_position;
in vec3 vert_normal;
in vec4 frag_colour;


// Fragment output

out vec4 FragColour;


void main() {

    // Calculate lighting for fragment

    vec3 lightResult = vec3(0.0f, 0.0f, 0.0f);
    float lightsUsed = 0.0f;
    int i = 0;
    
    for (i = 0; i < num_lights_used && i < 3; i++) {

        // Ambient
        vec3 ambient = light[i].colour * light[i].ambient_str;

        // Diffuse
        vec3 norm = normalize(vert_normal);
        vec3 lightDir = normalize(light[i].position - frag_position);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * light[i].colour;

        // specular
        vec3 viewDir = normalize(vec3_cam_pos - frag_position);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), light[i].specular_size);
        vec3 specular = light[i].specular_str * spec * light[i].colour;

        lightResult = lightResult + (ambient + diffuse + specular);

        lightsUsed = lightsUsed + 1.0f;
    }

    // Default no lighting
    if (lightsUsed == 0) {

        lightResult = vec3(1.0f, 1.0f, 1.0f);
    }
    // Average out the lights used
    else {

        lightResult = lightResult / lightsUsed;
    }

    FragColour = frag_colour * vec4(lightResult, 1.0f);
}
