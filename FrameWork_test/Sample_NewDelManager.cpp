
#include <stdio.h>
#include "gift.h"

//----------------------------------------------------------
//	���Ɍy���i����֐������j�N���X
//----------------------------------------------------------
template<int v = 0>
class	FactoryMethod
{
public:
	enum
	{
		value = v
	};

public:
	int*& Create( int*& pValue )
	{
		printf("FactoryMethod::Create()\n");

		pValue = new int( value );

		return pValue;
	};

	int*& Release( int*& pValue )
	{
		printf("FactoryMethod::Release()\n");

		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

//----------------------------------------------------------
//	int�^�𐶐�����O���[�o���֐�
//----------------------------------------------------------
int*& CreateFunction( int*& pValue )
{
	printf("CreateFunction()\n");

	pValue = new int(5);

	return pValue;
};

//----------------------------------------------------------
//	int�^��j������O���[�o���֐�
//----------------------------------------------------------
int*& ReleaseFunction( int*& pValue )
{
	printf("ReleaseFunction()\n");

	delete pValue;

	pValue = NULL;

	return pValue;
};

//----------------------------------------------------------
//	int�^�𐶐��A�j������ÓI�����o�֐����������N���X
//----------------------------------------------------------
class	StaticFactory
{
public:
	static int*& Create( int*& pValue )
	{
		printf("StaticFactory::Create()\n");

		pValue = new int(0);
		return pValue;
	};

	static int*& Release( int*& pValue )
	{
		printf("StaticFactory::Release()\n");

		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

//----------------------------------------------------------
//	�d���i����̓����o�ϐ��̂݁j�N���X
//----------------------------------------------------------
class	Factory
{
public:
	int _value;

public:
	Factory(void) : _value( 0 )
	{
	};

	int*& Create( int*& pValue )
	{
		printf("Factory::Create()\n");

		pValue = new int( _value );

		return pValue;
	};

	int*& Release( int*& pValue )
	{
		printf("Factory::Release()\n");

		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

void Sample_NewDelManager(void)
{
	/*
	�e���v���[�g�p�����[�^�[�ɂ���Ď��ʂ����A�C�ӂ̌^��
	���[�U�[�w��̐������@�A�j�����@�Ŏ�舵����悤�ɂ���N���X
	*/

	FactoryMethod<10> funObj;

	gift::NewDelManager<int*> fun(CreateFunction, ReleaseFunction);
	gift::NewDelManager<int*> Fun(StaticFactory::Create, StaticFactory::Release);
	gift::NewDelManager<int*> FunObj(funObj, FactoryMethod<10>::Create,
		funObj, FactoryMethod<10>::Release);

	/*
	�e���v���[�g�p�����[�^�[�ɂ́A�����E�j���������Ɉ����n���ϐ��̌^�������B
	����ɁA�������ʂ�Ԃ��Ƃ��̖߂�l�̌^�ɂ��Ȃ�B
	��L�̋L�q�͏ォ��A�֐��|�C���^�̓o�^�A�ÓI�����o�֐��ɂ��֐��|�C���^�A
	�����o�֐��|�C���^�̓o�^�ɂ��A���ꂼ�ꐶ���Ɣj�����ϑ����Ă���B

	�����A�j�����ɂ́A�������{���Ώۂւ̏�񂵂������Ƃ��ēn�����Ƃ��ł��Ȃ��B
	�܂��A�O�ڂ̂悤�ɃI�u�W�F�N�g�ƁA�����o�֐��|�C���^��o�^���Ă���̂́A
	�I�u�W�F�N�g���R�s�[���Ă���̂ł͂Ȃ��A�I�u�W�F�N�g�̌^�����ʂ��Ă���
	�����Ȃ̂ŁA������������ɓƎ��̃p�����[�^�[��n�����Ƃ��ł��Ă��Ȃ��B

	�����ŁA�����̉��P��Ƃ��āA�e���v���[�g�� 10 �Ƃ����萔���`���A��������
	�����l�Ƃ��Ă���B�������A����ŉ��������Ƃ͂ƂĂ�������B
	*/

	int* pInt = 0;

	fun.Initialize( pInt );
	fun.Release( pInt );

	Fun.Initialize( pInt );
	Fun.Release( pInt );

	FunObj.Initialize( pInt );
	FunObj.Release( pInt );

	/*
	��L�̂悤�ɁA���ꂼ�� Initialize() �Ő����ARelease() �Ŕj���̎��s��
	�s���Ă���A���̈����ɂ́A�������ʂ��i�[��������ƁA�j�����s��������
	�w�肳��Ă���B
	*/

	Factory* pFactory = new Factory();

	pFactory->_value = 20;

	gift::NewDelManager<int*> ObjFun(pFactory, Factory::Create,
		pFactory, Factory::Release);

	/*
	��L�̂悤�ɁA�I�u�W�F�N�g�ւ̃|�C���^�ƁA���̃����o�֐��|�C���^���w��
	���邱�ƂŁA�I�u�W�F�N�g�̏��𗘗p���������Ɣj�����s����\�����
	���Ă���B���R�ANewDelManager<> �̐����A�j���������s����܂ŁA������
	�I�u�W�F�N�g���������l��ێ����Ă��邱�Ƃ��ۏႳ��Ă��Ȃ���΂Ȃ�Ȃ��B
	*/

	FunObj = ObjFun;

	FunObj.Initialize( pInt );
	FunObj.Release( pInt );

	//	�ϑ������̂ŁA�����E�j���͍s���Ȃ�
	ObjFun.Initialize( pInt );
	ObjFun.Release( pInt );

	delete pFactory;

	/*
	��L�̂悤�ɁA�����p�����[�^�[�ł���Ȃ�A�ӔC���ϑ����邱�Ƃ��ł���B
	���̂Ƃ��A�ϑ��Ώۂ����łɐӔC��ێ����Ă����ꍇ�B�㏑������Ă��܂��B
	�܂��A�ϑ������ꍇ�B�����̎��s�̓X���[����Ă��܂��B

	�����܂łł́A�������\�b�h�A�j�����\�b�h�Ƃ��Ɋ֐��|�C���^��A
	�����o�֐��|�C���^�ŁA�o�����ɋ��ʂ���Ă������A���̂悤�Ȍ��܂�͖���
	*/

	gift::NewDelManager<int*> Function_Method(CreateFunction,
		funObj, FactoryMethod<10>::Release);

	Function_Method.Initialize( pInt );
	Function_Method.Release( pInt );

	/*
	��L�̂悤�ɁA���R�ȑg�ݍ��킹���\�ɂȂ��Ă���B
	*/
}
