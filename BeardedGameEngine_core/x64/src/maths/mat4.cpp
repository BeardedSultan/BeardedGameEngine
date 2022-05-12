#include "mat4.h"

namespace beardedGameEngine { namespace maths {

	mat4::mat4()
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
	}

	mat4::mat4(float diagonal) 
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
		elements[0 + 0 * 4] = diagonal; //row + col * 4
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}
	
	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}

	mat4& mat4::multiply(const mat4& other) 
	{
		float data[16];

		for (int row = 0; row < 4; row++) 
		{
			for (int col = 0; col < 4; col++) 
			{
				float sum = 0.0f;
				for (int elem = 0; elem < 4; elem++) 
				{
					sum += elements[col + elem * 4] * other.elements[elem + row * 4];
				}
				data[col + row * 4] = sum;
			}
		}

		memcpy(elements, data, 4 * 4 * sizeof(float));

		return *this;
	}
	
	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}
	
	mat4& mat4::operator*=(const mat4& other)
	{
		return multiply(other);
	}

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 ortho;
		for (int i = 0; i < 4 * 4; i++) {
			ortho.elements[i] = 0.0f;
		}

		//diagonal
		ortho.elements[0 + 0 * 4] = 2 / (right - left); //row + col * 4
		ortho.elements[1 + 1 * 4] = 2 / (top - bottom);
		ortho.elements[2 + 2 * 4] = -2 / (near - far);
		ortho.elements[3 + 3 * 4] = 1.0f;

		//last col
		ortho.elements[0 + 3 * 4] = (left + right) / (left - right);
		ortho.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		ortho.elements[2 + 3 * 4] = (far + near) / (far - near);

		return ortho;
	}

	mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4 perspective(1.0f);

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;
		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		//diagonal
		perspective.elements[0 + 0 * 4] = a; //row + col * 4
		perspective.elements[1 + 1 * 4] = q;
		perspective.elements[2 + 2 * 4] = b;
		//perspective.elements[3 + 3 * 4] = 0.0f;
		
		perspective.elements[3 + 2 * 4] = -1.0f;
		perspective.elements[2 + 3 * 4] = c;

		return perspective;
	}
	
	mat4 mat4::translation(const vec3& translation)
	{
		mat4 result(1.0f);
		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;
		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis)
	{
		mat4 result(1.0f);
		
		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	mat4 mat4::scale(const vec3& scale)
	{
		mat4 result(1.0f);
		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;
		return result;
	}

	std::ostream& operator<<(std::ostream& stream, const mat4& matrix)
	{

		for (int row = 0; row < 4; row++) 
		{
			stream << "[ ";
			for (int col = 0; col < 4; col++) 
			{
				stream << matrix.elements[row + col * 4] << " ";
			}
			stream << "]" << std::endl;
		}
		
		return stream;
	}

} }