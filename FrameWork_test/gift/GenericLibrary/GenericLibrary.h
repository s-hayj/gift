//----------------------------------------------------------
// file name: GenericLibrary.h
//
// memo: ���ɗ��p�p�r����܂��Ă��Ȃ��I�u�W�F�N�g�Q
//----------------------------------------------------------

#ifndef	__GENERIC_LIBRARY_H
#define	__GENERIC_LIBRARY_H

namespace gift
{

const class MultiNull{				//	���� const �I�u�W�F�N�g��
public:
	MultiNull(){};
	template<class T>				//	������^�̔񃁃��o�ւ�
		operator T*() const{		//		�|�C���^�ɕϊ��ł���
			return 0;
	}
#ifndef	__MWERKS__
	template<class C, class T>		//	������^�̃����o�ւ�
		operator T C::*() const{	//		�|�C���^�ɂ��ϊ��ł���
			return 0;
	}
#endif	__MWERKS__
private:
	void operator &() const;		//	�A�h���X�͎擾�ł��Ȃ�
} Null;								//	Null �Ƃ������O������

//----------------------------------------------------------
// name: gift::NullType
//
// attrib: final class
//
// memo: null ���ʗp�̌^
//----------------------------------------------------------
class	NullType
{
};

//----------------------------------------------------------
// name: gift::Int2Type
//
// attrib: template final struct
//
// memo: ���l�ʂ̌^�𐶐�����
//----------------------------------------------------------
template<int v>
struct	Int2Type
{
	enum { value = v;};
};

//----------------------------------------------------------
// name: gift::WriteMode
//
// attrib: final class
//
// memo: �f�[�^�������ݎ��̓�������ʂ���
//----------------------------------------------------------
class	WriteMode
{
public:
	//----------------------------------------------------------
	// name: gift::WriteMode::MODE
	//
	// attrib: public enumerated
	//
	// memo: �f�[�^�������ݎ��̓���w��
	//----------------------------------------------------------
	enum	MODE
	{
		Once,		//	��x�����̏������݁i�㏑�����֎~����j
		Overwrite,	//	�㏑����������
	};
};

};//namespace gift

#endif
