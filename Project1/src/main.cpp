#include "Display/Display.h"
#include "Display/Renderer.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
	Scene mainScene;
	Display mainDisplay;
	Renderer mainRenderer;
	mainDisplay.Initialize();
	mainRenderer.Initialize(mainDisplay);

	mainScene.camXform = IdentityMatrix();

	mainScene.triangle[0] = VectorPoint( 0.0f,  1.0f,  0.0f);
	mainScene.triangle[1] = VectorPoint( 1.0f,  0.0f,  0.0f);
	mainScene.triangle[2] = VectorPoint(-1.0f,  0.0f,  0.0f);

	mainScene.triangleXform = IdentityMatrix();
	mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection(0.0f, 0.0f, 10.0f));

	mainScene.camXform = IdentityMatrix();

	while (!mainDisplay.quitRequested)
	{
		//Poll for events sent by OS:
		mainDisplay.PollEvents();

		//Update loop:
		{
			float speed = 0.01f;
			if (GetAsyncKeyState('Z')) { mainScene.fov -= speed; }
			if (GetAsyncKeyState('C')) { mainScene.fov += speed; }

			if (GetAsyncKeyState('W')) { mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection(  0.0f,   0.0f,  speed)); }
			if (GetAsyncKeyState('S')) { mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection(  0.0f,   0.0f, -speed)); }
			if (GetAsyncKeyState('E')) { mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection(  0.0f, -speed,   0.0f)); }
			if (GetAsyncKeyState('Q')) { mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection(  0.0f,  speed,   0.0f)); }
			if (GetAsyncKeyState('D')) { mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection( speed,   0.0f,   0.0f)); }
			if (GetAsyncKeyState('A')) { mainScene.triangleXform = mainScene.triangleXform * TranslationMatrix(VectorDirection(-speed,   0.0f,   0.0f)); }

			if (GetAsyncKeyState('I')) { mainScene.triangleXform = mainScene.triangleXform * RotationMatrix(QuaternionNormalize(Quaternion(1.0f,  speed,   0.0f,   0.0f))); }
			if (GetAsyncKeyState('K')) { mainScene.triangleXform = mainScene.triangleXform * RotationMatrix(QuaternionNormalize(Quaternion(1.0f, -speed,   0.0f,   0.0f))); }
			if (GetAsyncKeyState('L')) { mainScene.triangleXform = mainScene.triangleXform * RotationMatrix(QuaternionNormalize(Quaternion(1.0f,   0.0f,  speed,   0.0f))); }
			if (GetAsyncKeyState('J')) { mainScene.triangleXform = mainScene.triangleXform * RotationMatrix(QuaternionNormalize(Quaternion(1.0f,   0.0f, -speed,   0.0f))); }
			if (GetAsyncKeyState('O')) { mainScene.triangleXform = mainScene.triangleXform * RotationMatrix(QuaternionNormalize(Quaternion(1.0f,   0.0f,   0.0f,  speed))); }
			if (GetAsyncKeyState('U')) { mainScene.triangleXform = mainScene.triangleXform * RotationMatrix(QuaternionNormalize(Quaternion(1.0f,   0.0f,   0.0f, -speed))); }

			Matrix4x4 projMat = PerspectiveProjectionMatrix(mainScene.fov, (float)mainDisplay.width / (float)mainDisplay.height, 10000.0f, 0.1f);
			mainScene.invProjection = MatrixInverse(projMat);
		}

		//Render loop:
		{
			mainDisplay.ClearPixelbuffer();
			mainRenderer.Render(mainScene);
			mainDisplay.FlipFromIntPtr(mainRenderer.GetResult());
			mainDisplay.PresentPixelbufferToWindow();
		}
	}

	mainRenderer.ShutDown();
	mainDisplay.Shutdown();
	return 0;
}
