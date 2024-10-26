#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Quad.h"
#include "BoundingBox.h"
#include <GLM/gtc/matrix_transform.hpp>

using namespace glm;

namespace Engine {
	struct AnimData {
		string name;
		int startFrameIndex, endFrameIndex;
	};

	class Sprite
	{
	public:
		Sprite(Texture* texture, Shader* shader, Quad* quad);
		~Sprite();
		void Draw();
		void Update(float deltaTime);
		Sprite* AddAnimation(string name, int startFrameIndex, int endFrameIndex);
		Sprite* PlayAnim(string name);
		Sprite* SetFlipHorizontal(bool flipHorizontal);
		Sprite* SetFlipVertical(bool flipVertical);
		Sprite* SetAnimationDuration(float maxFrameDuration);
		Sprite* SetEnableAnimation(bool enableAnimation);
		Sprite* SetPosition(float x, float y);
		Sprite* SetRotation(float degree);
		Sprite* SetNumXFrames(int numXFrames);
		Sprite* SetNumYFrames(int numYFrames);
		Sprite* SetSize(float width, float height);
		Sprite* SetScale(float s);
		Sprite* SetBoundingBoxSize(float w, float h);
		Sprite* SetWireframe(bool wireframe);
		int GetTotalFrames();
		float GetRotation();
		float GetScale();
		float GetScaleWidth();
		float GetScaleHeight();
		BoundingBox* GetBoundingBox();
		vec2 GetPosition();
		vec2 GetRotatedPoint(float x, float y);
	private:
		BoundingBox* boundingBox;
		vec4 min;
		Shader* shader;
		Quad* quad;
		Texture* texture;
		float width = 0, height = 0, s = 1, degree = 0, frameDuration = 0, maxFrameDuration = 80;
		bool flipHorizontal = false, flipVertical = false, enableAnimation = false, wireframe = false;
		int numXFrames = 1, numYFrames = 1, frameIndex = 0;
		mat4 CreateTransform();
		void UpdateShaderData();
		AnimData* GetAnimData(string name);
		vec2 position;
		vector<AnimData*> animationData;
		AnimData* currentAnim = NULL;
		
	};
}

#endif

