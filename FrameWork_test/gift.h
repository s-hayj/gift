//----------------------------------------------------------
// file name: gift.h
//
// memo: ÅiâºÅjgeneric fream work technic
//----------------------------------------------------------

#ifndef	__GIFT_H
#define	__GIFT_H

#include "gift/GenericLibrary.h"
#include "gift/NewDelManager.h"
#include "gift/ObjectBank.h"
#include "gift/DeleteHelper.h"
#include "gift/DrawDelegate.h"
#include "gift/RenderableCollection.h"

namespace gift
{
	namespace Renderable
	{
		typedef IDrawCommand Command;
		typedef IRenderableCollection Collection;
		typedef IRenderableContainer Container;
		typedef IRenderableComponent Component;
	};

	namespace Private
	{
		namespace Renderable
		{
			typedef StandardRenderableContainer StandardContainer;
			typedef RenderableContainer Container;
			typedef RenderableCollection Collection;
			typedef RenderableComponent Component;
		};
	};
};

#endif
