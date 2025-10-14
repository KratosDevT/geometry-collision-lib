#pragma once


#pragma once
#include <cmath>
#include <algorithm>

namespace STDev
{
	struct Vector2
	{
		float x;
		float y;

		// Costruttori
		Vector2() : x{ 0.0f }, y{ 0.0f }
		{}
		Vector2(float a, float b) : x{ a }, y{ b }
		{}

		// Operazioni vettoriali
		float magnitude() const
		{
			return std::sqrt(x * x + y * y);
		}

		float magnitudeSquared() const
		{
			return x * x + y * y;
		}

		float dot(const Vector2& other) const
		{
			return (x * other.x) + (y * other.y);
		}

		Vector2 normalized() const
		{
			float mag = magnitude();
			if (mag > 0.0001f)
			{
				return Vector2(x / mag, y / mag);
			}
			return Vector2(0.0f, 0.0f);
		}

		// Operatori
		Vector2 operator+(const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator-(const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator*(float scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		Vector2 operator/(float scalar) const
		{
			return Vector2(x / scalar, y / scalar);
		}
	};

	struct Ray
	{
		Vector2 origin;
		Vector2 direction;  // Dovrebbe essere normalizzato

		Ray() : origin(), direction(1.0f, 0.0f)
		{}
		Ray(const Vector2& orig, const Vector2& dir)
			: origin(orig), direction(dir.normalized())
		{}

		Vector2 pointAt(float t) const
		{
			return origin + direction * t;
		}
	};

	struct Circle
	{
		Vector2 center;
		float radius;

		Circle() : center(), radius{ 1.0f }
		{}
		Circle(const Vector2& c, float r) : center(c), radius(r)
		{}
	};

	struct CollisionResult
	{
		bool hit;
		float distance;      // Distanza dall'origine del raggio al punto di collisione
		Vector2 hitPoint;    // Punto di collisione
		Vector2 normal;      // Normale nel punto di collisione

		CollisionResult() : hit(false), distance(0.0f), hitPoint(), normal()
		{}
	};

	// Ray-Circle collision detection
	inline CollisionResult TestRayCircleCollision(const Ray& ray, const Circle& circle)
	{
		CollisionResult result;

		// Vettore dall'origine del raggio al centro del cerchio
		Vector2 oc = ray.origin - circle.center;

		// Risolviamo l'equazione quadratica:
		// ||origin + t * direction - center||^2 = radius^2
		// Espandendo: a*t^2 + b*t + c = 0
		float a = ray.direction.dot(ray.direction);  // Dovrebbe essere ~1 se normalizzato
		float b = 2.0f * oc.dot(ray.direction);
		float c = oc.dot(oc) - circle.radius * circle.radius;

		float discriminant = b * b - 4.0f * a * c;

		// Nessuna intersezione
		if (discriminant < 0.0f)
		{
			return result;
		}

		// Calcola le due soluzioni
		float sqrtDiscriminant = std::sqrt(discriminant);
		float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
		float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

		// Prende la soluzione più vicina che è positiva (davanti al raggio)
		float t = -1.0f;
		if (t1 >= 0.0f)
		{
			t = t1;
		}
		else if (t2 >= 0.0f)
		{
			t = t2;
		}

		// Nessuna intersezione davanti al raggio
		if (t < 0.0f)
		{
			return result;
		}

		// Calcola i dettagli della collisione
		result.hit = true;
		result.distance = t;
		result.hitPoint = ray.pointAt(t);
		result.normal = (result.hitPoint - circle.center).normalized();

		return result;
	}

	// Test di collisione semplice Ray-Circle (solo true/false)
	inline bool TestCollision(const Ray& ray, const Circle& circle)
	{
		return TestRayCircleCollision(ray, circle).hit;
	}

	// Test collisione Circle-Circle
	inline bool TestCollision(const Circle& c1, const Circle& c2)
	{
		Vector2 delta = c2.center - c1.center;
		float distanceSquared = delta.magnitudeSquared();
		float radiusSum = c1.radius + c2.radius;
		return distanceSquared <= (radiusSum * radiusSum);
	}

	// Test di collisione Point-Circle
	inline bool TestCollision(const Vector2& point, const Circle& circle)
	{
		Vector2 delta = point - circle.center;
		return delta.magnitudeSquared() <= (circle.radius * circle.radius);
	}
}
