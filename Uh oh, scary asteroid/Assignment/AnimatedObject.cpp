#include "AnimatedObject.h"
#include "GameManager.h"
using namespace std;

AnimatedObject::AnimatedObject(string name,
	SpriteSheet* spriteSheet,
	TransformationMatrix* transformMatrix,
	int red,
	int green,
	int blue,
	D3DXVECTOR2* position,
	float force,
	float mass,
	int animationFPS) : GameObject(name,
		spriteSheet,
		transformMatrix,
		red,
		green,
		blue,
		position,
		force,
		mass)
{
	this->characterAnimation = 0;
	this->currentFrame = 0;
	this->animationFPS = animationFPS;
}

SpriteSheet* AnimatedObject::getSprite() { return spriteSheet; }

void AnimatedObject::setCharacterAnimation(int animation) { characterAnimation = animation; }
void AnimatedObject::setCurrentFrame(int cFrame) { currentFrame = cFrame; }

int AnimatedObject::getAnimationFPS() { return animationFPS; }
int AnimatedObject::getCurrentFrame() { return currentFrame; }
int AnimatedObject::getCharacterAnimation() { return characterAnimation; }

void AnimatedObject::addCurrentFrame() { currentFrame++; }
void AnimatedObject::resetCurrentFrame() { currentFrame = 0; }

void AnimatedObject::updateSprite()
{
	spriteRect->left = (currentFrame % spriteSheet->getSpriteCol()) * spriteWidth;
	spriteRect->top = characterAnimation * spriteHeight;
	spriteRect->right = spriteRect->left + spriteWidth;
	spriteRect->bottom = spriteRect->top + spriteHeight;
}