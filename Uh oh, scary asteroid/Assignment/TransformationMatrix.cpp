#include "TransformationMatrix.h"

TransformationMatrix::TransformationMatrix(D3DXVECTOR2 scalingCentre,
	//float scalingRotation,
	D3DXVECTOR2 scaling,
	//D3DXVECTOR2 rotationCentre,
	float rotation)
{
	this->scalingCentre = scalingCentre;
	//this->scalingRotation = scalingRotation;
	this->scaling = scaling;
	//this->rotationCentre = rotationCentre;
	this->rotation = rotation;
}

D3DXVECTOR2 TransformationMatrix::getScalingCentre() { return scalingCentre; }
//float TransformationMatrix::getScalingRotation() { return scalingRotation; }
D3DXVECTOR2 TransformationMatrix::getScaling() { return scaling; }
//D3DXVECTOR2 TransformationMatrix::getRotationCenter() { return rotationCentre; }
float TransformationMatrix::getRotation() { return rotation; }
