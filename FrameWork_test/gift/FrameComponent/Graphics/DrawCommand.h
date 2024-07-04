//----------------------------------------------------------
//	@file	DrawCommand.h
//
//	@memo	�`�揈���̓o�^�Ɋւ��鐧��
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__DRAW_COMMAND_H
#define	__DRAW_COMMAND_H

#include "IRenderable.h"

//----------------------------------------------------------
//	@name	DrawCommand
//
//	@memo	�`�惁�\�b�h���i�[�A�o�^���쐧��
//
//	@attrib	public final class
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	DrawCommand
{
private:
	//----------------------------------------------------------
	//	@name	DrawCommand::FunctionObject
	//
	//	@memo	�֐��I�u�W�F�N�g�̕`�惁�\�b�h�i�[�p
	//
	//	@attrib	private nested template final sub class
	//
	//	@type	T	�֐��I�u�W�F�N�g�̌^
	//
	//	@base	public IRenderable
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template< class T >
	class	FunctionObject
		: public IRenderable
	{
	public:
		typedef	typename void (T::*Method)(RenderState*);

	private:
		T		_obj;	//	�Ăяo���I�u�W�F�N�g
		Method*	_pFun;	//	�Ăяo�����\�b�h

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	DrawCommand::FunctionObject::FunctionObject
		//
		//	@attrib	public
		//
		//	@attrib	(in)pFunction	�Ăяo���`�惁�\�b�h�ւ̃|�C���^
		//----------------------------------------------------------
		FunctionObject( Method* pFunction )
			: _pFun( pFunction )
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	DrawCommand::FunctionObject::~FunctionObject
		//
		//	@attrib	public
		//----------------------------------------------------------
		~FunctionObject(void)
		{
		};

		//----------------------------------------------------------
		//	�o�^���ꂽ�`�摀�상�\�b�h���Ăяo��
		//
		//	@name	DrawCommand::FunctionObject::Draw
		//
		//	@memo	�ԐړI�ɕ`�惁�\�b�h���Ăяo�����p������
		//
		//	@attrib	public override
		//
		//	@base	IRenderable::Draw
		//
		//	@param	(in/out)pState	�`��Ɋւ�����Q
		//
		//	@return	none
		//----------------------------------------------------------
		void Draw( RenderState* pState )
		{
			(_obj.*_pFun)( pState );
		};
	};

	//----------------------------------------------------------
	//	@name	Function
	//
	//	@memo	�ÓI�Ȋ֐����i�[����
	//
	//	@attrib	private nested final sub class
	//
	//	@base	public IRenderable
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	class	Function
		: public IRenderable
	{
	public:
		typedef typename void (*Method)(RenderState*);

	private:
		Method*	_pFun;	//	�Ăяo���֐��ւ̃|�C���^

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	DrawCommand::Function::Function
		//
		//	@attrib	public
		//
		//	@param	(in)pFunction	�Ăяo���֐��ւ̃|�C���^
		//----------------------------------------------------------
		Function( Method* pFunction)
			: _pFun( pFunction )
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	DrawCommand::Function::~Function
		//
		//	@attrib	public
		//----------------------------------------------------------
		~Function(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[���Ă���֐����Ăяo��
		//
		//	@name	DrawCommand::Function::Draw
		//
		//	@memo	�ԐړI�ɕ`�惁�\�b�h���Ăяo��
		//
		//	@attrib	public override
		//
		//	@base	IRenderable::Draw
		//
		//	@param	(in/out)pState
		//
		//	@return	none
		//----------------------------------------------------------
		void Draw( RenderState *pState )
		{
			(*_pFun)( pState );
		};
	};

	//----------------------------------------------------------
	//	@name	DrawCommand::ObjectMethod
	//
	//	@memo	�I�u�W�F�N�g�̃����o�֐����i�[����
	//
	//	@attrib	private nested template final sub class
	//
	//	@type	T	�o�^����I�u�W�F�N�g�̌^
	//
	//	@base	public IRenderable
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template< class T >
	class	ObjectMethod
		: public IRenderable
	{
	public:
		typedef typename void (T::*Method)(RenderState*);

	private:
		T*		_pObj;	//	�Ăяo���I�u�W�F�N�g�ւ̃|�C���^
		Method*	_pFun;	//	�Ăяo�����\�b�h�ւ̃|�C���^

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	DrawCommand::ObjectMethod::ObjectMethod
		//
		//	@attrib	public
		//
		//	@param	(in)pObject		�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
		//	@param	(in)pFunction	�Ăяo�������o�֐��ւ̃|�C���^
		//----------------------------------------------------------
		ObjectMethod( T* pObject, Method* pFunction )
			: _pObj(pObject), _pFunction(pFunction)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	DrawCommand::ObjectMethod::~ObjectMethod
		//
		//	@attrib	public
		//----------------------------------------------------------
		~ObjectMethod(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[�����o�֐����Ăяo��
		//
		//	@name	DrawCommand::ObjectMethod::Draw
		//
		//	@memo	�`�惁�\�b�h���ԐړI�ɌĂяo��
		//
		//	@attrib	public override
		//
		//	@base	IRenderable::Draw
		//
		//	@param	(in/out)pState
		//
		//	@return	none
		//----------------------------------------------------------
		void Draw( RenderState* pState )
		{
			(_pObj->*_pFun)(pState);
		};
	};

private:
	IRenderable*	_pRender;	//	�Ԑڕ`�摀��I�u�W�F�N�g

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	DrawCommand::DrawCommnad
	//
	//	@attrib	public
	//
	//	@param	(in)pFunction	�Ăяo���֐��ւ̃|�C���^
	//----------------------------------------------------------
	DrawCommand( void (*pFunction)(RenderState*) )
		: _pRender( NULL )
	{
		//	�ÓI�Ȋ֐����i�[����
		_pRender = new DrawCommand::Function( pFunction );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	DrawCommand::DrawCommand
	//
	//	@attrib	public template
	//
	//	@type	T	�Ăяo���I�u�W�F�N�g�̌^
	//
	//	@param	(in)object		�`��Ăяo�����̃I�u�W�F�N�g
	//	@param	(in)pFunction	�Ăяo���`�摀�상���o�֐��|�C���^
	//----------------------------------------------------------
	template< class T >
		DrawCommand( T& object, typename void (T::*pFunction)(RenderState*) )
		: _pRender( NULL )
	{
		//	�֐��I�u�W�F�N�g�̃����o�֐����i�[����
		_pRender = new DrawCommand::FunctionObject< T >( pFunction );
	}

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	DrawCommand::DrawCommand
	//
	//	@attrib	public template
	//
	//	@type	T	�Ăяo���I�u�W�F�N�g�̌^
	//
	//	@param	(in)pObject		�`��Ăяo�����ւ̃|�C���^
	//	@param	(in)pFunction	�Ăяo���`�摀�상���o�֐��|�C���^
	//----------------------------------------------------------
	template< class T >
		DrawCommand( T* pObject, typename void (T::*pFunction)(RenderState*) )
		: _pRender( NULL )
	{
		//	�I�u�W�F�N�g�̃����o�֐����i�[����
		_pRender = new DrawCommand::ObjectMethod< T >( pObject, pFunction );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	DrawCommand::DrawCommnad
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	DrawCommnad(void)
		: _pRender( NULL )
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	DrawCommand::~DrawCommand
	//
	//	@attrib	public
	//----------------------------------------------------------
	~DrawCommand(void)
	{
		//	�Ăяo���I�u�W�F�N�g��j������
		this->Release();
	};

	//----------------------------------------------------------
	//	�`�摀��̌Ăяo������ēo�^����
	//
	//	@name	DrawCommand::Register
	//
	//	@memo	�֐��I�u�W�F�N�g�̕`�惁�\�b�h��o�^����
	//
	//	@attrib	public template
	//
	//	@type	T	�Ăяo���I�u�W�F�N�g�̌^
	//
	//	@param	(in)object		�`��Ăяo�����̃I�u�W�F�N�g
	//	@param	(in)pFunction	�Ăяo���`�摀�상���o�֐��|�C���^
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Register( T& object, typename void (T::*pFunction)(RenderState*) )
	{
		//	�o�^���̃��\�b�h��j������
		this->Release();

		//	�֐��I�u�W�F�N�g�̕`�惁�\�b�h��o�^����
		_pRender = new DrawCommand::FunctionObject< T >( pFunction );
	};

	//----------------------------------------------------------
	//	�`�摀��̌Ăяo������ēo�^����
	//
	//	@name	DrawCommand::Register
	//
	//	@memo	�ÓI�Ȋ֐���o�^����
	//
	//	@attrib	public
	//
	//	@param	(in)pFunction	�Ăяo���`�摀��֐��|�C���^
	//
	//	@return	none
	//----------------------------------------------------------
	void Register( void (*pFunction)(RenderState*) )
	{
		//	�o�^���̃��\�b�h��j������
		this->Release();

		//	�ÓI�Ȋ֐��|�C���^��o�^����
		_pRender = new DrawCommand::Function( pFunction );
	};

	//----------------------------------------------------------
	//	�`�摀��̌Ăяo������ēo�^����
	//
	//	@name	DrawCommand::Register
	//
	//	@memo	�I�u�W�F�N�g�̃����o�֐���o�^����
	//
	//	@attrib	public template
	//
	//	@type	T	�Ăяo���I�u�W�F�N�g�̌^
	//
	//	@param	(in)pObject		�`��Ăяo�����̃I�u�W�F�N�g
	//	@param	(in)pFunction	�Ăяo���`�摀�상���o�֐��|�C���^
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Register( T* pObject, typename void (T::*pFunction)(pFunction) )
	{
		//	�o�^���̃��\�b�h��j������
		this->Register();

		//	�I�u�W�F�N�g�̃����o�֐���o�^����
		_pRender = new DrawCommand::ObjectMethod( pObject, pFunction );
	};

	//----------------------------------------------------------
	//	�o�^���\�b�h��j������
	//
	//	@name	DrawCommand::Release
	//
	//	@memo	�Ăѓo�^������܂ŏ������X���[����
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Release(void)
	{
		//	�j������Ă��Ȃ�
		if ( _pRender )
		{
			delete _pRender;
			_pRender = NULL;
		}
	};

	//----------------------------------------------------------
	//	�`��Ăяo����̃C���^�[�t�F�[�X���Q�Ƃ���
	//
	//	@name	DrawCommand::GetRenderable
	//
	//	@memo	�o�^�����`�摀����ԐړI�ɌĂяo���C���^�[�t�F�[�X��Ԃ�
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	IRenderable*	NULL	�o�^�Ɏ��s�������́A���o�^
	//----------------------------------------------------------
	IRenderable* GetRenderable(void)
	{
		return _pRender;
	};

	//----------------------------------------------------------
	//	�`��Ăяo����̃C���^�[�t�F�[�X���Q�Ƃ���
	//
	//	@name	DrawCommand::operator IRenderable*
	//
	//	@memo	�ÖٓI�^�ϊ�
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	IRenderable*	NULL	�o�^�Ɏ��s�������́A���o�^
	//----------------------------------------------------------
	operator IRenderable* (void)
	{
		return _pRender;
	};

private:
	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^
	//
	//	@name	DrawCommand::DrawCommnad
	//
	//	@memo	�R�s�[�R���X�g���N�^���֎~����
	//
	//	@attrib	private
	//
	//	@param	(in)object	�R�s�[����f�[�^�Ώ�
	//----------------------------------------------------------
	DrawCommand( DrawCommand& object )
	{
	};

	//----------------------------------------------------------
	//	������Z�q�̃I�[�o�[���[�h
	//
	//	@name	DrawCommand::operator =
	//
	//	@memo	������֎~����
	//
	//	@attrib	private
	//
	//	@param	(in)object	������ւ̎Q��
	//
	//	@param	none
	//----------------------------------------------------------
	void operator = ( DrawCommand& object )
	{
	};
};

#endif