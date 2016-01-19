#pragma once

#include <cmath>
#include <vector>

#define MATH_PI 3.14159265358979323846f
#define ToRadian(x) (float)(((x) * MATH_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / MATH_PI))

namespace Math
{
	inline void Swap(float& a, float& b)
	{
		float temp = a;
		a = b;
		b = temp;
	}

	struct Vector2f
	{
		union
		{
			struct
			{
				float x;
				float y;
			};

			struct
			{
				float r;
				float g;
			};

			struct
			{
				float Value[2];
			};
		};

		Vector2f()
		{
			Value[0] = 0.0f;
			Value[1] = 0.0f;
		}

		Vector2f(float value)
		{
			Value[0] = value;
			Value[1] = value;
		}

		Vector2f(float x, float y)
		{
			Value[0] = x;
			Value[1] = y;
		}

		float& operator[](unsigned int index)
		{
			return Value[index];
		}

		float* GetValue()
		{
			return Value;
		}
	};

	struct Vector3f
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			struct
			{
				float r;
				float g;
				float b;
			};

			struct
			{
				float Value[3];
			};
		};

		Vector3f()
		{
			Value[0] = 0.0f;
			Value[1] = 0.0f;
			Value[2] = 0.0f;
		}

		Vector3f(float value)
		{
			Value[0] = value;
			Value[1] = value;
			Value[2] = value;
		}

		Vector3f(float x, float y, float z)
		{
			Value[0] = x;
			Value[1] = y;
			Value[2] = z;
		}

		Vector3f(Vector2f a, float z)
		{
			Value[0] = a[0];
			Value[1] = a[1];
			Value[2] = z;
		}

		float& operator[](unsigned int index)
		{
			return Value[index];
		}

		float* GetValue()
		{
			return Value;
		}

		float* Get()
		{
			return Value;
		}
	};

	struct Vector4f
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			struct
			{
				float r;
				float g;
				float b;
				float a;
			};

			struct
			{
				float Value[4];
			};
		};

		Vector4f()
		{
			Value[0] = 0.0f;
			Value[1] = 0.0f;
			Value[2] = 0.0f;
			Value[3] = 0.0f;
		}

		Vector4f(float value)
		{
			Value[0] = value;
			Value[1] = value;
			Value[2] = value;
			Value[3] = value;
		}

		Vector4f(Vector3f a, float b)
		{
			Value[0] = a[0];
			Value[1] = a[1];
			Value[2] = a[2];
			Value[3] = b;
		}

		Vector4f(float x, float y, float z, float w)
		{
			Value[0] = x;
			Value[1] = y;
			Value[2] = z;
			Value[3] = w;
		}

		float& operator[](unsigned int index)
		{
			return Value[index];
		}

		float* GetValue()
		{
			return Value;
		}

		float* Get()
		{
			return Value;
		}
	};

	struct Matrix33f
	{
		union
		{
			struct
			{
				float Value[9];
			};

			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			};
		};

		Matrix33f()
		{
			m00 = m11 = m22 = 1.0f;
			m01 = m02 = 0.0f;
			m10 = m12 = 0.0f;
			m20 = m21 = 0.0f;
		}

		Matrix33f(float value)
		{
			m00 = m01 = m02 = value;
			m10 = m11 = m12 = value;
			m20 = m21 = m22 = value;
		}

		Matrix33f(float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22)
		{
			this->m00 = m00;
			this->m01 = m01;
			this->m02 = m02;

			this->m10 = m10;
			this->m11 = m11;
			this->m12 = m12;

			this->m20 = m20;
			this->m21 = m21;
			this->m22 = m22;
		}

		float& operator[](unsigned int index)
		{
			return Value[index];
		}

		const float* GetMatrix()
		{
			return Value;
		}

		const float* Get()
		{
			return Value;
		}
	};

	struct Matrix44f
	{
		union
		{
			struct
			{
				float Value[16];
			};

			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			struct
			{
				Vector4f Columns[4];
			};
		};

		Matrix44f()
		{
			m00 = m11 = m22 = m33 = 1.0f;
			m01 = m02 = m03 = 0.0f;
			m10 = m12 = m13 = 0.0f;
			m20 = m21 = m23 = 0.0f;
			m30 = m31 = m32 = 0.0f;
		}

		Matrix44f(float value)
		{
			m00 = m01 = m02 = m03 = value;
			m10 = m11 = m12 = m13 = value;
			m20 = m21 = m22 = m23 = value;
			m30 = m31 = m32 = m33 = value;
		}

		Matrix44f(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			this->m00 = m00;
			this->m01 = m01;
			this->m02 = m02;
			this->m03 = m03;

			this->m10 = m10;
			this->m11 = m11;
			this->m12 = m12;
			this->m13 = m13;

			this->m20 = m20;
			this->m21 = m21;
			this->m22 = m22;
			this->m23 = m23;

			this->m30 = m30;
			this->m31 = m31;
			this->m32 = m32;
			this->m33 = m33;
		}

		float &operator[](int index)
		{
			return Value[index];
		}

		const float* GetMatrix()
		{
			return Value;
		}

		const float* Get()
		{
			return Value;
		}

		const float* GetTranspose()
		{
			float* Value = this->Value;

			Swap(Value[1], Value[4]);
			Swap(Value[2], Value[8]);
			Swap(Value[3], Value[12]);
			Swap(Value[6], Value[9]);
			Swap(Value[7], Value[13]);
			Swap(Value[11], Value[14]);

			return Value;
		}
	};

#pragma region OPERATOR

	// Equal - Vector
	inline bool operator !=(Vector2f a, Vector2f b)
	{
		return (a.x != b.x || a.y != b.y);
	}

	inline bool operator !=(Vector3f a, Vector3f b)
	{
		return (a.x != b.x || a.y != b.y || a.z != b.z);
	}

	inline bool operator !=(Vector4f a, Vector4f b)
	{
		return (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
	}

	// Add - Vector
	inline Vector2f operator+(Vector2f a, Vector2f b)
	{
		return Vector2f(a[0] + b[0], a[1] + b[1]);
	}

	inline Vector2f operator+(Vector2f a, float b)
	{
		return Vector2f(a[0] + b, a[1] + b);
	}

	inline Vector3f operator+(Vector3f a, Vector3f b)
	{
		return Vector3f(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
	}

	inline Vector3f operator+(Vector3f a, float b)
	{
		return Vector3f(a[0] + b, a[1] + b, a[2] + b);
	}

	inline Vector4f operator+(Vector4f a, Vector4f b)
	{
		return Vector4f(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
	}

	inline Vector4f operator+(Vector4f a, float b)
	{
		return Vector4f(a[0] + b, a[1] + b, a[2] + b, a[3] + b);
	}

	// Add - Vector
	inline void operator+=(Vector2f& a, Vector2f b)
	{
		a = Vector2f(a[0] + b[0], a[1] + b[1]);
	}

	inline void operator+=(Vector2f& a, float b)
	{
		a = Vector2f(a[0] + b, a[1] + b);
	}

	inline void operator+=(Vector3f& a, Vector3f b)
	{
		a = Vector3f(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
	}

	inline void operator+=(Vector3f& a, float b)
	{
		a = Vector3f(a[0] + b, a[1] + b, a[2] + b);
	}

	inline void operator+=(Vector4f& a, Vector4f b)
	{
		a = Vector4f(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
	}

	inline void operator+=(Vector4f& a, float b)
	{
		a = Vector4f(a[0] + b, a[1] + b, a[2] + b, a[3] + b);
	}

	// Add - Matrix
	inline Matrix33f operator+(Matrix33f a, Matrix33f b)
	{
		return Matrix33f(a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02,
			a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12,
			a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22);
	}

	inline Matrix33f operator+(Matrix33f a, float b)
	{
		return Matrix33f(a.m00 + b, a.m01 + b, a.m02 + b,
			a.m10 + b, a.m11 + b, a.m12 + b,
			a.m20 + b, a.m21 + b, a.m22 + b);
	}

	inline Matrix44f operator+(Matrix44f a, Matrix44f b)
	{
		return Matrix44f(a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
			a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
			a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
			a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33);
	}

	inline Matrix44f operator+(Matrix44f a, float b)
	{
		return Matrix44f(a.m00 + b, a.m01 + b, a.m02 + b, a.m03 + b,
			a.m10 + b, a.m11 + b, a.m12 + b, a.m13 + b,
			a.m20 + b, a.m21 + b, a.m22 + b, a.m23 + b,
			a.m30 + b, a.m31 + b, a.m32 + b, a.m33 + b);
	}

	// Add - Matrix
	inline void operator+=(Matrix33f& a, Matrix33f b)
	{
		a = Matrix33f(a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02,
			a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12,
			a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22);
	}

	inline void operator+=(Matrix33f& a, float b)
	{
		a = Matrix33f(a.m00 + b, a.m01 + b, a.m02 + b,
			a.m10 + b, a.m11 + b, a.m12 + b,
			a.m20 + b, a.m21 + b, a.m22 + b);
	}

	inline void operator+=(Matrix44f& a, Matrix44f b)
	{
		a = Matrix44f(a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
			a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
			a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
			a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33);
	}

	inline void operator+=(Matrix44f& a, float b)
	{
		a = Matrix44f(a.m00 + b, a.m01 + b, a.m02 + b, a.m03 + b,
			a.m10 + b, a.m11 + b, a.m12 + b, a.m13 + b,
			a.m20 + b, a.m21 + b, a.m22 + b, a.m23 + b,
			a.m30 + b, a.m31 + b, a.m32 + b, a.m33 + b);
	}

	// Sub - Vector
	inline Vector2f operator-(Vector2f a, Vector2f b)
	{
		return Vector2f(a[0] - b[0], a[1] - b[1]);
	}

	inline Vector2f operator-(Vector2f a, float b)
	{
		return Vector2f(a[0] - b, a[1] - b);
	}

	inline Vector3f operator-(Vector3f a, Vector3f b)
	{
		return Vector3f(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
	}

	inline Vector3f operator-(Vector3f a, float b)
	{
		return Vector3f(a[0] - b, a[1] - b, a[2] - b);
	}

	inline Vector4f operator-(Vector4f a, Vector4f b)
	{
		return Vector4f(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
	}

	inline Vector4f operator-(Vector4f a, float b)
	{
		return Vector4f(a[0] - b, a[1] - b, a[2] - b, a[3] - b);
	}

	// Sub - Vector
	inline void operator-=(Vector2f& a, Vector2f b)
	{
		a = Vector2f(a[0] - b[0], a[1] - b[1]);
	}

	inline void operator-=(Vector2f& a, float b)
	{
		a = Vector2f(a[0] - b, a[1] - b);
	}

	inline void operator-=(Vector3f& a, Vector3f b)
	{
		a = Vector3f(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
	}

	inline void operator-=(Vector3f& a, float b)
	{
		a = Vector3f(a[0] - b, a[1] - b, a[2] - b);
	}

	inline void operator-=(Vector4f& a, Vector4f b)
	{
		a = Vector4f(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
	}

	inline void operator-=(Vector4f& a, float b)
	{
		a = Vector4f(a[0] - b, a[1] - b, a[2] - b, a[3] - b);
	}

	// Sub - Matrix
	inline Matrix33f operator-(Matrix33f a, Matrix33f b)
	{
		return Matrix33f(a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02,
			a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12,
			a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22);
	}

	inline Matrix33f operator-(Matrix33f a, float b)
	{
		return Matrix33f(a.m00 - b, a.m01 - b, a.m02 - b,
			a.m10 - b, a.m11 - b, a.m12 - b,
			a.m20 - b, a.m21 - b, a.m22 - b);
	}

	inline Matrix44f operator-(Matrix44f a, Matrix44f b)
	{
		return Matrix44f(a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
			a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
			a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
			a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33);
	}

	inline Matrix44f operator-(Matrix44f a, float b)
	{
		return Matrix44f(a.m00 - b, a.m01 - b, a.m02 - b, a.m03 - b,
			a.m10 - b, a.m11 - b, a.m12 - b, a.m13 - b,
			a.m20 - b, a.m21 - b, a.m22 - b, a.m23 - b,
			a.m30 - b, a.m31 - b, a.m32 - b, a.m33 - b);
	}

	// Sub - Matrix
	inline void operator-=(Matrix33f& a, Matrix33f b)
	{
		a = Matrix33f(a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02,
			a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12,
			a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22);
	}

	inline void operator-=(Matrix33f& a, float b)
	{
		a = Matrix33f(a.m00 - b, a.m01 - b, a.m02 - b,
			a.m10 - b, a.m11 - b, a.m12 - b,
			a.m20 - b, a.m21 - b, a.m22 - b);
	}

	inline void operator-=(Matrix44f& a, Matrix44f b)
	{
		a = Matrix44f(a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
			a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
			a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
			a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33);
	}

	inline void operator-=(Matrix44f& a, float b)
	{
		a = Matrix44f(a.m00 - b, a.m01 - b, a.m02 - b, a.m03 - b,
			a.m10 - b, a.m11 - b, a.m12 - b, a.m13 - b,
			a.m20 - b, a.m21 - b, a.m22 - b, a.m23 - b,
			a.m30 - b, a.m31 - b, a.m32 - b, a.m33 - b);
	}

	// Negative - Vector
	inline Vector2f operator-(Vector2f a)
	{
		return Vector2f(-a.x, -a.y);
	}

	inline Vector3f operator-(Vector3f a)
	{
		return Vector3f(-a.x, -a.y, -a.z);
	}

	inline Vector4f operator-(Vector4f a)
	{
		return Vector4f(-a.x, -a.y, -a.z, -a.w);
	}

	// Negative - Matrix
	inline Matrix33f operator-(Matrix33f a)
	{
		return Matrix33f(
			-a.m00, -a.m01, -a.m02,
			-a.m10, -a.m11, -a.m12,
			-a.m20, -a.m21, -a.m22);
	}

	inline Matrix44f operator-(Matrix44f a)
	{
		return Matrix44f(
			-a.m00, -a.m01, -a.m02, -a.m03,
			-a.m10, -a.m11, -a.m12, -a.m13,
			-a.m20, -a.m21, -a.m22, -a.m23,
			-a.m30, -a.m31, -a.m32, -a.m33);
	}

	// Multi - Vector
	inline Vector2f operator*(Vector2f a, Vector2f b)
	{
		return Vector2f(a[0] * b[0], a[1] * b[1]);
	}

	inline Vector2f operator*(Vector2f a, float b)
	{
		return Vector2f(a[0] * b, a[1] * b);
	}

	inline Vector3f operator*(Vector3f a, Vector3f b)
	{
		return Vector3f(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
	}

	inline Vector3f operator*(Vector3f a, float b)
	{
		return Vector3f(a[0] * b, a[1] * b, a[2] * b);
	}

	inline Vector4f operator*(Vector4f a, Vector4f b)
	{
		return Vector4f(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
	}

	inline Vector4f operator*(Vector4f a, float b)
	{
		return Vector4f(a[0] * b, a[1] * b, a[2] * b, a[3] * b);
	}

	// Multi - Vector
	inline void operator*=(Vector2f& a, Vector2f b)
	{
		a = Vector2f(a[0] * b[0], a[1] * b[1]);
	}

	inline void operator*=(Vector2f& a, float b)
	{
		a = Vector2f(a[0] * b, a[1] * b);
	}

	inline void operator*=(Vector3f& a, Vector3f b)
	{
		a = Vector3f(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
	}

	inline void operator*=(Vector3f& a, float b)
	{
		a = Vector3f(a[0] * b, a[1] * b, a[2] * b);
	}

	inline void operator*=(Vector4f& a, Vector4f b)
	{
		a = Vector4f(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
	}

	inline void operator*=(Vector4f& a, float b)
	{
		a = Vector4f(a[0] * b, a[1] * b, a[2] * b, a[3] * b);
	}

	// Multi - Matrix
	inline Matrix33f operator*(Matrix33f a, Matrix33f b)
	{
		return Matrix33f(
			a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20,
			a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21,
			a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,

			a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20,
			a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21,
			a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,

			a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20,
			a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21,
			a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22);
	}

	inline Matrix33f operator*(Matrix33f a, float b)
	{
		return Matrix33f(
			a.m00 * b, a.m01 * b, a.m02 * b,
			a.m10 * b, a.m11 * b, a.m12 * b,
			a.m20 * b, a.m21 * b, a.m22 * b);
	}

	inline Matrix44f operator*(Matrix44f a, Matrix44f b)
	{
		return Matrix44f(
			a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30,
			a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31,
			a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32,
			a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,

			a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30,
			a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
			a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
			a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,

			a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30,
			a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
			a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
			a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,

			a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30,
			a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
			a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
			a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33);
	}

	inline Matrix44f operator*(Matrix44f a, float b)
	{
		return Matrix44f(
			a.m00 * b, a.m01 * b, a.m02 * b, a.m03 * b,
			a.m10 * b, a.m11 * b, a.m12 * b, a.m13 * b,
			a.m20 * b, a.m21 * b, a.m22 * b, a.m23 * b,
			a.m30 * b, a.m31 * b, a.m32 * b, a.m33 * b);
	}

	// Multi - Matrix
	inline void operator*=(Matrix33f& a, Matrix33f b)
	{
		a = Matrix33f(
			a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20,
			a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21,
			a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,

			a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20,
			a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21,
			a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,

			a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20,
			a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21,
			a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22);
	}

	inline void operator*=(Matrix33f& a, float b)
	{
		a = Matrix33f(
			a.m00 * b, a.m01 * b, a.m02 * b,
			a.m10 * b, a.m11 * b, a.m12 * b,
			a.m20 * b, a.m21 * b, a.m22 * b);
	}

	inline void operator*=(Matrix44f& a, Matrix44f b)
	{
		a = Matrix44f(
			a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30,
			a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31,
			a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32,
			a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,

			a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30,
			a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
			a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
			a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,

			a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30,
			a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
			a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
			a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,

			a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30,
			a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
			a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
			a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33);
	}

	inline void operator*=(Matrix44f& a, float b)
	{
		a = Matrix44f(
			a.m00 * b, a.m01 * b, a.m02 * b, a.m03 * b,
			a.m10 * b, a.m11 * b, a.m12 * b, a.m13 * b,
			a.m20 * b, a.m21 * b, a.m22 * b, a.m23 * b,
			a.m30 * b, a.m31 * b, a.m32 * b, a.m33 * b);
	}

	// Divide - Vector
	inline Vector2f operator/(Vector2f a, Vector2f b)
	{
		return Vector2f(a.x / b.x, a.y / b.y);
	}

	inline Vector2f operator/(Vector2f a, float b)
	{
		return Vector2f(a.x / b, a.y / b);
	}

	inline Vector3f operator/(Vector3f a, Vector3f b)
	{
		return Vector3f(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	inline Vector3f operator/(Vector3f a, float b)
	{
		return Vector3f(a.x / b, a.y / b, a.z / b);
	}

	inline Vector4f operator/(Vector4f a, Vector4f b)
	{
		return Vector4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	inline Vector4f operator/(Vector4f a, float b)
	{
		return Vector4f(a.x / b, a.y / b, a.z / b, a.w / b);
	}

	// Divide - Vector
	inline void operator/=(Vector2f& a, Vector2f b)
	{
		a = Vector2f(a.x / b.x, a.y / b.y);
	}

	inline void operator/=(Vector2f& a, float b)
	{
		a = Vector2f(a.x / b, a.y / b);
	}

	inline void operator/=(Vector3f& a, Vector3f b)
	{
		a = Vector3f(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	inline void operator/=(Vector3f& a, float b)
	{
		a = Vector3f(a.x / b, a.y / b, a.z / b);
	}

	inline void operator/=(Vector4f& a, Vector4f b)
	{
		a = Vector4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	inline void operator/=(Vector4f& a, float b)
	{
		a = Vector4f(a.x / b, a.y / b, a.z / b, a.w / b);
	}

	// Divice - Matrix
	inline Matrix33f operator/(Matrix33f a, float b)
	{
		return Matrix33f(a.m00 / b, a.m01 / b, a.m02 / b,
			a.m10 / b, a.m11 / b, a.m12 / b,
			a.m20 / b, a.m21 / b, a.m22 / b);
	}

	inline Matrix44f operator/(Matrix44f a, float b)
	{
		return Matrix44f(
			a.m00 / b, a.m01 / b, a.m02 / b, a.m03 / b,
			a.m10 / b, a.m11 / b, a.m12 / b, a.m13 / b,
			a.m20 / b, a.m21 / b, a.m22 / b, a.m23 / b,
			a.m30 / b, a.m31 / b, a.m32 / b, a.m33 / b);
	}

	// Inverse - Matrix
	inline Matrix33f Inverse(Matrix33f a)
	{
		float inv = a.Value[2] * a.Value[3] * a.Value[7] - a.Value[0] * a.Value[5] * a.Value[7] +
			a.Value[1] * a.Value[5] * a.Value[6] - a.Value[1] * a.Value[3] * a.Value[8] +
			a.Value[0] * a.Value[4] * a.Value[8] - a.Value[2] * a.Value[4] * a.Value[6];

		return a / inv;
	}

	inline Matrix44f Inverse(Matrix44f a)
	{
		float inv = a.Value[3] * a.Value[4] * a.Value[9] * a.Value[14] - a.Value[0] * a.Value[7] * a.Value[10] * a.Value[13] +
			a.Value[2] * a.Value[7] * a.Value[8] * a.Value[13] - a.Value[1] * a.Value[4] * a.Value[11] * a.Value[14] +
			a.Value[1] * a.Value[6] * a.Value[11] * a.Value[12] - a.Value[2] * a.Value[5] * a.Value[8] * a.Value[15] +
			a.Value[0] * a.Value[5] * a.Value[10] * a.Value[15] - a.Value[3] * a.Value[6] * a.Value[9] * a.Value[12];

		return a / inv;
	}

	// Divide - Matrix
	inline Matrix33f operator/(Matrix33f a, Matrix33f b)
	{
		return a * Inverse(b);
	}

	inline Matrix44f operator/(Matrix44f a, Matrix44f b)
	{
		return a * Inverse(b);
	}

	// Divide - Matrix
	inline void operator/=(Matrix33f& a, Matrix33f b)
	{
		a = a * Inverse(b);
	}

	inline void operator/=(Matrix33f& a, float b)
	{
		a = Matrix33f(a.m00 / b, a.m01 / b, a.m02 / b,
			a.m10 / b, a.m11 / b, a.m12 / b,
			a.m20 / b, a.m21 / b, a.m22 / b);
	}

	inline void operator/=(Matrix44f& a, Matrix44f b)
	{
		a = a * Inverse(b);
	}

	inline void operator/=(Matrix44f& a, float b)
	{
		a = Matrix44f(
			a.m00 / b, a.m01 / b, a.m02 / b, a.m03 / b,
			a.m10 / b, a.m11 / b, a.m12 / b, a.m13 / b,
			a.m20 / b, a.m21 / b, a.m22 / b, a.m23 / b,
			a.m30 / b, a.m31 / b, a.m32 / b, a.m33 / b);
	}

	// Equal - Vector
	inline bool operator==(Vector2f a, Vector2f b)
	{
		return (a.x == b.x && a.y == b.y);
	}

	inline bool operator==(Vector3f a, Vector3f b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}

	inline bool operator==(Vector4f a, Vector4f b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
	}

	// Equal - Matrix
	inline bool operator==(Matrix33f a, Matrix33f b)
	{
		return (a.m00 == b.m00 && a.m01 == b.m01 && a.m02 == b.m02 &&
			a.m10 == b.m10 && a.m11 == b.m11 && a.m12 == b.m12 &&
			a.m20 == b.m20 && a.m21 == b.m21 && a.m22 == b.m22);
	}

	inline bool operator==(Matrix44f a, Matrix44f b)
	{
		return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3] &&
			a[4] == b[4] && a[5] == b[5] && a[6] == b[6] && a[7] == b[7] &&
			a[8] == b[8] && a[9] == b[9] && a[10] == b[10] && a[11] == b[11] &&
			a[12] == b[12] && a[13] == b[13] && a[14] == b[14] && a[15] == b[15]);
	}

#pragma endregion

	// Basic math
	inline float Degree(float x)
	{
		return (float)(x * 180 / MATH_PI);
	}

	inline float Radian(float x)
	{
		return (float)(x * MATH_PI / 180);
	}

	inline float DegToRad(float x)
	{
		return (float)(Radian(x) * (180 / MATH_PI));
	}

	inline float RadToDeg(float x)
	{
		return (float)(Degree(x) * (MATH_PI / 180));
	}

	inline float Min(float a, float b)
	{
		return a < b ? a : b;
	}

	inline float Max(float a, float b)
	{
		return a < b ? b : a;
	}

	// Dot - Vector
	inline float Dot(float a, float b)
	{
		return a * b;
	}

	inline float Dot(Vector2f a, Vector2f b)
	{
		return a[0] * b[0] + a[1] * b[1];
	}

	inline float Dot(Vector3f a, Vector3f b)
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	}

	inline float Dot(Vector4f a, Vector4f b)
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
	}

	// Lenght - Vector
	inline float Length(Vector2f a)
	{
		return sqrt(pow(a.x, 2) + pow(a.y, 2));
	}

	inline float Length(float x, float y)
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	inline float Length(Vector3f a)
	{
		return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	}

	inline float Length(float x, float y, float z)
	{
		//return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	inline float Length(Vector4f a)
	{
		return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
	}

	inline float Length(float x, float y, float z, float w)
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
	}

	// Cross - Vector
	inline Vector3f Cross(Vector3f a, Vector3f b)
	{
		return Vector3f((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
	}

	// Normalize - Vector
	inline Vector2f Normalize(Vector2f a)
	{
		return a / Length(a);
	}

	inline Vector3f Normalize(Vector3f a)
	{
		return a / Length(a);
	}

	inline Vector4f Normalize(Vector4f a)
	{
		return a / Length(a);
	}

	// Transpose - Matrix
	inline Matrix33f Transpose(Matrix33f a)
	{
		Swap(a.Value[1], a.Value[3]);
		Swap(a.Value[2], a.Value[6]);
		Swap(a.Value[5], a.Value[7]);

		return a;
	}

	inline Matrix44f Transpose(Matrix44f a)
	{
		Swap(a.Value[1], a.Value[4]);
		Swap(a.Value[2], a.Value[8]);
		Swap(a.Value[3], a.Value[12]);
		Swap(a.Value[6], a.Value[9]);
		Swap(a.Value[7], a.Value[13]);
		Swap(a.Value[11], a.Value[14]);

		return a;
	}

	inline void Transpo(Matrix44f& a)
	{
		Swap(a.Value[1], a.Value[4]);
		Swap(a.Value[2], a.Value[8]);
		Swap(a.Value[3], a.Value[12]);
		Swap(a.Value[6], a.Value[9]);
		Swap(a.Value[7], a.Value[13]);
		Swap(a.Value[11], a.Value[14]);
	}

	// Identity - Matrix
	inline Matrix33f Identity3x3()
	{
		return Matrix33f(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f);
	}

	inline Matrix44f Identity4x4()
	{
		return Matrix44f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline void Identity(Matrix44f& a)
	{
		a[0] = 1.0f;
		a[1] = 0.0f;
		a[2] = 0.0f;
		a[3] = 0.0f;

		a[4] = 0.0f;
		a[5] = 1.0f;
		a[6] = 0.0f;
		a[7] = 0.0f;

		a[8]  = 0.0f;
		a[9]  = 0.0f;
		a[10] = 1.0f;
		a[11] = 0.0f;

		a[12] = 0.0f;
		a[13] = 0.0f;
		a[14] = 0.0f;
		a[15] = 1.0f;
	}

	// Translation - Matrix
	inline Matrix44f Translation(Vector3f b)
	{
		return Matrix44f(
			1.0f, 0.0f, 0.0f, b.x,
			0.0f, 1.0f, 0.0f, b.y,
			0.0f, 0.0f, 1.0f, b.z,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline void Translation(Matrix44f& a, Vector3f b)
	{
		a[0] += a[12] * b.x;   a[1] += a[13] * b.x;   a[2] += a[14] * b.x;   a[3] += a[15] * b.x;
		a[4] += a[12] * b.y;   a[5] += a[13] * b.y;   a[6] += a[14] * b.y;   a[7] += a[15] * b.y;
		a[8] += a[12] * b.z;   a[9] += a[13] * b.z;   a[10] += a[14] * b.z;   a[11] += a[15] * b.z;
	}

	inline void Rotate(Matrix44f& a, float angle, float x, float y, float z)
	{
		float c = cosf(DegToRad(angle));    // cosine
		float s = sinf(DegToRad(angle));    // sine
		float xx = x * x;
		float xy = x * y;
		float xz = x * z;
		float yy = y * y;
		float yz = y * z;
		float zz = z * z;

		// build rotation matrix
		Matrix44f m;
		m[0] = xx * (1 - c) + c;
		m[1] = xy * (1 - c) - z * s;
		m[2] = xz * (1 - c) + y * s;
		m[3] = 0;
		m[4] = xy * (1 - c) + z * s;
		m[5] = yy * (1 - c) + c;
		m[6] = yz * (1 - c) - x * s;
		m[7] = 0;
		m[8] = xz * (1 - c) - y * s;
		m[9] = yz * (1 - c) + x * s;
		m[10] = zz * (1 - c) + c;
		m[11] = 0;
		m[12] = 0;
		m[13] = 0;
		m[14] = 0;
		m[15] = 1;

		a = m * a;
	}

	// Scale - Matrix
	inline Matrix44f Scale(Vector3f b)
	{
		return Matrix44f(
			b.x, 0.0f, 0.0f, 0.0f,
			0.0f, b.y, 0.0f, 0.0f,
			0.0f, 0.0f, b.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Rotate - Matrix
	inline Matrix44f Rotate(Vector3f a)
	{
		const float x = ToRadian(a.x);
		const float y = ToRadian(a.y);
		const float z = ToRadian(a.z);

		Matrix44f rx = Matrix44f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosf(x), -sinf(x), 0.0f,
			0.0f, sinf(x), cosf(x), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		Matrix44f ry = Matrix44f(
			cosf(y), 0.0f, -sinf(y), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinf(y), 0.0f, cosf(y), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		Matrix44f rz = Matrix44f(
			cosf(z), -sinf(z), 0.0f, 0.0f,
			sinf(z), cosf(z), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return rz * ry * rx;
	}

	// Transform - Vector
	inline Vector3f Transform(Vector3f a, Matrix33f b)
	{
		return Vector3f((a.x * b[0]) + (a.y * b[3]) + (a.z * b[6]),
			(a.x * b[1]) + (a.y * b[4]) + (a.z * b[7]),
			(a.x * b[2]) + (a.y * b[5]) + (a.z * b[8]));
	}

	// Calculate Vector Normal
	inline std::vector<Vector3f> CalculateNormal(std::vector<Vector3f> vVertex)
	{
		std::vector<Vector3f> vNormal;

		for (unsigned int i = 0; i < vVertex.size() / 3; i++)
		{
			Vector3f d1 = vVertex[i * 3 + 1] - vVertex[i * 3 + 0];
			Vector3f d2 = vVertex[i * 3 + 2] - vVertex[i * 3 + 0];

			Vector3f cross = Cross(d1, d2);

			float dist = Length(cross);

			Vector3f norm = cross / dist;

			vNormal.push_back(norm);
			vNormal.push_back(norm);
			vNormal.push_back(norm);
		}

		return vNormal;
	}

	struct QQuaternion
	{
		float x, y, z, w;

		QQuaternion(float _x, float _y, float _z, float _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
	};

	inline QQuaternion Normalize(QQuaternion a)
	{
		float Length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);

		a.x /= Length;
		a.y /= Length;
		a.z /= Length;
		a.w /= Length;

		return a;
	}

	inline QQuaternion Conjugate(QQuaternion a)
	{
		return QQuaternion(-a.x, -a.y, -a.z, a.w);
	}

	inline QQuaternion operator*(const QQuaternion& l, const QQuaternion& r)
	{
		const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
		const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
		const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
		const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

		QQuaternion ret(x, y, z, w);

		return ret;
	}

	inline QQuaternion operator*(const QQuaternion& q, const Vector3f& v)
	{
		const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
		const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
		const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
		const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

		QQuaternion ret(x, y, z, w);

		return ret;
	}

	inline Vector3f Rotate(Vector3f a, float Angle, const Vector3f& Axe)
	{
		const float SinHalfAngle = sinf(ToRadian(Angle / 2));
		const float CosHalfAngle = cosf(ToRadian(Angle / 2));

		const float Rx = Axe.x * SinHalfAngle;
		const float Ry = Axe.y * SinHalfAngle;
		const float Rz = Axe.z * SinHalfAngle;
		const float Rw = CosHalfAngle;
		QQuaternion RotationQ(Rx, Ry, Rz, Rw);

		QQuaternion ConjugateQ = Conjugate(RotationQ);

		QQuaternion W = RotationQ * a * ConjugateQ;

		return Vector3f(W.x, W.y, W.z);
	}

	inline Matrix44f CameraTranslation(Vector3f Target, Vector3f Up)
	{
		Vector3f N = Math::Normalize(Target);
		Vector3f U = Math::Cross(Math::Normalize(Up), N);
		Vector3f V = Math::Cross(N, U);

		return Matrix44f(U.x, U.y, U.y, 0.0f,
			V.x, V.y, V.z, 0.0f,
			N.x, N.y, N.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline void computeTangentBasis(
		// inputs
		std::vector<Vector3f> & vertices,
		std::vector<Vector2f> & uvs,
		std::vector<Vector3f> & normals,
		// outputs
		std::vector<Vector3f> & tangents,
		std::vector<Vector3f> & bitangents
		)
	{
		for (unsigned int i = 0; i<vertices.size(); i += 3)
		{
			// Shortcuts for vertices
			Vector3f & v0 = vertices[i + 0];
			Vector3f & v1 = vertices[i + 1];
			Vector3f & v2 = vertices[i + 2];

			// Shortcuts for UVs
			Vector2f & uv0 = uvs[i + 0];
			Vector2f & uv1 = uvs[i + 1];
			Vector2f & uv2 = uvs[i + 2];

			// Edges of the triangle : postion delta
			Vector3f deltaPos1 = v1 - v0;
			Vector3f deltaPos2 = v2 - v0;

			// UV delta
			Vector2f deltaUV1 = uv1 - uv0;
			Vector2f deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

			Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
			Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

			// Set the same tangent for all three vertices of the triangle.
			// They will be merged later, in vboindexer.cpp
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			tangents.push_back(tangent);

			// Same thing for binormals
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
		}

		//// See "Going Further"
		//for (unsigned int i = 0; i<vertices.size(); i += 1)
		//{
		//	Vector3f & n = normals[i];
		//	Vector3f & t = tangents[i];
		//	Vector3f & b = bitangents[i];

		//	// Gram-Schmidt orthogonalize
		//	t = Normalize(t - n * Dot(n, t));

		//	// Calculate handedness
		//	if (Dot(Cross(n, t), b) < 0.0f)
		//	{
		//		t = t * -1.0f;
		//	}
		//}
	}


}