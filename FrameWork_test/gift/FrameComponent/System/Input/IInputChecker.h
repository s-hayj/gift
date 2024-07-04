//----------------------------------------------------------
//	@file	IInputChecker.h
//
//	@memo	���͂��ꂽ��Ԃ𒲂ׂ邽�߂̃C���^�[�t�F�[�X
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__IINPUT_CHECKER_H
#define	__IINPUT_CHECKER_H

//----------------------------------------------------------
//	@name	IInputChecker
//
//	@memo	���͏��𒲂ׂ�
//
//	@attrib	public template interface
//
//	@type	T	���ׂ���͏��t���O�̌^
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template< class T >
class	IInputChecker
{
public:
	//----------------------------------------------------------
	//	�w��̓��͂����͂��ꂽ
	//
	//	@name	IInputChecker::Push
	//
	//	@memo	�O�t���[���܂ł͓��͂����������Ƃ��̂ݔ���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	�m�F������̓t���O
	//
	//	@return	bool	true �Ȃ�A�����𖞂�����
	//----------------------------------------------------------
	virtual bool Push( T& input ) = 0;

	//----------------------------------------------------------
	//	�w��̓��͂�����Ă��邩�m�F����
	//
	//	@name	IInputChecker::Press
	//
	//	@memo	���t���[���œ��͂��m�F�ł����Ƃ��ɔ���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	�m�F������̓t���O
	//
	//	@return	bool	true �Ȃ�A�����𖞂�����
	//----------------------------------------------------------
	virtual bool Press( T& input ) = 0;

	//----------------------------------------------------------
	//	�w��̓��͂��r�₦�����m�F����
	//
	//	@name	IInputChecker::Release
	//
	//	@memo	�O�t���[���܂œ��͂���Ă���A���t���[���œ��͂���Ȃ��Ƃ�����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	�m�F������̓t���O
	//
	//	@return	bool	true �Ȃ�A�����𖞂�����
	//----------------------------------------------------------
	virtual bool Release( T& input ) = 0;

	//----------------------------------------------------------
	//	�w��̓��͏��ɕω��������m�F����
	//
	//	@name	IInputChecker::Change
	//
	//	@memo	�O�t���[���ƍ��t���[���ŁA���̗͂L���ɕω�������Ƃ��ɔ���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	�m�F������̓t���O
	//
	//	@return	bool	true �Ȃ�A�����𖞂�����
	//----------------------------------------------------------
	virtual bool Change( T& input ) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IInputChecker::~IInputChecker
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IInputChecker(void) {};
};

#endif