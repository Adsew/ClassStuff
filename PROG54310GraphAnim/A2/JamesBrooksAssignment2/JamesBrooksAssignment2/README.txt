Assignment 2
Student: James Brooks

Compiling
-----------

Should compile without modification.
May require retargeting solution and changing compile mode to x86.
Sometimes when opening the solution for the first time it auto
changes to x64 (which, of course, does not work with our libraries).



Everything is implemented from assignment page.

Everything is textured.

Ground has two textures, grass and bananas.

Three lights:
    One forward in distance, white light with bright ambience and large specular.
    One to the left, white light, medium ambient, small specular.
    One directional from the star, only shines forward-right from the star
        position. Red light with no specular.

Bonuses:

Depth Effect: Depth test allows objects to render in order of depth.

Direction lighting: A light (The star in the middle) shines a red
    light in a single direction at the monster. The star looks bad
    since the lighting comes from the center and goes in one direction,
    but it showcases that the light goes in only one direciton.



CONTROLS
--------------
W - move forward
S - move backward
A - move left
D - move right
Q - rotate left
E - rotate right
R - ascend up
F - descend down

You can move and rotate freely and properly.
Rotation appropriately effects movement direction.
