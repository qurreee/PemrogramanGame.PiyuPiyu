#include "Sprite.h"


using namespace Engine;


Sprite::Sprite(Texture* texture, Shader* shader, Quad* quad)
{
	this->texture = texture;
	this->quad = quad;
	this->shader = shader;
	this->width = (float)texture->GetWidth();
	this->height = (float)texture->GetHeight();
	this->boundingBox = new BoundingBox();
	SetBoundingBoxSize(GetScaleWidth(), GetScaleHeight());
}

Sprite::~Sprite()
{
	delete boundingBox;
	delete currentAnim;
}

void Sprite::Draw()
{
	if (wireframe) {
		glPolygonMode(GL_FRONT, GL_LINE);
		UpdateShaderData();
		// Draw Quad
		quad->Draw();
		return;
	}

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Bind texture
	texture->Bind();
	UpdateShaderData();
	// Draw Quad
	quad->Draw();
	// Unbind texture
	texture->UnBind();
	// Disable transparency
	glDisable(GL_BLEND);
}


void Engine::Sprite::Update(float deltaTime)
{
	int n = GetTotalFrames();
	if (!enableAnimation || currentAnim == NULL || n == 1)
		return;

	frameDuration += deltaTime;

	if (frameDuration >= maxFrameDuration) {
		frameDuration = 0;
		frameIndex = (frameIndex < currentAnim->startFrameIndex || frameIndex >= currentAnim->endFrameIndex) ? currentAnim->startFrameIndex : frameIndex + 1;
	}
}

Engine::Sprite* Engine::Sprite::AddAnimation(string name, int startFrameIndex, int endFrameIndex)
{
	AnimData* a = new AnimData();
	a->name = name;
	a->startFrameIndex = startFrameIndex;
	a->endFrameIndex = endFrameIndex;
	this->animationData.push_back(a);
	return this;
}

Engine::Sprite* Engine::Sprite::PlayAnim(string name)
{
	enableAnimation = true;
	if (currentAnim != NULL && name == currentAnim->name) return this;
	currentAnim = GetAnimData(name);
	return this;
}

Engine::Sprite* Engine::Sprite::SetFlipHorizontal(bool flipHorizontal)
{
	this->flipHorizontal = flipHorizontal;
	return this;
}

Engine::Sprite* Engine::Sprite::SetFlipVertical(bool flipVertical)
{
	this->flipVertical = flipVertical;
	return this;
}


Engine::Sprite* Engine::Sprite::SetAnimationDuration(float maxFrameDuration)
{
	this->maxFrameDuration = maxFrameDuration;
	return this;
}

Engine::Sprite* Engine::Sprite::SetEnableAnimation(bool enableAnimation)
{
	this->enableAnimation = enableAnimation;
	return this;
}

Engine::Sprite* Sprite::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	return this;
}

Engine::Sprite* Sprite::SetRotation(float degree)
{
	this->degree = degree;
	return this;
}

Engine::Sprite* Engine::Sprite::SetNumXFrames(int numXFrames)
{
	this->numXFrames = numXFrames;
	return this;
}

Engine::Sprite* Engine::Sprite::SetNumYFrames(int numYFrames)
{
	this->numYFrames = numYFrames;
	return this;
}

Engine::Sprite* Sprite::SetScale(float s)
{
	this->s = abs(s);
	return SetBoundingBoxSize(GetScaleWidth(), GetScaleHeight());
}


int Engine::Sprite::GetTotalFrames()
{
	return numXFrames * numYFrames;
}

float Sprite::GetRotation()
{
	return this->degree;
}


float Engine::Sprite::GetScale()
{
	return this->s;
}

Engine::Sprite* Sprite::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;

	return SetBoundingBoxSize(GetScaleWidth(), GetScaleHeight());
}

float Sprite::GetScaleWidth()
{
	return (s * width) / numXFrames;
}

float Sprite::GetScaleHeight()
{
	return (s * height) / numYFrames;
}

BoundingBox* Sprite::GetBoundingBox()
{
	float x = position.x;
	float y = position.y;
	float w = boundingBox->width, h = boundingBox->height;
	float dx = GetScaleWidth() - w;
	x += 0.5f * dx;
	vec2 p1 = GetRotatedPoint(x + w, y);
	vec2 p2 = GetRotatedPoint(x + w, y + h);
	vec2 p3 = GetRotatedPoint(x, y + h);
	vec2 p4 = GetRotatedPoint(x, y);
	boundingBox->SetVertices(p1, p2, p3, p4);

	return boundingBox;
}

vec2 Engine::Sprite::GetPosition()
{
	return position;
}



mat4 Sprite::CreateTransform()
{
	mat4 transform = mat4();
	// Translate Sprite
	float x = position.x;
	float y = position.y;
	float w = GetScaleWidth(), h = GetScaleHeight();
	transform = translate(transform, vec3(x, y, 0.0f));
	// Rotate sprite at center
	transform = translate(transform, vec3(0.5f * w, 0.5f * h, 0.0f));
	transform = rotate(transform, radians(degree), vec3(0.0f, 0.0f, 1.0f));
	transform = translate(transform, vec3(-0.5f * w, -0.5f * h, 0.0f));
	// Scale sprite
	float sx = flipHorizontal ? -1.0f : 1.0f;
	float sy = flipVertical ? -1.0f : 1.0f;
	float tx = flipHorizontal ? w : 0;
	float ty = flipVertical ? h : 0;
	transform = translate(transform, vec3(tx, ty, 0.0f));
	transform = scale(transform, vec3(sx * w, sy * h, 1));

	return transform;
}

void Engine::Sprite::UpdateShaderData()
{
	shader->Use();
	shader->setInt(numXFrames, "nx");
	shader->setInt(numYFrames, "ny");
	shader->setInt(frameIndex, "frameIndex");
	shader->setMat4(CreateTransform(), "model");
}

AnimData* Engine::Sprite::GetAnimData(string name)
{
	for (AnimData* a : animationData)
		if (name == a->name) return a;
	return NULL;
}

vec2 Engine::Sprite::GetRotatedPoint(float x, float y)
{
	float rad = glm::radians(degree);
	float sinx = glm::sin(rad);
	float cosx = glm::cos(rad);
	float w = GetScaleWidth(), h = GetScaleHeight();
	float cx = position.x + (w * 0.5f);
	float cy = position.y + (h * 0.5f);

	return vec2((x - cx) * cosx - (y - cy) * sinx + cx,
		(x - cx) * sinx + (y - cy) * cosx + cy);
}

Engine::Sprite* Engine::Sprite::SetBoundingBoxSize(float w, float h)
{
	this->boundingBox->width = w;
	this->boundingBox->height = h;
	return this;
}

Sprite* Engine::Sprite::SetWireframe(bool wireframe)
{
	this->wireframe = wireframe;
	return this;
}



