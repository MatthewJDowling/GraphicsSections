#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\Draw.h"
#include "graphics\genShape.h"
#include "graphics\Load.h"
#include "graphics\GameObjects.h"

#include"glm/ext.hpp"


void main()
{
	SpecGloss Presets[50];
	createAllAssets(Presets, 50);

	SpecGloss LotsOfSpears[10];

	int IndexIamLookingFor = -1;

	for (int i = 0; i < 10; i++)
	{
		if (IndexIamLookingFor == -1)
		{
			for (int j = 0; j < 50; j++)
			{
				if (Presets[j].objName == "GLOSSY AS FUCK SOUL SPEAR")
				{
					IndexIamLookingFor = j;

				}
			}
		}
		
		LotsOfSpears[i] = Presets[IndexIamLookingFor];
	}
	

}