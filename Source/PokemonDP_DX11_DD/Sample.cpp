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
	#pragma region ��Ʈ��ũ �ʱ�ȭ
	//auto size = static_cast<DWORD>((sizeof(char)*24)+1);
	//if (!GetComputerNameA(computer_name, &size))
	//{
	//	strcat(computer_name, "NoName");
	//}

	//m_Net.InitNetwork();
	////Ÿ�� ��Ʈ ������
	//if(m_Net.Connect(g_hWnd, SOCK_STREAM, 10000, ip_Address))
	//{
	//	m_bConnect = true;
	//}
#pragma endregion

    //���� �ʱ�ȭ 
	g_SoundManager.Init();
	//�� �Ŵ���
	g_SceneManager.Init(m_pImmediateContext);

    return true;
}
// ������ �Լ�
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
	//	//������ �ȵǾ� ������ ���� �� �õ�
	//	if (!m_Net.m_bConnect)
	//	{
	//		ImGui::InputText("������ �Է�", ip_Address, sizeof(char) * 30);
	//		ImGui::SameLine();
	//		if (ImGui::Button(u8"���� ��õ�"))
	//		{
	//			if (m_Net.Connect(g_hWnd, SOCK_STREAM, 10000, ip_Address))
	//			{
	//				m_bConnect = true;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		ImGui::BeginChild(u8"ä��â", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing() - 15));
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

	//			//�ε��� �̸� �޽���
	//			kpacket << 10 << computer_name << m_buffer;

	//			//���� ���� 0���� ������ ���۵��� �ʾ���
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

	#pragma region ��Ʈ��ũ ������
	//// ��Ŷ Ǯ ������� ä�� ���� üũ
	//int iChatCnt = m_Net.m_User.m_lPacketPool.size();
	//if (iChatCnt > 0 && m_iChatCount != iChatCnt)
	//{
	//	m_iChatCount = iChatCnt;
	//	char clear[2048] = { 0, };
	//	strcpy(m_chatItems, clear);

	//	std::list<KPacket>::iterator iter;
	//	//��ȭ���� ���ѷ��� ������ ������
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

WinMain_OPT(��������Ʈ �ִϸ��̼�, 960, 540);
//WinMain_OPT(��������Ʈ �ִϸ��̼�, 800, 600);