#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::addAnimation(const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y,
	int width, int height)
{
	this->animations[key] = new Animation(sprite, textureSheet, animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y,
		width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority, const bool playOnce)
{
	//std::cout << "Animation play: " << key << std::endl;
	if (this->priorityAnimation) //if there is a priority animation
	{
		//std::cout << "Priority animation active" << std::endl;
		if (this->priorityAnimation == this->animations[key])
		{
			//std::cout << "Priority animation == Keyed in animation ("<<key<<")" << std::endl;
			if (this->lastAnimation != this->animations[key])
			{
				//reset all other animations except the one playing
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			// if the priority animation is done, remove it
			if (this->animations[key]->play(dt, playOnce))
			{
				this->priorityAnimation = nullptr;
			}
		}
		else
		{
			//std::cout << "Priority animation != keyed animation" << std::endl;
			if (this->priorityAnimation->play(dt, playOnce))
			{
				this->priorityAnimation = nullptr;
				return true;
			}
			else
				return false;
		}

	}
	else //play animation if no other priority animation is set
	{
		if (priority)
			this->priorityAnimation = this->animations[key];
		// reset all other animations when play new animation
		if (this->lastAnimation != this->animations[key]) //a new animation is being played
		{
			//reset all other animations except the one playing
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key]; //set last animation to current animation
			else
			{
				this->lastAnimation->reset(); //reset previously played animation
				this->lastAnimation = this->animations[key]; //set last animation as current animation
			}
		}
		this->animations[key]->play(dt, playOnce);
	}
	//std::cout << "Returning is done: " << this->animations[key]->isDone()<<std::endl;
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority, const bool playOnce)
{
	if (this->priorityAnimation) //if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				//reset all other animations except the one playing
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)), playOnce)
			{
				this->priorityAnimation = nullptr;
			}
		}
		else
		{
			return false;
		}
	}
	else //play animation if no other priority animation is set
	{
		// reset all other animations when play new animation
		if (this->lastAnimation != this->animations[key])
		{
			//reset all other animations except the one playing
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max), playOnce);
	}
	return this->animations[key]->isDone();
}
