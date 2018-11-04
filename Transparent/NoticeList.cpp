#include "stdafx.h"
#include "NoticeList.h"
#include <string>

IMPLEMENT_DYNAMIC(NoticeList, CListCtrl)

BEGIN_MESSAGE_MAP(NoticeList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

NoticeList::NoticeList()
{
}

NoticeList::~NoticeList()
{
}

bool NoticeList::SetRowHeight(const int height)
{
	m_imageList.DeleteImageList();
	m_imageList.Create(1, height, ILC_COLOR32, 1, 0);

	if (SetImageList(&m_imageList, LVSIL_SMALL) == NULL)
	{
		return false;
	}

	return true;
}

void NoticeList::OnCustomDraw(NMHDR * pNMHDR, LRESULT * pResult)
{
	*pResult = CDRF_DODEFAULT;
	LPNMLVCUSTOMDRAW pcd = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	HDC hdc = pcd->nmcd.hdc;
	CDC* pDC = CDC::FromHandle(hdc);
	RECT rect = pcd->nmcd.rc;
	CString log;
	switch (pcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		if (GetItemCount() == 0)
		{
			std::wstring text = L"Empty";
			SetBkMode(hdc, TRANSPARENT);


			DrawText(hdc, text.c_str(), static_cast<int>(text.length()), const_cast<LPRECT>(&rect), DT_CENTER | DT_END_ELLIPSIS | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER);
		}

		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	}

	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_NOTIFYPOSTPAINT;
		break;
	}

	case CDDS_ITEMPOSTPAINT:
	{
		auto item = static_cast<int>(pcd->nmcd.dwItemSpec);
		auto subitem = pcd->iSubItem;

		if (pcd->nmcd.uItemState & ODS_FOCUS)
		{
			FillRect(hdc, rect, RGB(229, 243, 255));
		}
		else
		{
			FillRect(hdc, rect, RGB(255, 255, 255));
		}

		CRect rcSub = rect;
		rcSub.top += 20;
		rcSub.bottom -= 10;

		CString str = GetItemText(item, 0);
		if (!str.IsEmpty())
		{
			pDC->DrawText(str, rcSub, DT_LEFT | DT_SINGLELINE | DT_VCENTER);

			CPen pen;
			pen.CreatePen(PS_SOLID, 1, RGB(223, 222, 222));
			auto oldPen = pDC->SelectObject(pen);

			pDC->MoveTo(rect.left, rect.bottom - 1);
			pDC->LineTo(rect.right, rect.bottom - 1);
		}

		break;
	}

	default:
		break;
	}
}

void NoticeList::FillRect(HDC& hdc, const RECT& rect, COLORREF color) const
{
	auto oldColor = ::SetBkColor(hdc, color);
	::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, L"", 0, nullptr);
	::SetBkColor(hdc, oldColor);
}
