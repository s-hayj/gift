

#include <stdio.h>
#include "gift.h"

using namespace gift;

class	Player
{
public:
	void DrawHead(RenderStates* pStates)
	{
		printf("Start_PlayerHead\n");
	};

	void DrawBody(RenderStates* pStates)
	{
		printf("Start_PlayerBody\n");
	};

	void DrawLeg(RenderStates* pStates)
	{
		printf("Start_PlayerLeg\n");
	};

	void EndDraw(RenderStates* pStates)
	{
		printf("End_Player\n");
	};
};

class	Enemy
{
public:
	void DrawEnemy(RenderStates* pStates)
	{
		printf("Start_Enemy\n");
	};

	void DrawEnemyBullet(RenderStates* pStates)
	{
		printf("Start_EnemyBullet\n");
	};

	void EndDraw(RenderStates* pStates)
	{
		printf("End_Enemy\n");
	};
};

/*
����t���[�����[�N���`��̎��s���Ԃ𐧌䂷�邱�Ƃ�O��ɁA
�l�Ă��ꂽ�N���X�̃e�X�g
*/
void Sample_DrawDelegate(void)
{
	using namespace gift::Renderable;

	Player player;

	DrawDelegate DrawPlayer(&player, Player::DrawHead,
		&DrawDelegate::Null<Player>());

	/*
	DrawDelegate �́A���g�ŕ`��̎��s���Ăяo�����Ƃ͂ł��Ȃ��B
	�{�����[�U�[�� ICommand�C���^�[�t�F�[�X���p�����Ď���������̂Ȃ̂����A
	DrawDelegate �́A�p���ł͂Ȃ��R���|�W�b�g�Ōp���̌���������A
	�t���[�����[�N�ɁA�`����@��o�^����B
	*/

	DrawPlayer.Register(gift::WriteMode::Overwrite, &player,
		&DrawDelegate::Null<Player>(), &DrawDelegate::Null<Player>());

	/*
	��L�̂悤�ɁA�ォ��`����e��ύX���邱�Ƃ��ł���B���̂Ƃ��̑������́A
	���łɓo�^����Ă���`����e�̏㏑���L�����w������B
	�̐S�ȕ`����e�����A���������Ȃ��Ƃ��A�������Ȃ������o�֐���o�^����Ƃ���
	�����ANULL�|�C���^���w��ł���悤�ɂ���B�������A�`����s�I�u�W�F�N�g��
	�����o�֐��łȂ���΂Ȃ�Ȃ����߁A�`����s�I�u�W�F�N�g�̃����o�֐��|�C���^
	�^�ɃL���X�g����NULL�|�C���^��񋟂ł���悤�ɁADrawDelete::Null<>��񋟁B
	�e���v���[�g�p�����[�^�[�́A�`����s�I�u�W�F�N�g�̌^���w�肵�Ĉꎞ�I�ɐ���
	����B&���Z�q���I�[�o�[���[�h���Ă���̂ŁA����Ő������ꂽ�^��NULL�|�C���^
	�������n����B
	���̕��@�Ƃ��āADRAWDELEGATE_NULL(T) �Ƃ����}�N���֐�������B
	*/

	DrawPlayer.Register(gift::WriteMode::Overwrite,
		&player, Player::DrawLeg, &DrawDelegate::Null<Player>());

	Command* pCommand = DrawPlayer;

	/*
	���g�ł͎��s�ł��Ȃ����߁AIDrawCommand �ɈϏ�����B
	��x���s���Ϗ�������A�����Ϗ����邱�Ƃ͂ł��Ȃ��B
	�܂��AIDrawCommnad �̔j�����Ϗ��������Ƃ�Y��Ȃ��悤��
	*/

	pCommand->DrawBegin(NULL);
	pCommand->DrawEnd(NULL);

	delete pCommand;
}
