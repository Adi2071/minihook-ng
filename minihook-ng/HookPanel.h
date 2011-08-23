#pragma once
#include <VGUI_Panel.h>
#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

class HookPanel :
	public vgui::Panel
{
public:
	HookPanel(vgui::Panel** ppPanel)
	{
		m_pPanel = *ppPanel;
		*ppPanel = this;

		vgui::Panel* child = m_pPanel->getChild(0);
		gEngfuncs.Con_Printf("Child Dim: %i by %i", child->getWide(), child->getTall());

		m_pPanel->setEnabled(true);
		m_pPanel->setPaintEnabled(true);
		m_pPanel->requestFocus();
	}

	vgui::Panel* m_pPanel;

	virtual void   setPos(int x,int y);
	virtual void   getPos(int& x,int& y);
	virtual void   setSize(int wide,int tall);
	virtual void   getSize(int& wide,int& tall);
	virtual void   setBounds(int x,int y,int wide,int tall);
	virtual void   getBounds(int& x,int& y,int& wide,int& tall);
	virtual int    getWide();
	virtual int    getTall();
	virtual Panel* getParent();
	virtual void   setVisible(bool state);
	virtual bool   isVisible();
	virtual bool   isVisibleUp();
	virtual void   repaint();
	virtual void   repaintAll();
	virtual void   getAbsExtents(int& x0,int& y0,int& x1,int& y1);
	virtual void   getClipRect(int& x0,int& y0,int& x1,int& y1);
	virtual void   setParent(Panel* newParent);
	virtual void   addChild(Panel* child);
	virtual void   insertChildAt(Panel* child,int index);
	virtual void   removeChild(Panel* child);
	virtual bool   wasMousePressed(vgui::MouseCode code);
	virtual bool   wasMouseDoublePressed(vgui::MouseCode code);
	virtual bool   isMouseDown(vgui::MouseCode code);
	virtual bool   wasMouseReleased(vgui::MouseCode code);
	virtual bool   wasKeyPressed(vgui::KeyCode code);
	virtual bool   isKeyDown(vgui::KeyCode code);
	virtual bool   wasKeyTyped(vgui::KeyCode code);
	virtual bool   wasKeyReleased(vgui::KeyCode code);
	virtual void   addInputSignal(vgui::InputSignal* s);
	virtual void   removeInputSignal(vgui::InputSignal* s);
	virtual void   addRepaintSignal(vgui::RepaintSignal* s);
	virtual void   removeRepaintSignal(vgui::RepaintSignal* s);
	virtual bool   isWithin(int x,int y); //in screen space
	virtual Panel* isWithinTraverse(int x,int y);
	virtual void   localToScreen(int& x,int& y);
	virtual void   screenToLocal(int& x,int& y);
	virtual void   setCursor(vgui::Cursor* cursor);
	virtual void   setCursor(vgui::Scheme::SchemeCursor scu);
	virtual vgui::Cursor* getCursor();
	virtual void   setMinimumSize(int wide,int tall);
	virtual void   getMinimumSize(int& wide,int& tall);
	virtual void   requestFocus();
	virtual bool   hasFocus();
	virtual int    getChildCount();
	virtual Panel* getChild(int index);
	virtual void   setLayout(vgui::Layout* layout);
	virtual void   invalidateLayout(bool layoutNow);
	virtual void   setFocusNavGroup(vgui::FocusNavGroup* focusNavGroup);
	virtual void   requestFocusPrev();
	virtual void   requestFocusNext();
	virtual void   addFocusChangeSignal(vgui::FocusChangeSignal* s);
	virtual bool   isAutoFocusNavEnabled();
	virtual void   setAutoFocusNavEnabled(bool state);
	virtual void   setBorder(vgui::Border* border);
	virtual void   setPaintBorderEnabled(bool state);
	virtual void   setPaintBackgroundEnabled(bool state);
	virtual void   setPaintEnabled(bool state);
	virtual void   getInset(int& left,int& top,int& right,int& bottom);
	virtual void   getPaintSize(int& wide,int& tall);
	virtual void   setPreferredSize(int wide,int tall);
	virtual void   getPreferredSize(int& wide,int& tall);
	virtual vgui::SurfaceBase* getSurfaceBase();
	virtual bool   isEnabled();
	virtual void   setEnabled(bool state);
	virtual void   setBuildGroup(vgui::BuildGroup* buildGroup,const char* panelPersistanceName);
	virtual bool   isBuildGroupEnabled();
	virtual void   removeAllChildren();
	virtual void   repaintParent();
	virtual Panel* createPropertyPanel();
	virtual void   getPersistanceText(char* buf,int bufLen);
	virtual void   applyPersistanceText(const char* buf);
	virtual void   setFgColor(vgui::Scheme::SchemeColor sc);
	virtual void   setBgColor(vgui::Scheme::SchemeColor sc);
	virtual void   setFgColor(int r,int g,int b,int a);
	virtual void   setBgColor(int r,int g,int b,int a);
	virtual void   getFgColor(int& r,int& g,int& b,int& a);
	virtual void   getBgColor(int& r,int& g,int& b,int& a);
	virtual void   setBgColor(vgui::Color color);
	virtual void   setFgColor(vgui::Color color);
	virtual void   getBgColor(vgui::Color& color);
	virtual void   getFgColor(vgui::Color& color);
	virtual void   setAsMouseCapture(bool state);
	virtual void   setAsMouseArena(bool state);
	virtual vgui::App*   getApp();
	virtual void   getVirtualSize(int& wide,int& tall);
	virtual void   setLayoutInfo(vgui::LayoutInfo* layoutInfo);
	virtual vgui::LayoutInfo* getLayoutInfo();
	virtual bool   isCursorNone();
public: //bullshit public
	virtual void solveTraverse();
	virtual void paintTraverse();
	virtual void setSurfaceBaseTraverse(vgui::SurfaceBase* surfaceBase);
protected:
	virtual void performLayout();
	virtual void internalPerformLayout();
	virtual void drawSetColor(vgui::Scheme::SchemeColor sc);
	virtual void drawSetColor(int r,int g,int b,int a);
	virtual void drawFilledRect(int x0,int y0,int x1,int y1);
	virtual void drawOutlinedRect(int x0,int y0,int x1,int y1);
	virtual void drawSetTextFont(vgui::Scheme::SchemeFont sf);
	virtual void drawSetTextFont(vgui::Font* font);
	virtual void drawSetTextColor(vgui::Scheme::SchemeColor sc);
	virtual void drawSetTextColor(int r,int g,int b,int a);
	virtual void drawSetTextPos(int x,int y);
	virtual void drawPrintText(const char* str,int strlen);
	virtual void drawPrintText(int x,int y,const char* str,int strlen);
	virtual void drawPrintChar(char ch);
	virtual void drawPrintChar(int x,int y,char ch);
	virtual void drawSetTextureRGBA(int id,const char* rgba,int wide,int tall);
	virtual void drawSetTexture(int id);
	virtual void drawTexturedRect(int x0,int y0,int x1,int y1);
	virtual void solve();
	virtual void paintTraverse(bool repaint);
	virtual void paintBackground();
	virtual void paint();
	virtual void paintBuildOverlay();
	virtual void internalCursorMoved(int x,int y);
	virtual void internalCursorEntered();
	virtual void internalCursorExited();
	virtual void internalMousePressed(vgui::MouseCode code);
	virtual void internalMouseDoublePressed(vgui::MouseCode code);
	virtual void internalMouseReleased(vgui::MouseCode code);
	virtual void internalMouseWheeled(int delta);
	virtual void internalKeyPressed(vgui::KeyCode code);
	virtual void internalKeyTyped(vgui::KeyCode code);
	virtual void internalKeyReleased(vgui::KeyCode code);
	virtual void internalKeyFocusTicked();
	virtual void internalFocusChanged(bool lost);
	virtual void internalSetCursor();
};
