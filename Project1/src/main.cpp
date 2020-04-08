#include "Display/Display.h"
#include "Display/Renderer.h"
#include "Scene/Scene.h"

#include <iostream>

int main()
{
	Scene mainScene;
	Display mainDisplay;
	Renderer mainRenderer;

	//Initialize the scene:
	mainScene.meshArray.push_back(Mesh(0, 0, 1));
	mainScene.meshArray.push_back(Mesh(1, 0, 1));

	mainScene.meshXformArray.push_back(IdentityMatrix() * TranslationMatrix(VectorDirection(0.0f, 0.0f, 10.0f)));
	mainScene.meshXformArray.push_back(IdentityMatrix() * TranslationMatrix(VectorDirection(0.0f, 0.0f, 12.0f)));

	mainScene.indexArray.push_back(Index(0, 1, 2, Colour(), Colour()));

	mainScene.verticies.push_back(VectorPoint( 0.0f, 1.0f, 0.0f));
	mainScene.verticies.push_back(VectorPoint( 1.0f, 0.0f, 0.0f));
	mainScene.verticies.push_back(VectorPoint(-1.0f, 0.0f, 0.0f));

	mainScene.camXform = IdentityMatrix();
	
	//Initialize rendering systems:
	mainDisplay.Initialize();
	mainRenderer.Initialize(mainDisplay, mainScene);

	//Start game loop:
	while (!mainDisplay.quitRequested)
	{
		//Poll for events sent by OS:
		mainDisplay.PollEvents();

		//Update loop:
		{
			float speed = 0.01f;

			Matrix4x4& m1 = mainScene.meshXformArray[0];
			Matrix4x4& m2 = mainScene.meshXformArray[1];

			if (GetAsyncKeyState('A')) { m1 = m1 * TranslationMatrix(VectorDirection(-speed,   0.0f,   0.0f)); }
			if (GetAsyncKeyState('D')) { m1 = m1 * TranslationMatrix(VectorDirection( speed,   0.0f,   0.0f)); }
			if (GetAsyncKeyState('W')) { m2 = m2 * TranslationMatrix(VectorDirection(  0.0f,  speed,   0.0f)); }
			if (GetAsyncKeyState('S')) { m2 = m2 * TranslationMatrix(VectorDirection(  0.0f, -speed,   0.0f)); }
			if (GetAsyncKeyState('Q')) { m1 = m1 * TranslationMatrix(VectorDirection(  0.0f,   0.0f,  speed)); }
			if (GetAsyncKeyState('E')) { m1 = m1 * TranslationMatrix(VectorDirection(  0.0f,   0.0f, -speed)); }
			if (GetAsyncKeyState('Z')) { m2 = m2 * TranslationMatrix(VectorDirection(  0.0f,   0.0f,  speed)); }
			if (GetAsyncKeyState('C')) { m2 = m2 * TranslationMatrix(VectorDirection(  0.0f,   0.0f, -speed)); }

			Matrix4x4 projMat = PerspectiveProjectionMatrix(mainScene.fov, (float)mainDisplay.width / (float)mainDisplay.height, 10000.0f, 0.1f);
			mainScene.invProjection = MatrixInverse(projMat);
		}

		//Render loop:
		{
			mainDisplay.ClearPixelbuffer();
			mainRenderer.Render();
			mainDisplay.PresentPixelbufferToWindow();
		}
	}

	mainRenderer.ShutDown();
	mainDisplay.Shutdown();
	return 0;
}
