#include "Lesson01_BgColor.h"

Engine::Lesson01_BgColor::Lesson01_BgColor(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Change Background Color";
}

Engine::Lesson01_BgColor::~Lesson01_BgColor()
{
}

//void Engine::Lesson01_BgColor::Init()
//{
//	r = 255;
//	g = 51;
//	b = 51;
//	mul = 1;
//}
//
//void Engine::Lesson01_BgColor::Update()
//{
//	if (color_duration >= 100) {
//		/*if (r <= 0 || r >= 255) {
//			mul *= -1;
//		}*/
//		//mul *= (r <= 0 || r >= 255) ? -1 : 1;
//		//r += mul * 5;
//		r += (mul *= (r <= 0 || r >= 255) ? -1 : 1) * 5;
//		g += (mul *= (g <= 0 || g >= 255) ? -1 : 1) * 9;
//		b += (mul *= (g <= 0 || g >= 255) ? -1 : 1) * 4;
//		SetBackgroundColor(r, g, b);
//		color_duration = 0;
//	}
//	color_duration += GetGameTime();
//}

void Engine::Lesson01_BgColor::Init()
{
	r = 255;
	g = 51;
	b = 51;
	mul = 1;
}

void Engine::Lesson01_BgColor::Update()
{
	color_duration += GetGameTime();	
	if (color_duration >= 100) {
		
		if (r == 255) {
			b = 255;
			r = 51;
		}

		if (b == 255) {
			g = 255;
			b = 51;
		}
		if (g == 255) {
			r = 255;
			g = 51;
		}
		SetBackgroundColor(r, g, b);
		
	}
	

	color_duration = 0;
}


//loop blue to red
//void Engine::Lesson01_BgColor::Init()
//{
//    r = 0;     // Start with red at 0
//    g = 0;     // Green stays at 0
//    b = 255;   // Start with blue at full intensity
//    mul = 1;   // Multiplier for color change
//    direction = 1; // Direction of color change (1 for blue to red, -1 for red to blue)
//}
//
//void Engine::Lesson01_BgColor::Update()
//{
//    if (color_duration >= 100) {
//        // Change color based on the current direction
//        if (direction == 1) {
//            // Transition from blue to red
//            b -= 5;  // Decrease blue intensity
//            r += 5;  // Increase red intensity
//
//            // Check if we have reached the transition point
//            if (b <= 0) {
//                b = 0; // Clamp blue to 0
//                r = 255; // Ensure red is at full intensity
//                direction = -1; // Change direction to red to blue
//            }
//        }
//        else {
//            // Transition from red to blue
//            b += 5;  // Increase blue intensity
//            r -= 5;  // Decrease red intensity
//
//            // Check if we have reached the transition point
//            if (r <= 0) {
//                r = 0; // Clamp red to 0
//                b = 255; // Ensure blue is at full intensity
//                direction = 1; // Change direction to blue to red
//            }
//        }
//
//        // Set the background color
//        SetBackgroundColor(r, g, b);
//
//        color_duration = 0;  // Reset color duration
//    }
//    color_duration += GetGameTime();  // Update color duration
//}





void Engine::Lesson01_BgColor::Render()
{

}

