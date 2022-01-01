#include "AcGame.h"

void AcGame::Init()
{
	this->baseAddress  = (int)GetModuleHandle(L"client.dll");
	Init_base_address();
}


void AcGame::Init_base_address()
{
	AC::Base::MatrixAddress = (Matrixf*)GAME_OFFSET(0x4dc23b4);
}

void AcGame::SetModuleBaseAddress(WCHAR* str)
{
	DWORD id = GetCurrentProcessId();
	baseAddress = UTIL::dwGetModuleBaseAddress(id, (TCHAR*)str);
}

void AcGame::DrawBox()
{
	for (int i = 1; i < this->numPlayers ; i++)
	{
		player* ent = entiylist->entList_arry[i].player_ptr;
		if (!ent)
			break;
		playerinfo_t playerinfo(ent, (float)AC::Base::WindowWidth, (float)AC::Base::WindowHeigth);
		if (playerinfo.isValid)
		{
			DrawOnePlayer(&playerinfo);
		}
	}
}

void AcGame::DrawOnePlayer(playerinfo_t* playerinfo)
{
	ImDrawList* Draw = ImGui::GetBackgroundDrawList();

	float Height = playerinfo->pos2D.y - playerinfo->headpos2D.y;

	float BoxWidth = Height / 2;
	float BoxHeigth = Height;

	ImVec2 TopLeft = { playerinfo->headpos2D.x - BoxWidth / 2,playerinfo->headpos2D.y };
	ImVec2 BottomLeft = { playerinfo->headpos2D.x - BoxWidth / 2 ,playerinfo->pos2D.y };
	ImVec2 BottomRight = { playerinfo->headpos2D.x + BoxWidth / 2 ,playerinfo->pos2D.y };
	ImVec2 TopRight = { playerinfo->headpos2D.x + BoxWidth / 2,playerinfo->headpos2D.y };

	ImColor BoxColor_enemy = { 0xff,0,0,0xff };
	ImColor BoxColor_friend = { 0,0xff,0,0xff };

	ImColor health_armor_color;
	if (playerinfo->ent->health > 70)
		health_armor_color = { 0,0,0xFF ,0xFF };
	else if (playerinfo->ent->health > 30 && playerinfo->ent->health <= 70)
		health_armor_color = { 0xff,0xff,0 ,0xFF };
	else
		health_armor_color = { 0xff,0,0  ,0xFF };

	ImColor BoxColor = local_player->team == playerinfo->ent->team ? BoxColor_friend : BoxColor_enemy;

	Draw->AddQuad(TopLeft, BottomLeft, BottomRight, TopRight, BoxColor, 2.0f);
	Draw->AddQuad({ 11,11 }, { 11,200 }, { 200,200 }, { 200,11 },BoxColor, 2.0f);

	//  绘制血条
	float current_health = static_cast<float>(playerinfo->ent->health) / 100.0f;

	TopLeft = ImVec2(BottomLeft.x, BottomLeft.y + (TopLeft.y - BottomLeft.y) * current_health);

	Draw->AddLine(TopLeft, BottomLeft, health_armor_color, 6.0f);
	// 绘制护甲

	//float current_armor= static_cast<float>(playerinfo->ent->armor) / 100.0f;

	//TopRight = ImVec2(BottomRight.x, BottomRight.y + (TopRight.y - BottomRight.y) * current_armor);

	//Draw->AddLine(TopRight, BottomRight, health_armor_color, 6.0f);
}

playerinfo_t::playerinfo_t(player* ent, float width, float height)
{
	if (!ent)
		return;
	bool check = true;
	this->ent = ent;
	if (check )
	{
		this->headpos3D = this->ent->pos_3;
		this->pos3D = this->ent->pos_3;
		this->headpos3D.y += 50;
		check &= WorldToScreen(this->pos3D, &this->pos2D);
		check &= WorldToScreen(this->headpos3D, &this->headpos2D);
		this->isValid = check;
	}
	else
	{
		this->isValid = false;
	}
}

