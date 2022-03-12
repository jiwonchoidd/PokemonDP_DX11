#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"
//ImVec4 login_text_color = ImVec4(1.0f,1.0f,1.0f,1.0f);
////WSAAsyncSelect
//LRESULT  Sample::ExternMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	return m_Net.Select_MsgProc(hWnd, msg, wParam, lParam);
//}
bool Sample::Init()
{
	#pragma region 네트워크 초기화
	//auto size = static_cast<DWORD>((sizeof(char)*24)+1);
	//if (!GetComputerNameA(computer_name, &size))
	//{
	//	strcat(computer_name, "NoName");
	//}

	//m_Net.InitNetwork();
	////타입 포트 아이피
	//if(m_Net.Connect(g_hWnd, SOCK_STREAM, 10000, ip_Address))
	//{
	//	m_bConnect = true;
	//}
#pragma endregion

    //사운드 초기화 
	g_SoundManager.Init();
	//씬 매니져
	g_SceneManager.Init(m_pImmediateContext);

    return true;
}
// 프레임 함수
bool Sample::Frame()
{
	#pragma region IMGUI INTERFACE
	//(m_Net.m_bConnect)? str_isConnect = "Online" : str_isConnect = "Offline";
	//(m_Net.m_bConnect)? login_text_color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f) :
	//					login_text_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

	//if (ImGui::Begin("Chat"))
	//{
	//	
	//	ImGui::TextColored(login_text_color,str_isConnect.c_str());
	//	//연결이 안되어 있으면 연결 재 시도
	//	if (!m_Net.m_bConnect)
	//	{
	//		ImGui::InputText("아이피 입력", ip_Address, sizeof(char) * 30);
	//		ImGui::SameLine();
	//		if (ImGui::Button(u8"연결 재시도"))
	//		{
	//			if (m_Net.Connect(g_hWnd, SOCK_STREAM, 10000, ip_Address))
	//			{
	//				m_bConnect = true;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		ImGui::BeginChild(u8"채팅창", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing() - 15));
	//		ImGui::Text(m_chatItems);
	//		ImGui::EndChild();
	//		ImGui::Dummy(ImVec2(0.0f, 5));
	//		ImGui::InputText("", m_buffer, sizeof(m_buffer));
	//		
	//		ImGui::SameLine();

	//		if (ImGui::Button("Send") || g_InputData.bEnter)
	//		{
	//			char clear[MAX_PATH] = { 0, };
	//			KPacket kpacket(PACKET_CHAT_MSG);

	//			//인덱스 이름 메시지
	//			kpacket << 10 << computer_name << m_buffer;

	//			//리턴 값이 0보다 작으면 전송되지 않았음
	//			if (m_Net.SendMsg(m_Net.m_Sock, kpacket.m_uPacket) < 0)
	//			{
	//				ZeroMemory(&m_chatItems, sizeof(char) * 2048);
	//				strcat(m_chatItems, "Error\n");
	//				m_Net.m_bConnect = false;
	//			}
	//			ImGui::SetKeyboardFocusHere(0);
	//			strcpy(m_buffer, clear);
	//		}
	//	}
	//}
	//ImGui::End();
#pragma endregion

	#pragma region 네트워크 프레임
	//// 패킷 풀 사이즈로 채팅 수량 체크
	//int iChatCnt = m_Net.m_User.m_lPacketPool.size();
	//if (iChatCnt > 0 && m_iChatCount != iChatCnt)
	//{
	//	m_iChatCount = iChatCnt;
	//	char clear[2048] = { 0, };
	//	strcpy(m_chatItems, clear);

	//	std::list<KPacket>::iterator iter;
	//	//대화양이 제한량을 넘으면 지워줌
	//	if (m_Net.m_User.m_lPacketPool.size() > 10)
	//	{
	//		m_Net.m_User.m_lPacketPool.pop_front();
	//	}
	//	for (iter = m_Net.m_User.m_lPacketPool.begin();
	//		iter != m_Net.m_User.m_lPacketPool.end();
	//		iter++)
	//	{

	//		KChatting recv_data;
	//		ZeroMemory(&recv_data, sizeof(recv_data));
	//		(*iter) >> recv_data.index >> recv_data.name
	//			>> recv_data.message;
	//		//strcat(m_chatItems, (char*)(*iter).m_uPacket.ph.time);
	//		strcat(m_chatItems, recv_data.name);
	//		strcat(m_chatItems, " : ");
	//		strcat(m_chatItems, recv_data.message);
	//		strcat(m_chatItems, "\n");

	//		(*iter).Reset();
	//	}
	//}
#pragma endregion

	g_SceneManager.Frame();
    return true;
}
bool Sample::Render()
{
	g_SceneManager.Render();
    return true;
}
bool Sample::Release()
{
	g_SceneManager.Release();
	//m_Net.CloseNetwork();
    return true;
}

Sample::Sample()
{
}

Sample::~Sample()
{
}

WinMain_OPT(스프라이트 애니메이션, 960, 540);
//WinMain_OPT(스프라이트 애니메이션, 800, 600);