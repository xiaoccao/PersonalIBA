#pragma once

#include "DdnDataX.h"
#include "RealNameDataX.h"

#include "..\NetBarUser.h"
#include "..\Servlet\BalanceMethod.h"
#include "..\Servlet\IDCheckCardMethod.h"

using namespace NS_SERVLET;

namespace NS_REALNAME
{
	
	typedef struct tag_CheckoutInfo
	{
		TCHAR szIP[50];
		TCHAR szTermId[50];
		TCHAR szNetId[100];
		TCHAR szName[100];
		int nCheckoutType;
		int nMoney;
		bool bClientCheckOut;		// �ͻ��˷����Ľ�����Ϣ
		
		tag_CheckoutInfo()
		{
			ZeroMemory(szIP, sizeof(szIP));
			ZeroMemory(szTermId, sizeof(szTermId));
			ZeroMemory(szNetId, sizeof(szNetId));
			ZeroMemory(szName, sizeof(szName));
			nCheckoutType = 0;
			nMoney = 0;
			bClientCheckOut = false;
		};
	}CheckoutInfo;

class CRealNameBase
{
public:	
	virtual ~CRealNameBase(void);

	//!<ʵ����ʼ��
	virtual BOOL InitRealName();
	
	//!<ʵ������
	virtual BOOL UnInitRealName();

	//!<ʵ�����
	virtual BOOL CheckRealName();
	/**
	* ��Ӧʵ����Ϣ
	* @param nMsgType 0:ˢ����Ϣ��1:��ʱ��Ϣ
	*/
	virtual INT  OnRealNameMsg(UINT nMsgType, LPVOID lpData = NULL, DWORD dwLen = 0);

	//!<���ڶ���ִ��ˢ����Ϣ
	virtual INT  OnExecuteMsg(UINT nExecuteType, LPVOID lpData = NULL, DWORD dwLen = 0);

	//!<ˢϣ֮��Ķ�����
	virtual void OnCardIn();

	//!<����ʵ����ع���
	virtual INT  InvokeRealName(UINT nMsgType, LPVOID lpData = NULL, DWORD dwLen = 0);

	//!<ɨ�����Ƿ����
	virtual BOOL IsScanEnabled();

	//!<ɨ��֤��
	virtual BOOL ScanUserInfo(UINT nType, CNetBarUser& NetBarUser, UINT nOption);

	//!<ɨ��֤�����������û��Ƿ�ע�����ʾע����߳�ֵ�˿�Ի���
	virtual BOOL DoScan(UINT nType);

	//!<�ϴ���Ƭ
	virtual BOOL UploadImage(UINT nType, CNetBarUser& NetBarUser, UINT nOption);
	
	//!<�����û�
	virtual BOOL ActivationMember(const CNetBarUser& netBarUser);

	//!<�Ƿ���������
	virtual BOOL IsRegisterEnabled();

	//!<�Ƿ������ͻ��˵�¼
	virtual BOOL IsCheckInEnabled();

	//!<�Ƿ���ҪУ�鿪��ʵ������
	virtual BOOL NeedToCheckRegisterData();

	//!<�Ƿ�����ʵ���˵�
	virtual BOOL IsMenuEnabled();

	//!<�Ƿ�����ʵ����չ�˵�
	virtual BOOL IsRealNameExtendMenuEnabled();

	//!<ˢ�����Ƿ�������
	virtual BOOL RobFocusAfterSwipingCard();

	//!<����Ա��¼
	virtual void OnCashierCheckIn();

	// 2011/12/02-8232-gxx: 
	void ExecuteRNS(BOOL bInit);

	// 2014-5-8 - qsc 
	void ExeSfreg(LPCTSTR szNation, LPCTSTR szDepart, LPCTSTR szAddress, LPCTSTR szTel);

	// 2014-5-23 - qsc
	void SendRegDataToProxy(LPCTSTR szNation, LPCTSTR szDepart, LPCTSTR szAddress, LPCTSTR szTel);

	// 2014-10-10 - qsc
	virtual void OnCheckOut(const CheckoutInfo* pCheckoutInfo){}
protected:

	CRealNameBase(void);

	virtual INT OnOldUser(CNetBarUser & NetBarUser);  //�����

	virtual INT OnOldUserInLocalMode(CNetBarUser & NetBarUser); //���ؼ����

	virtual INT OnNewUser(CNetBarUser & NetBarUser); //ע��

	virtual BOOL CheckCard(LPCTSTR lpszNetId);//У��NetId. ������m_nCardId��m_nMemberId.

	virtual BOOL CheckCardInLocalMode(LPCTSTR lpszNetId); //����ģʽ��У��NetId.��Member�����Ҷ�ӦNetId��NebBarId,�ҿ��õ��˻�,������m_nCardId��m_nMemberId,����m_NetBarUser

	virtual BOOL QueryBalance(); //ʹ��m_nMemberId��m_nCardId�����Ĳ���ʹ�÷��ص�SerialNum��ʾ�ڹ������С�

	//!<�Զ�����ʵ������
	virtual BOOL AutoModifyMemberInfo();

	virtual BOOL AutoMatchIDCard(CNetBarUser & NetBarUser);
	
	//�Ѷ���֤ת��Ϊ������
	virtual BOOL ChangeNetIdToPersonalId(CString strNewNetId);

	//����ʵ������
	virtual BOOL ExecuteProxy();

	// 2011/08/01-8201-gxx: 
	virtual BOOL OnLocalRealName(UINT nMsgType, CString strNetID);
	virtual BOOL DoHasLocalRealName(UINT nMsgType,LPVOID lpData = NULL, DWORD dwLen = 0);

protected:

	virtual BOOL ReadUserInfo(CNetBarUser & NetBarUser);

protected:

	BOOL m_bOpenReader;

	UINT m_nMemberId;

	UINT m_nCardId;

public:
	CNetBarUser m_NetBarUser;

protected:

	CDataXMSender m_DataXSender;

	CDataXMReceiverT<CRealNameBase> m_DataXReceiver;

	INT OnDataArrival(INT nAppId, INT nMsg, INT nParam1, INT nParam2, 
		LPVOID lpBuf, size_t cbLen);

	virtual BOOL OnCardInfo(DataX_UserInfo& dxUserInfo);

	virtual BOOL OnForceCheckOut(DataX_UserInfo& dxUserInfo);
	
	virtual BOOL OnAddMember(DataX_UserInfo& dxUserInfo);

	// 2011/06/15-gxx: ��������ף����
	BOOL SpeakBirthday(CNetBarUser & NetBarUser);
};


class CNoneRealName : public CRealNameBase
{
public:	
	CNoneRealName(void);
	virtual ~CNoneRealName(void);

	//!<ʵ����ʼ��
	virtual BOOL InitRealName();

	//!<ʵ�����
	virtual BOOL CheckRealName();

	//!<ɨ�����Ƿ����
	virtual BOOL IsScanEnabled();
};

}