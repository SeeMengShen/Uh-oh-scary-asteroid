#include "Button.h"
using namespace std;

Button::Button(
	Texture* texture,
	TransformationMatrix* tm,
	Text* label,
	D3DXVECTOR2* positionRelativeToPanel)
{
	this->texture = texture;
	this->tm = tm;
	this->label = label;
	this->positionRelativeToPanel = positionRelativeToPanel;
	buttonRect = new RECT();
	buttonBoxCollider = RECT();

	buttonRect->left = 0;
	buttonRect->right = texture->getTextureWidth();
	buttonRect->top = 0;
	buttonRect->bottom = texture->getTextureHeight();

	mouseOn = false;
}

Texture* Button::getTexture() { return texture; }

TransformationMatrix* Button::getTransformationMatrix() { return tm; }

Text* Button::getLabel() { return label; }

D3DXVECTOR2* Button::getPositionRelativeToPanel() { return positionRelativeToPanel; }

RECT* Button::getButtonRect() { return buttonRect; }

RECT Button::getButtonBoxCollider() { return buttonBoxCollider; }

bool Button::isMouseOn() { return mouseOn; }

void Button::setMouseOn(bool mouseOn)
{
	this->mouseOn = mouseOn;
}

void Button::setButtonBoxCollider(float panelPositionRelativeToWindowsX, float panelPositionRelativeToWindowsY)
{
	buttonBoxCollider.left = panelPositionRelativeToWindowsX + positionRelativeToPanel->x;
	buttonBoxCollider.right = panelPositionRelativeToWindowsX + positionRelativeToPanel->x + texture->getTextureWidth() * tm->getScaling().x;
	buttonBoxCollider.top = panelPositionRelativeToWindowsY + positionRelativeToPanel->y;
	buttonBoxCollider.bottom = panelPositionRelativeToWindowsY + positionRelativeToPanel->y + texture->getTextureHeight() * tm->getScaling().y;
}

void Button::cleanup()
{
	cout << "\n\nCleanup button : " + label->getStr() << endl;

	texture = NULL;

	delete tm;
	tm = NULL;

	label->cleanup();
	delete label;
	label = NULL;

	delete positionRelativeToPanel;
	positionRelativeToPanel = NULL;
	cout << "SUCCESSFUL\n\n" << endl;
}