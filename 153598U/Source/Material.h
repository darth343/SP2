#ifndef MATERIAL_H
#define MATERIAL_H


struct Component
{
	float r, g, b, a;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1)
	{
		Set(r, g, b, a);
	}
	void Set(float r, float g, float b, float a = 1)
	{
		this->r = r; this->g = g; this->b = b; this->a = a;
	}

};

struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material()
	{
		kAmbient.Set(0.15f, 0.15f, 0.15f);
		kDiffuse.Set(0.3f, 0.3f, 0.3f);
		kSpecular.Set(0.f, 0.f, 0.f);
		kShininess = 0.5f;
	}
};
#endif