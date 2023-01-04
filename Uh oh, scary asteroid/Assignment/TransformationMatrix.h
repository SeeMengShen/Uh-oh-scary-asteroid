#ifndef TRANSFORMATION_MATRIX_H
#define TRANSFORMATION_MATRIX_H

#pragma once
#include <d3dx9.h>
#include <iostream>
using namespace std;

class TransformationMatrix
{
private:
	D3DXVECTOR2 scalingCentre;
	float scalingRotation;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 rotationCentre;
	float rotation;

public:
	TransformationMatrix(D3DXVECTOR2 scalingCentre,
		D3DXVECTOR2 scaling,
		float rotation);

	D3DXVECTOR2 getScalingCentre();
	D3DXVECTOR2 getScaling();
	float getRotation();
};

#endif