#include <iostream>
#include <string>
#include <cmath>

// For overloading  stream operators such as <<
#include <glm/gtx/string_cast.hpp>

// For glm math operations
#include <glm\glm.hpp>

#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;
using namespace std;


void printMatrix(mat4 &M) {

    const float *ptr = (const float *)glm::value_ptr(M);
    int i = 0, j = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j = j + 4) {

            cout << ptr[i+j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{
	/*vec2 first = vec2(-1.0f, -0.1f);
	vec2 second = vec2(0.1f, 1.0f);

	float dotproduct = dot(first, second);

	cout << "the dot product of " 
        << to_string(first) << " and " 
        << to_string(second) << " is : " 
	    << dotproduct << endl;*/

    int i = 0;

    vec3 v[5];

    v[0] = vec3(0.89, 0.65, 0.12);
    v[1] = vec3(-0.19, 0.32, -0.19);
    v[2] = vec3(0.39, -0.61, 0.88);
    v[3] = vec3(-0.9, 0.61, -0.31);
    v[4] = vec3(0.45, -0.71, 0.06);

    float vMag[5];
    vec3 vAng[5];

    for (i = 0; i < 5; i++) {

        vMag[i] = glm::length(v[i]);
        vAng[i] = glm::atan(glm::normalize(v[i])) * (180.0f / 3.14f);
    }

    vec3 vx3[5];
    vec3 vxNeg3[5];
    float vx3Mag[5];
    float vxNeg3Mag[5];
    vec3 vx3Ang[5];
    vec3 vxNeg3Ang[5];

    for (i = 0; i < 5; i++) {

        vx3[i] = v[i] * 3.0f;
        vx3Mag[i] = glm::length(vx3[i]);
        vx3Ang[i] = glm::atan(glm::normalize(vx3[i]))  * (180.0f / 3.14f);

        vxNeg3[i] = v[i] * -3.0f;
        vxNeg3Mag[i] = glm::length(vxNeg3[i]);
        vxNeg3Ang[i] = glm::atan(glm::normalize(vxNeg3[i]))  * (180.0f / 3.14f);
    }

    for (i = 0; i < 5; i++) {

        cout << "Vector: V" << i + 1 << " " << v[i].x << "," << v[i].y << "," << v[i].z << " Mag: " << vMag[i] << "\n";
        cout << "Angle:  V" << i + 1 << " " << vAng[i].x << "," << vAng[i].y << "," << vAng[i].z << "\n\n";

        cout << "Vector: 3V" << i + 1 << " " << vx3[i].x << "," << vx3[i].y << "," << vx3[i].z << " Mag: " << vx3Mag[i] << "\n";
        cout << "Angle:  3V" << i + 1 << " " << vx3Ang[i].x << "," << vx3Ang[i].y << "," << vx3Ang[i].z << "\n\n";
        
        cout << "Vector: -3V" << i + 1 << " " << vxNeg3[i].x << "," << vxNeg3[i].y << "," << vxNeg3[i].z << " Mag: " << vxNeg3Mag[i] << "\n";
        cout << "Angle:  -3V" << i + 1 << " " << vxNeg3Ang[i].x << "," << vxNeg3Ang[i].y << "," << vxNeg3Ang[i].z << "\n\n";

        cout << "----------------------\n\n";
    }

    float dotProd[5];
    vec3 crossProd[5];

    for (i = 0; i < 4; i++) {

        dotProd[i] = glm::dot(v[i], v[i + 1]);
        crossProd[i] = glm::cross(v[i], v[i + 1]);
    }
    dotProd[4] = glm::dot(v[4], v[0]);
    crossProd[4] = glm::cross(v[4], v[0]);

    for (i = 0; i < 5; i++) {

        cout << "Dot of V" << i + 1 << ".V" << i + 2 << ": " << dotProd[i] << "\n";
        cout << "Cross of V" << i + 1 << "XV" << i + 2 << ": " << crossProd[i].x << ", " << crossProd[i].y << ", " << crossProd[i].z << "\n";
    }

    vec3 v1proj2 = glm::normalize(v[0]) * glm::dot(glm::normalize(v[0]), v[1]);

    cout << "\nV1 projected onto V2: " << v1proj2.x << ", " << v1proj2.y << ", " << v1proj2.z << "\n\n\n\n";

    mat4 M1(1.0f);
    vec3 xAxis(1, 0, 0);
    vec3 yAxis(0, 1, 0);
    vec3 zAxis(0, 0, 1);

    printMatrix(M1);

    // Rotate then translate
    cout << "Task 1: Rotate first\n\n";

    mat4 M2 = glm::rotate(M1, 30.0f, xAxis);
    M2 = glm::rotate(M2, 12.0f, yAxis);
    M2 = glm::rotate(M2, 45.0f, zAxis);

    printMatrix(M2);

    cout << "Task 2&3: Translate after rotation\n\n";

    vec3 trans1(10.0f, 18.0f, -7.0f);

    M2 = glm::translate(M2, trans1);

    printMatrix(M2);

    // Translate then rotate
    cout << "Task 2&3: Translate first\n\n";

    M2 = glm::translate(M1, trans1);
    
    printMatrix(M2);

    cout << "Task 2&3: Rotate after translation\n\n";

    M2 = glm::rotate(M2, 30.0f, xAxis);
    M2 = glm::rotate(M2, 12.0f, yAxis);
    M2 = glm::rotate(M2, 45.0f, zAxis);

    printMatrix(M2);

    cout << "Task 4: Scale matrix by 3\n\n";

    vec3 scale3(3.0f, 3.0f, 3.0f);

    M2 = glm::scale(M1, scale3);

    printMatrix(M2);

    return 0;
}
