#include "collision.h"
#include <iostream>
#include "main.h"

using namespace STDev;

void PrintVector(const Vector2& v)
{
	std::cout << "(" << v.x << ", " << v.y << ")";
}

void PrintBox(const AABB& v)
{
	std::cout << "[";
	PrintVector(v.min);
	std::cout << ";";
	PrintVector(v.max);
	std::cout << "]" << std::endl;
}

void PrintCollisionDetails(const CollisionResult& result)
{
	if (result.hit)
	{
		std::cout << "=== COLLISION DETECTED ===\n";
		std::cout << "Distance: " << result.distance << "\n";
		std::cout << "Hit Point: ";
		PrintVector(result.hitPoint);
		std::cout << "\nNormal: ";
		PrintVector(result.normal);
		std::cout << "\n========================\n";
	}
	else
	{
		std::cout << "No collision detected.\n";
	}
}

void test_ray_circle_hit()
{
	std::cout << "=== TEST 1: Ray-Circle Collision ===\n";
	Ray r1(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
	Circle c1(Vector2(2.0f, 2.0f), 1.0f);

	CollisionResult result1 = TestRayCircleCollision(r1, c1);
	PrintCollisionDetails(result1);
	std::cout << "\n";
}

void test_ray_circle_miss()
{
	std::cout << "=== TEST 2: Ray Miss Circle ===\n";
	Ray r2(Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f));
	Circle c2(Vector2(5.0f, 5.0f), 1.0f);

	CollisionResult result2 = TestRayCircleCollision(r2, c2);
	PrintCollisionDetails(result2);
	std::cout << "\n";
}

void test_ray_from_inside()
{
	std::cout << "=== TEST 3: Ray from Inside Circle ===\n";
	Ray r3(Vector2(2.0f, 2.0f), Vector2(1.0f, 0.0f));
	Circle c3(Vector2(2.0f, 2.0f), 1.0f);

	CollisionResult result3 = TestRayCircleCollision(r3, c3);
	PrintCollisionDetails(result3);
	std::cout << "\n";
}

void test_circle_circle_overlap()
{
	std::cout << "=== TEST 4: Circle-Circle Collision (Overlapping) ===\n";
	Circle c4(Vector2(0.0f, 0.0f), 2.0f);
	Circle c5(Vector2(3.0f, 0.0f), 2.0f);

	if (TestCollision(c4, c5))
	{
		std::cout << "Circles are overlapping!\n";
	}
	else
	{
		std::cout << "Circles are NOT overlapping.\n";
	}
	std::cout << "\n";
}

void test_circle_circle_separate()
{
	std::cout << "=== TEST 5: Circle-Circle Collision (Separate) ===\n";
	Circle c6(Vector2(0.0f, 0.0f), 1.0f);
	Circle c7(Vector2(5.0f, 0.0f), 1.0f);

	if (TestCollision(c6, c7))
	{
		std::cout << "Circles are overlapping!\n";
	}
	else
	{
		std::cout << "Circles are NOT overlapping.\n";
	}
	std::cout << "\n";
}

void test_point_inside_circle()
{
	std::cout << "=== TEST 6: Point-Circle Collision (Inside) ===\n";
	Vector2 point(1.0f, 1.0f);
	Circle c8(Vector2(0.0f, 0.0f), 2.0f);

	if (TestCollision(point, c8))
	{
		std::cout << "Point is inside circle!\n";
	}
	else
	{
		std::cout << "Point is outside circle.\n";
	}
	std::cout << "\n";
}

void test_point_outside_circle()
{
	std::cout << "=== TEST 7: Point-Circle Collision (Outside) ===\n";
	Vector2 point2(5.0f, 5.0f);
	Circle c9(Vector2(0.0f, 0.0f), 2.0f);

	if (TestCollision(point2, c9))
	{
		std::cout << "Point is inside circle!\n";
	}
	else
	{
		std::cout << "Point is outside circle.\n";
	}
	std::cout << "\n";
}

void test_ray_tangent()
{
	std::cout << "=== TEST 8: Ray Tangent to Circle ===\n";
	Ray r4(Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f));
	Circle c10(Vector2(5.0f, 1.0f), 1.0f);

	CollisionResult result4 = TestRayCircleCollision(r4, c10);
	PrintCollisionDetails(result4);
	std::cout << "\n";
}

void test_ray_backwards()
{
	std::cout << "=== TEST 9: Ray Pointing Backwards ===\n";
	Ray r5(Vector2(5.0f, 5.0f), Vector2(-1.0f, 0.0f));
	Circle c11(Vector2(10.0f, 5.0f), 1.0f);

	CollisionResult result5 = TestRayCircleCollision(r5, c11);
	PrintCollisionDetails(result5);
	std::cout << "\n";
}

void test_original_case()
{
	std::cout << "=== TEST 10: Original Case from Your Code ===\n";
	Ray r;
	r.direction = Vector2(1.0f, 1.0f);
	r.origin = Vector2(0.0f, 0.0f);
	Circle c;
	c.center = Vector2(2.0f, 2.0f);
	c.radius = 1.0f;

	if (TestCollision(r, c))
	{
		std::cout << "collision detected\n";
	}
	else
	{
		std::cout << "collision NOT detected\n";
	}
	std::cout << "\n";
}
void test_aabb_case()
{
	AABB box1 = AABB({ 1,1 }, { 2,2 });
	AABB box2 = AABB({ 2,2 }, { 4,4 });
	BoxCollisionTest(box1, box2);

	box1 = AABB({ 2,2 }, { 4,4 });
	box2 = AABB({ 1,1 }, { 2,2 });
	BoxCollisionTest(box1, box2);

	box1 = AABB({ 1,1 }, { 2,2 });
	box2 = AABB({ 1,3 }, { 2,4 });
	BoxCollisionTest(box1, box2);
}

void BoxCollisionTest(STDev::AABB& box1, STDev::AABB& box2)
{
	std::cout << "BOX 1:";
	PrintBox(box1);
	std::cout << "BOX 2:";
	PrintBox(box2);

	std::cout << "collisione BOX:" << (TestAABBCollision(box1, box2) ? "TRUE" : "FALSE") << std::endl;
	std::cout << "collisione BOX:" << (TestAABBCollisionOptimized(box1, box2) ? "TRUE" : "FALSE") << std::endl;
}

int main()
{
	std::cout << "\n";
	std::cout << "========================================\n";
	std::cout << "   COLLISION DETECTION TEST SUITE\n";
	std::cout << "========================================\n";
	std::cout << "\n";

	//test_ray_circle_hit();
	//test_ray_circle_miss();
	//test_ray_from_inside();
	//test_circle_circle_overlap();
	//test_circle_circle_separate();
	//test_point_inside_circle();
	//test_point_outside_circle();
	//test_ray_tangent();
	//test_ray_backwards();
	//test_original_case();

	//test_aabb_case();
	AABB box2 = AABB({ 1,3 }, { 2,4 });
	Circle circle;
	circle.center = Vector2(1.0f, 2.0f);
	circle.radius = 1.0f;
	std::cout << "TestAABBCircleCollision:" << (TestAABBCircleCollision(circle, box2) ? "TRUE" : "FALSE") << std::endl;

	std::cout << "========================================\n";
	std::cout << "   ALL TESTS COMPLETED\n";
	std::cout << "========================================\n";
	std::cout << "\n";

	return 0;
}