// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    mat3 ret;
	vec3 normAxis = normalize(axis);
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
	// YOUR CODE FOR HW1 HERE
	//mat3 tensorProduct = axis * transpose(axis);
	mat3 rotationMatrix = mat3(cos(degrees) + normAxis[0] * normAxis[0] * (1 - cos(degrees)),
		normAxis[0] * normAxis[1] * (1 - cos(degrees)) + normAxis[2] * sin(degrees),
		normAxis[0] * normAxis[2] * (1 - cos(degrees)) - normAxis[1] * sin(degrees),

		normAxis[0] * normAxis[1] * (1 - cos(degrees)) - normAxis[2] * sin(degrees),
		cos(degrees) + normAxis[1] * normAxis[1] * (1 - cos(degrees)),
		normAxis[1] * normAxis[2] * (1 - cos(degrees)) + normAxis[0] * sin(degrees),

		normAxis[0] * normAxis[2] * (1 - cos(degrees)) + normAxis[1] * sin(degrees),
		normAxis[1] * normAxis[2] * (1 - cos(degrees)) - normAxis[0] * sin(degrees),
		cos(degrees) + normAxis[2] * normAxis[2] * (1 - cos(degrees)));
	mat3 rotationMatrix2 = mat3(cos(degrees)/* + axis[0]*axis[0]*(1 - cos(degrees))*/,
		/*axis[0] * axis[1] * (1 - cos(degrees)) + */normAxis[2] * sin(degrees),
		/*axis[0] * axis[2] * (1 - cos(degrees))*/ -normAxis[1] * sin(degrees),

		/*axis[0] * axis[1] * (1 - cos(degrees))*/ -normAxis[2] * sin(degrees),
		cos(degrees)/* + axis[1] * axis[1] * (1 - cos(degrees))*/,
		/*axis[1] * axis[2] * (1 - cos(degrees)) + */normAxis[0] * sin(degrees),

		/*axis[0] * axis[2] * (1 - cos(degrees)) + */normAxis[1] * sin(degrees),
		/*axis[1] * axis[2] * (1 - cos(degrees))*/ -normAxis[0] * sin(degrees),
		cos(degrees) /*+ axis[2] * axis[2] * (1 - cos(degrees))*/);
	mat3 rotationMatrix3 = mat3(/*cos(degrees) + */axis[0] * axis[0] * (1 - cos(degrees)),
		axis[0] * axis[1] * (1 - cos(degrees)) + axis[2] * sin(degrees),
		axis[0] * axis[2] * (1 - cos(degrees)) - axis[1] * sin(degrees),

		axis[0] * axis[1] * (1 - cos(degrees)) - axis[2] * sin(degrees),
		/*cos(degrees) + */axis[1] * axis[1] * (1 - cos(degrees)),
		axis[1] * axis[2] * (1 - cos(degrees)) + axis[0] * sin(degrees),

		axis[0] * axis[2] * (1 - cos(degrees)) + axis[1] * sin(degrees),
		axis[1] * axis[2] * (1 - cos(degrees)) - axis[0] * sin(degrees),
		/*cos(degrees) + */axis[2] * axis[2] * (1 - cos(degrees)));
	// You will change this return call


	return rotationMatrix;// rotationMatrix2;
    return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
	vec3 upLookCrossProduct = normalize(glm::cross(eye, up));
	vec3 betterUp = normalize(glm::cross(upLookCrossProduct, eye));
	up = betterUp;
	//degrees *= -1;
	double oldx = eye[0];
	double oldy = eye[1];
	double oldz = eye[2];
	//this section underneath is good ol' George original, and matches the Rodrigues equation
	//eye[0] = cos(degrees * pi / 180.0) * oldx + sin(degrees * pi / 180.0) * upLookCrossProduct[0];
	//eye[1] = cos(degrees * pi / 180.0) * oldy + sin(degrees * pi / 180.0) * upLookCrossProduct[1];
	//eye[2] = cos(degrees * pi / 180.0) * oldz + sin(degrees * pi / 180.0) * upLookCrossProduct[2]; //oldz;

	eye = rotate(degrees * pi / 180.0, betterUp) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
	double oldx = eye[0];
	double oldy = eye[1];
	double oldz = eye[2];
	double oldUpX = up[0];
	double oldUpY = up[1];
	double oldUpZ = up[2];

	//this commented out section below is beautiful George original code that WORKS
	//eye[0] = cos(degrees * pi / 180.0) * oldx + sin(degrees * pi / 180.0) * oldUpX * 7;
	//eye[1] = cos(degrees * pi / 180.0) * oldy + sin(degrees * pi / 180.0) * oldUpY * 7;//7 * sin(counter2 * pi / 180.0);
	//eye[2] = cos(degrees * pi / 180.0) * oldz + sin(degrees * pi / 180.0) * oldUpZ * 7;//7 * cos(counter2 * pi / 180.0);
	//up = normalize(up - ((dot(eye, up) / (dot(eye, eye)) * eye)));
	vec3 oldEye = vec3(eye[0], eye[1], eye[2]);
	eye = rotate(degrees * pi / 180.0, normalize(cross(eye, up))) * eye;
	up = rotate(degrees * pi / 180.0, normalize(cross(oldEye, up))) * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
	vec3 Wvector = normalize(eye - center);
	vec3 Uvector = normalize(cross(up, Wvector));
	vec3 Vvector = cross(Wvector, Uvector);
	//vec3 translationVector 

	mat4 lookAtMatrix = mat4(Uvector[0], Vvector[0], Wvector[0], 0,
		Uvector[1], Vvector[1], Wvector[1], 0,
		Uvector[2], Vvector[2], Wvector[2], 0,
		-eye[0] * Uvector[0] - eye[1] * Uvector[1] - eye[2] * Uvector[2], -eye[0] * Vvector[0] - eye[1] * Vvector[1] - eye[2] * Vvector[2], -eye[0] * Wvector[0] - eye[1] * Wvector[1] - eye[2] * Wvector[2], 1
	);
	// You will change this return call
	return lookAtMatrix;
    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret( (cos(fovy/2.0f * (pi / 180.0)) / sin(fovy / 2.0f * (pi / 180.0))) /aspect,0,0,0,
		0, cos(fovy / 2.0f * (pi / 180.0)) / sin(fovy / 2.0f * (pi / 180.0)),0,0,
		0,0,  -(zFar + zNear)/ (zFar - zNear), -1.0,
		0,0,-(2.0f * zFar * zNear)/ (zFar - zNear),0);
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    //mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
	mat4 ret = mat4(
		sx,0,0,0,
		0,sy,0,0,
		0,0,sz,0,
		0,0,0,1
	);

    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
	ret = mat4(
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	tx,ty,tz,1
	);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
