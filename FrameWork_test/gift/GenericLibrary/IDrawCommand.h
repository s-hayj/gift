//----------------------------------------------------------
// file name: IDrawCommand.h
//
// memo: �`�掞�̊e���s���\�b�h���Ϗ����邽�߂̃C���^�[�t�F�[�X
//----------------------------------------------------------

#ifndef	__IDRAW_COMMAND_H
#define	__IDRAW_COMMAND_H

#include "RenderStates.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IDrawCommand
//
// attrib: interface
//
// memo: �`����s���̊e�Ăяo���p�C���^�[�t�F�[�X
//----------------------------------------------------------
class	IDrawCommand
{
public:
	virtual ~IDrawCommand(void) {};

	//----------------------------------------------------------
	//	�`������s����
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//----------------------------------------------------------
	virtual void DrawBegin(RenderStates* pStates) = 0;

	//----------------------------------------------------------
	//	�`��̌㏈�������s����
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//----------------------------------------------------------
	virtual void DrawEnd(RenderStates* pStates) = 0;
};

	};//namespace Renderable
};//namespace gift

#endif
