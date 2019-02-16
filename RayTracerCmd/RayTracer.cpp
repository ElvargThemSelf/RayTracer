#include <iostream>
#include <fstream>
#include <chrono>


#include <SceneObjects/Sphere.hpp>
#include <SceneObjects/CompositeSceneObject.hpp>
#include <Materials/Lambertian.h>
#include <Materials/Metal.h>
#include <Materials/Dielectric.h>
#include <SimpleRT/SimpleRT.hpp>


using namespace std;

template <typename T>
auto Run(string desc, T method)
{
	const auto start = chrono::steady_clock::now();
	auto results = method();
	const auto end = chrono::steady_clock::now();

	cout << desc.c_str() << " - Duration: " << chrono::duration<double, milli>(end - start).count() << endl;

	return results;
}

template <typename T>
auto composeWorld()
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject<T>>();

	auto sphere1 = std::make_unique<Sphere<T>>(Vector3<T>{ 0.0f, 0.0f, -1.0f }, 0.5f);
	sphere1->SetMaterial(std::make_shared<Lambertian<T>>(Vector3<T>{ 0.1f, 0.2f, 0.5f }));
	world->Add(move(sphere1));

	auto sphere2 = std::make_unique<Sphere<T>>(Vector3<T>{ 0.0f, -100.5f, -1.0f }, 100.0f);
	sphere2->SetMaterial(std::make_shared<Lambertian<T>>(Vector3<T>{ 0.8f, 0.8f, 0.0f }));
	world->Add(move(sphere2));

	auto sphere3 = std::make_unique<Sphere<T>>(Vector3<T>{ 1.0f, 0.0f, -1.0f }, 0.5f);
	sphere3->SetMaterial(std::make_shared<Metal<T>>(Vector3<T>{ 0.8f, 0.6f, 0.2f }, 0.0f));
	world->Add(move(sphere3));

	auto sphere4 = std::make_unique<Sphere<T>>(Vector3<T>{ -1.0f, 0.0f, -1.0f }, 0.5f);
	sphere4->SetMaterial(std::make_shared<Dielectric<T>>(1.5f));
	world->Add(move(sphere4));

	auto sphere5 = std::make_unique<Sphere<T>>(Vector3<T>{ -1.0f, 0.0f, -1.0f }, -0.45f);
	sphere5->SetMaterial(std::make_shared<Dielectric<T>>(1.5f));
	world->Add(move(sphere5));

	return world;
}

auto simplertf(int w, int h)
{
	auto world = composeWorld<float>();
	auto simpleRTf = SimpleRT<float>();

	return Run("SimpleRTf", [&simpleRTf, w, h, &world] { return simpleRTf.Render(w, h, *world); });
}

auto simplertd(int w, int h)
{
	auto world = composeWorld<double>();
	auto simpleRTd = SimpleRT<double>();

	return Run("SimpleRTd", [&simpleRTd, w, h, &world] { return simpleRTd.Render(w, h, *world); });
}

void write(string fileName, int w, int h, vector<Vector3<int>> results)
{
	auto out = ofstream();
	out.open(fileName, ofstream::out);
	out << "P3" << endl;
	out << w << " " << h << endl;
	out << 255 << endl;
	for (auto v : results)
		out << v.x() << " " << v.y() << " " << v.z() << endl;
	out.close();
}

int main()
{
	int w = 400;
	int h = 200;

	auto s1 = simplertf(w, h);
	write("simplertf.ppm", w, h, s1);

	auto s2 = simplertd(w, h);
	write("simplertd.ppm", w, h, s2);

	return cin.get();
}