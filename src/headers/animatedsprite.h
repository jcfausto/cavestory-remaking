/*
 * animatedsprite.h
 *
 *  Created on: 9 de jun de 2017
 *      Author: jcfausto
 *
 *  Holds logic for animated sprites
 */

#ifndef HEADERS_ANIMATEDSPRITE_H_
#define HEADERS_ANIMATEDSPRITE_H_

#include <string>
#include <map>
#include <vector>
#include "sprite.h"
#include "globals.h"
#include "graphics.h"

//class Graphics;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
			int width, int height, float posX, float posY, float timeToUpdate);

	/* void playAnimation
	 * Plays the animation provided if it's not already playing
	 */
	void playAnimation(std::string animation, bool once = false);

	/* void update
	 * Updates the animated sprite (timer)
	 */
	void update(int elapsedTime);

	/* void draw
	 * Draws the sprite to the screen
	 */
	void draw(Graphics &graphics, int x, int y);

	/* void setupAnimations
	 * A required function that sets up all animations for a sprite
	 */
	virtual void setupAnimations();

protected:
	double timeToUpdate_;
	bool currentAnimationOnce_;

	std::string currentAnimation_;

	/* void addAnimation
	 * Add an animation to the map of animations for the sprite
	 */
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/* void resetAnimations
	 * Resets all animations associated with this sprite
	 */
	void resetAnimations();

	/* void stopAnimation
	 * Stops current animation
	 */
	void stopAnimation();

	/* void setVisibility
	 * Changes the visibility of the animated sprite
	 */
	void setVisible(bool visible);

	/* void animationDone
	 * Logic that happens everytime when the animation ends
	 */
	virtual void animationDone(std::string currentAnimation);
private:
	std::map<std::string, std::vector<SDL_Rect> > animations_;
	std::map<std::string, Vector2> offsets_;

	int frameIndex_;
	double timeElapsed_;
	bool visible_;
};

#endif /* HEADERS_ANIMATEDSPRITE_H_ */
