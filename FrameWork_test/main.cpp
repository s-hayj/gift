
#include <crtdbg.h>
#include <stdio.h>
#include <assert.h>
#include "gift.h"
#include "test.h"

using namespace gift;

#define	MEM_BREAK NULL

extern void Sample_DeleteHelper(void);
extern void Sample_NewDelManager(void);
extern void Sample_ObjectBank(void);
extern void Sample_DrawDelegate(void);

void main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(MEM_BREAK);


	//	DeleteHelper<> の大まかな使い方
	Sample_DeleteHelper();

	//	NewDelManager<> の大まかな使い方
	Sample_NewDelManager();

	//	ObjectBank<> の大まかな使い方
	Sample_ObjectBank();

	//	DrawDelegate<> の大まかな使い方
	Sample_DrawDelegate();


	gift::Private::Renderable::Collection* pCollection =
		new gift::Private::Renderable::Collection();

	gift::Renderable::Component* pComponent = pCollection->OrderComponent();

	pComponent->Register(pCollection->OrderContainer(RenderStates(), false), true);
	pComponent->Connect(pCollection->OrderComponent());

	delete pComponent;

	delete pCollection;

	Math math;

	int a = math(Math::Add, 10, 10);
	float b = math(Math::Sub, 10.0f, 10);
	double c = math(Math::Mul, 10.0, 1.0f);
	char d = math(Math::Div, 600, 2);
}
