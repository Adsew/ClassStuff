#version 330


// Lighting

struct Light {

    glm::vec3 colour;
    glm::vec3 position;
    glm::vec3 direction;

    float ambient_str;
    float specular_str;

    int specular_size;
};

uniform Light light[3];
uniform int num_lights_used;


// Object

in vec4 frag_colour;


// Fragment output

out vec4 FragColour;


void main() {

    // Calculate lighting for fragment
    vec3 ambient;
    //vec3 diffuse;
    //vec3 specular;
    vec3 lightResult = vec3(1.0f, 1.0f, 1.0f);
    int i = 0;
    
    for (i = 0; i < num_lights_used && i < 3; i++) {

        ambient = light[i].colour * light[i].ambient_str;

        if (i == 0) {

            lightResult = ambient;
        }
        else {

            lightResult = lightResult * ambient;
        }
    }

    FragColour = frag_colour * vec4(lightResult, 1.0f);
}
