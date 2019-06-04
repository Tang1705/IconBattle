#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <algorithm>

#include "Theme.h"
#include "User.h"

#include "BackButton.h"
#include "SettingButton.h"
#include "Dialog.h"

#include "StructNames.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

using std::pair;
using std::swap;
using std::set;
using namespace StructNames;

USING_NS_CC;

/*
 * 图层顺序
 * 从底到顶
 * -1层 宝石的背景板
 * 1+层 宝石
 * 10+层 主背景板+所有按钮
 * 20+层 结算结果框
 * 30+层 返回提示框
 */

class GameScene final :
	public Scene
{
public:
	static Scene* createScene(int stepNumber, int totalScore, bool isClassical, int hintNumber = 3);
	bool init() override { return Scene::init(); }
	CREATE_FUNC(GameScene)

private:
	bool isClassical = true;
	Theme* theme = Theme::getInstance();

#pragma region Information Board
	int stepNumber = 0;
	int hintNumber = 0;
	int totalScore = 0;
	int currentScore = 0;

	void setStepNumber(int step);
	void setTotalScore(int score);
	void setCurrentScore(int score);

	Label* stepNumberLabel = nullptr;
	Sprite* hintNumberSprite = nullptr;
	Label* scoreLabel = nullptr;
	Sprite* currentProgressBar = nullptr;
	ProgressTimer* progressController = nullptr;

	void initInformationBoard();

#pragma endregion

#pragma region Result Board
	void showResult(bool result);

#pragma endregion


#pragma region Game Board
	// 初始化棋盘和鼠标监听器
	void initGameBoard();

#pragma endregion
	// 不同模式得分，待调整
	const int threeScore = 100;
	const int fourScore = 150;
	const int fiveScore = 200;
	const int doubleThree = 300;
	const int otherDouble = 500;
	const int super = 800;
	const int doubleSuper = 10000;

	/*
	 * 标准模式：
	 * 三消
	 * 加强模式：
	 * 横四消：直接清除在本行的所有宝石
	 * 竖四消：直接清除在本列的所有宝石
	 * 横五消：直接清除在临近三行的所有宝石
	 * 竖五消：直接清除在临近三列的所有宝石
	 * 有交点的双三消：直接清除临近 3X3 的所有宝石
	 * 有交点的双三消+横或竖添加任意一至多个宝石：生成SUPER宝石
	 * SUPER宝石与某个颜色交换：消去整个画面中该颜色的宝石，两个SUPER换则刷新棋盘
	 */


	static const int BOARD_SIZE = 8;


	

	// 进行动画时锁定棋盘
	bool boardLocked = true;
	// 表示当前选中与否的两块
	pii selectedBlockF = {-1, -1};
	pii selectedBlockS = {-1, -1};

	blockInfo boardInfo[BOARD_SIZE * 2][BOARD_SIZE];

	int leftStepNumber = 0;

	// 由坐标得位置
	pii getPosition(pii index);
	// 由位置得坐标
	pii getIndex(pii pos);

	Actor* createActor(int, int, pii);

	// 获取可消除方块列表
	KillGroupList getKillList();

	// 尝试两方快交换：若不可以交换则不做动画，反之进行
	void trySwap(pii block1, pii block2);
	// 无效交换动画
	void failSwap(pii blocka, pii blockb);

	
	// 刷新棋盘：上半部分BFS填充，下半部分-1初始化
	void refreshBoard();

	// 方块交换动画
	void blockSwap(pii blocka, pii blockb);
	// 方块消除动画
	void blockVanish(KillGroupList killList);
	// 消除后新产生方块下落动画
	void newBlocksDrop();

	// 消除并下落动画回调函数：
	// 检测若新棋盘无可消除则unlock，否则继续消除
	void animationDoneCallback();

	// 判断是否为死局
	bool isDead();
	// 得到提示
	validOperateList getHintList();

	// 显示得分动画
	void showScore(int value, pii pos);
};

#endif
